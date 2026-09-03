#include "LinkTimingService.h"

#include <ableton/Link.hpp>

#include <algorithm>
#include <chrono>

namespace yarmi
{
class LinkTimingService::Impl
{
public:
    explicit Impl(const double tempo) : link(tempo)
    {
        link.enable(true);
    }

    TimingSnapshot captureAudio(const double latency) noexcept
    {
        const auto state = link.captureAudioSessionState();
        const auto now = link.clock().micros();
        const auto atOutput = now + std::chrono::microseconds {
                                        static_cast<long long>(latency * 1'000'000.0) };
        return { state.beatAtTime(atOutput, 4.0),
                 state.phaseAtTime(atOutput, 4.0),
                 state.tempo(),
                 link.numPeers(),
                 link.isEnabled() };
    }

    TimingSnapshot captureApp()
    {
        const auto state = link.captureAppSessionState();
        const auto now = link.clock().micros();
        return { state.beatAtTime(now, 4.0),
                 state.phaseAtTime(now, 4.0),
                 state.tempo(),
                 link.numPeers(),
                 link.isEnabled() };
    }

    ableton::Link link;
};

LinkTimingService::LinkTimingService(const double initialTempo)
    : implementation(std::make_unique<Impl>(initialTempo))
{
}

LinkTimingService::~LinkTimingService() = default;

TimingSnapshot LinkTimingService::captureAudio(const double outputLatencySeconds) noexcept
{
    return implementation->captureAudio(outputLatencySeconds);
}

TimingSnapshot LinkTimingService::captureApp()
{
    return implementation->captureApp();
}

void LinkTimingService::setTempo(const double bpm)
{
    auto state = implementation->link.captureAppSessionState();
    state.setTempo(std::clamp(bpm, 40.0, 240.0), implementation->link.clock().micros());
    implementation->link.commitAppSessionState(state);
}

void LinkTimingService::setEnabled(const bool enabled)
{
    implementation->link.enable(enabled);
}

bool LinkTimingService::supportsDirectEnable() const noexcept
{
    return true;
}

void LinkTimingService::showSettings()
{
}
} // namespace yarmi
