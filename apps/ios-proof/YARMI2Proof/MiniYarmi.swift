import Foundation
import simd

struct ProofStation: Hashable {
    let id: UUID
}

struct ProofTrack: Equatable {
    let id: UUID
    let start: SIMD3<Float>
    let end: SIMD3<Float>
}

struct ProofSample: Equatable, Identifiable {
    let id: UUID
    let trackID: UUID
    let position: Float
    let frequency: Double
}

enum ProofEntity: Equatable {
    case track(ProofTrack)
    case sample(ProofSample)
}

enum ProofAction {
    case createTrack(actor: UUID, track: ProofTrack)
    case createSample(actor: UUID, sample: ProofSample)
    case reset(actor: UUID)
}

struct ProofEnsemble {
    let localStation = ProofStation(id: UUID())
    private(set) var entities: [UUID: ProofEntity] = [:]

    var track: ProofTrack? {
        entities.values.compactMap {
            if case let .track(track) = $0 { return track }
            return nil
        }.first
    }

    var samples: [ProofSample] {
        entities.values.compactMap {
            if case let .sample(sample) = $0 { return sample }
            return nil
        }.sorted { $0.position < $1.position }
    }

    mutating func apply(_ action: ProofAction) {
        switch action {
        case let .createTrack(_, track):
            entities[track.id] = .track(track)
        case let .createSample(_, sample):
            entities[sample.id] = .sample(sample)
        case .reset:
            entities.removeAll()
        }
    }
}

@MainActor
final class ProofModel: ObservableObject {
    @Published var instruction = "Move the device until a surface is detected, then tap twice to define a track."
    @Published var resetCounter = 0

    func showTrackReady() {
        instruction = "Track created. Tap near it to add notes; the moving cursor will play them."
    }

    func showFirstPoint() {
        instruction = "Track start placed. Tap again to place the end."
    }

    func showSampleCount(_ count: Int) {
        instruction = "YARMI 2: \(count) note\(count == 1 ? "" : "s") on the track."
    }

    func reset() {
        resetCounter += 1
        instruction = "Move the device until a surface is detected, then tap twice to define a track."
    }
}
