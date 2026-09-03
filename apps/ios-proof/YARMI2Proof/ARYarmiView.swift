import ARKit
import RealityKit
import SwiftUI
import UIKit

struct ARYarmiView: UIViewRepresentable {
    @ObservedObject var model: ProofModel
    let resetCounter: Int

    func makeCoordinator() -> Coordinator {
        Coordinator(model: model, resetCounter: resetCounter)
    }

    func makeUIView(context: Context) -> ARView {
        let view = ARView(frame: .zero, cameraMode: .ar, automaticallyConfigureSession: false)
        context.coordinator.attach(to: view)
        return view
    }

    func updateUIView(_ uiView: ARView, context: Context) {
        if context.coordinator.lastResetCounter != resetCounter {
            context.coordinator.lastResetCounter = resetCounter
            context.coordinator.reset()
        }
    }

    @MainActor
    final class Coordinator: NSObject {
        private weak var arView: ARView?
        private let model: ProofModel
        private let toneEngine = ToneEngine()

        fileprivate var lastResetCounter: Int

        private var ensemble = ProofEnsemble()
        private var startPoint: SIMD3<Float>?
        private var endPoint: SIMD3<Float>?
        private var rootAnchor: AnchorEntity?
        private var cursorEntity: ModelEntity?
        private var displayLink: CADisplayLink?
        private var playbackStartedAt: CFTimeInterval = 0
        private var previousPhase: Float = 0

        private let cycleSeconds: Double = 4.0

        init(model: ProofModel, resetCounter: Int) {
            self.model = model
            self.lastResetCounter = resetCounter
        }

        deinit {
            displayLink?.invalidate()
        }

        func attach(to view: ARView) {
            arView = view

            let configuration = ARWorldTrackingConfiguration()
            configuration.planeDetection = [.horizontal, .vertical]
            configuration.environmentTexturing = .automatic
            view.session.run(configuration)

            let tap = UITapGestureRecognizer(target: self, action: #selector(handleTap(_:)))
            view.addGestureRecognizer(tap)
        }

        @objc private func handleTap(_ recognizer: UITapGestureRecognizer) {
            guard let view = arView else { return }
            let point = recognizer.location(in: view)
            let results = view.raycast(from: point, allowing: .estimatedPlane, alignment: .any)
            guard let hit = results.first else {
                model.instruction = "No surface at that point yet. Move the device and try again."
                return
            }

            let c = hit.worldTransform.columns.3
            let worldPoint = SIMD3<Float>(c.x, c.y, c.z)

            if startPoint == nil {
                beginTrack(at: worldPoint)
            } else if endPoint == nil {
                finishTrack(at: worldPoint)
            } else {
                addSample(near: worldPoint)
            }
        }

        private func beginTrack(at point: SIMD3<Float>) {
            startPoint = point

            let anchor = AnchorEntity(world: point)
            rootAnchor = anchor
            arView?.scene.addAnchor(anchor)

            anchor.addChild(makeSphere(radius: 0.014, color: .systemGreen))
            model.showFirstPoint()
        }

        private func finishTrack(at point: SIMD3<Float>) {
            guard let start = startPoint, let anchor = rootAnchor else { return }
            let vector = point - start
            guard simd_length(vector) > 0.06 else {
                model.instruction = "Place the track end a little farther from the start."
                return
            }

            endPoint = point
            let localEnd = vector

            let endMarker = makeSphere(radius: 0.014, color: .systemRed)
            endMarker.position = localEnd
            anchor.addChild(endMarker)

            let line = makeLine(from: .zero, to: localEnd)
            anchor.addChild(line)

            let cursor = makeSphere(radius: 0.010, color: .white)
            cursor.position = SIMD3<Float>(0, 0.025, 0)
            anchor.addChild(cursor)
            cursorEntity = cursor

            let track = ProofTrack(id: UUID(), start: start, end: point)
            ensemble.apply(.createTrack(actor: ensemble.localStation.id, track: track))

            model.showTrackReady()
            startPlayback()
        }

        private func addSample(near worldPoint: SIMD3<Float>) {
            guard
                let start = startPoint,
                let end = endPoint,
                let anchor = rootAnchor,
                let track = ensemble.track
            else { return }

            let vector = end - start
            let denom = simd_dot(vector, vector)
            guard denom > 0 else { return }

            let rawT = simd_dot(worldPoint - start, vector) / denom
            let t = min(1, max(0, rawT))
            let localPoint = vector * t

            let frequency = 220.0 * pow(4.0, Double(t))
            let sample = ProofSample(
                id: UUID(),
                trackID: track.id,
                position: t,
                frequency: frequency
            )
            ensemble.apply(.createSample(actor: ensemble.localStation.id, sample: sample))

            let marker = makeSphere(radius: 0.012, color: .systemOrange)
            marker.position = localPoint + SIMD3<Float>(0, 0.012, 0)
            anchor.addChild(marker)

            toneEngine.play(frequency: frequency)
            model.showSampleCount(ensemble.samples.count)
        }

        private func startPlayback() {
            displayLink?.invalidate()
            playbackStartedAt = CACurrentMediaTime()
            previousPhase = 0

            let link = CADisplayLink(target: self, selector: #selector(stepPlayback))
            link.add(to: .main, forMode: .common)
            displayLink = link
        }

        @objc private func stepPlayback() {
            guard let start = startPoint, let end = endPoint, let cursor = cursorEntity else { return }

            let elapsed = CACurrentMediaTime() - playbackStartedAt
            let phase = Float((elapsed.truncatingRemainder(dividingBy: cycleSeconds)) / cycleSeconds)
            let vector = end - start
            cursor.position = vector * phase + SIMD3<Float>(0, 0.025, 0)

            for sample in ensemble.samples where crossed(sample.position, from: previousPhase, to: phase) {
                toneEngine.play(frequency: sample.frequency)
            }

            previousPhase = phase
        }

        private func crossed(_ target: Float, from previous: Float, to current: Float) -> Bool {
            if current >= previous {
                return target > previous && target <= current
            }
            return target > previous || target <= current
        }

        func reset() {
            displayLink?.invalidate()
            displayLink = nil
            previousPhase = 0

            if let anchor = rootAnchor {
                arView?.scene.removeAnchor(anchor)
            }

            startPoint = nil
            endPoint = nil
            rootAnchor = nil
            cursorEntity = nil
            ensemble.apply(.reset(actor: ensemble.localStation.id))
        }

        private func makeSphere(radius: Float, color: UIColor) -> ModelEntity {
            let mesh = MeshResource.generateSphere(radius: radius)
            let material = SimpleMaterial(color: color, isMetallic: false)
            return ModelEntity(mesh: mesh, materials: [material])
        }

        private func makeLine(from start: SIMD3<Float>, to end: SIMD3<Float>) -> ModelEntity {
            let direction = end - start
            let length = simd_length(direction)
            let midpoint = (start + end) * 0.5

            let mesh = MeshResource.generateBox(
                size: SIMD3<Float>(0.006, 0.006, length),
                cornerRadius: 0.002
            )
            let material = SimpleMaterial(color: UIColor.white.withAlphaComponent(0.85), isMetallic: false)
            let entity = ModelEntity(mesh: mesh, materials: [material])
            entity.position = midpoint
            entity.orientation = simd_quatf(
                from: SIMD3<Float>(0, 0, 1),
                to: simd_normalize(direction)
            )
            return entity
        }
    }
}
