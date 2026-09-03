#pragma once

#include "Pattern.h"
#include "Timing/TimingService.h"

#include <array>
#include <cstddef>
#include <cstdint>

namespace yarmi
{
struct TriggerEvent
{
    int sampleOffset = 0;
    int lane = 0;
    int midiNote = 60;
    float velocity = 0.8f;
};

class Sequencer
{
public:
    static constexpr std::size_t maxEventsPerBlock = 64;

    std::size_t schedule(const TimingSnapshot& timing,
                         double sampleRate,
                         int numSamples,
                         const Pattern& pattern,
                         std::array<TriggerEvent, maxEventsPerBlock>& events) noexcept;

    void reset() noexcept;
    [[nodiscard]] int currentStep() const noexcept;

private:
    static int wrapStep(std::int64_t step) noexcept;

    std::int64_t lastTriggeredAbsoluteStep = 0;
    bool initialised = false;
    std::atomic<int> visibleStep { 0 };
};
} // namespace yarmi
