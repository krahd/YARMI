#pragma once

#include <cstddef>

namespace yarmi
{
struct TimingSnapshot
{
    double beat = 0.0;
    double phase = 0.0;
    double tempo = 120.0;
    std::size_t peers = 0;
    bool enabled = false;
};

class TimingService
{
public:
    virtual ~TimingService() = default;

    virtual TimingSnapshot captureAudio(double outputLatencySeconds) noexcept = 0;
    virtual TimingSnapshot captureApp() = 0;
    virtual void setTempo(double bpm) = 0;
    virtual void setEnabled(bool enabled) = 0;
    [[nodiscard]] virtual bool supportsDirectEnable() const noexcept = 0;
    virtual void showSettings() = 0;
};
} // namespace yarmi
