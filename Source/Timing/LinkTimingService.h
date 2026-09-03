#pragma once

#include "TimingService.h"

#include <memory>

namespace yarmi
{
class LinkTimingService final : public TimingService
{
public:
    explicit LinkTimingService(double initialTempo);
    ~LinkTimingService() override;

    TimingSnapshot captureAudio(double outputLatencySeconds) noexcept override;
    TimingSnapshot captureApp() override;
    void setTempo(double bpm) override;
    void setEnabled(bool enabled) override;
    [[nodiscard]] bool supportsDirectEnable() const noexcept override;
    void showSettings() override;

private:
    class Impl;
    std::unique_ptr<Impl> implementation;
};
} // namespace yarmi
