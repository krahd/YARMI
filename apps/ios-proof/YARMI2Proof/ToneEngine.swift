import AVFoundation

final class ToneEngine {
    private let engine = AVAudioEngine()
    private let player = AVAudioPlayerNode()
    private let sampleRate = 44_100.0

    init() {
        let session = AVAudioSession.sharedInstance()
        try? session.setCategory(.ambient, options: [.mixWithOthers])
        try? session.setActive(true)

        engine.attach(player)
        let format = AVAudioFormat(standardFormatWithSampleRate: sampleRate, channels: 1)!
        engine.connect(player, to: engine.mainMixerNode, format: format)
        try? engine.start()
        player.play()
    }

    func play(frequency: Double) {
        let duration = 0.14
        let frameCount = AVAudioFrameCount(sampleRate * duration)
        guard
            let format = AVAudioFormat(standardFormatWithSampleRate: sampleRate, channels: 1),
            let buffer = AVAudioPCMBuffer(pcmFormat: format, frameCapacity: frameCount)
        else { return }

        buffer.frameLength = frameCount
        guard let channel = buffer.floatChannelData?[0] else { return }

        let attackFrames = max(1, Int(sampleRate * 0.008))
        let releaseFrames = max(1, Int(sampleRate * 0.045))
        let total = Int(frameCount)

        for i in 0..<total {
            let attack = min(1.0, Double(i) / Double(attackFrames))
            let releaseStart = max(0, total - releaseFrames)
            let release: Double
            if i >= releaseStart {
                release = max(0.0, Double(total - i) / Double(releaseFrames))
            } else {
                release = 1.0
            }
            let envelope = attack * release
            channel[i] = Float(sin(2.0 * .pi * frequency * Double(i) / sampleRate) * 0.22 * envelope)
        }

        player.scheduleBuffer(buffer)
        if !player.isPlaying {
            player.play()
        }
    }
}
