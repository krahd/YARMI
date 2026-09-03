#include "Sequencer.h"

#include <algorithm>
#include <cmath>

namespace yarmi
{
namespace
{
constexpr std::array<int, Pattern::lanes> laneNotes { 48, 55, 60, 63 };
constexpr std::array<float, Pattern::lanes> laneVelocities { 0.92f, 0.82f, 0.76f, 0.70f };
constexpr double stepsPerBeat = 4.0;
}

int Sequencer::wrapStep(const std::int64_t step) noexcept
{
    const auto wrapped = step % Pattern::steps;
    return static_cast<int>(wrapped < 0 ? wrapped + Pattern::steps : wrapped);
}

std::size_t Sequencer::schedule(
    const TimingSnapshot& timing,
    const double sampleRate,
    const int numSamples,
    const Pattern& pattern,
    std::array<TriggerEvent, maxEventsPerBlock>& events) noexcept
{
    if (sampleRate <= 0.0 || numSamples <= 0 || timing.tempo <= 0.0)
        return 0;

    const auto beatsInBlock = static_cast<double>(numSamples) * timing.tempo
                              / (60.0 * sampleRate);
    const auto first = static_cast<std::int64_t>(std::floor(timing.beat * stepsPerBeat));
    const auto last = static_cast<std::int64_t>(
        std::floor((timing.beat + beatsInBlock - 1.0e-10) * stepsPerBeat));

    if (! initialised || first < lastTriggeredAbsoluteStep
        || first - lastTriggeredAbsoluteStep > Pattern::steps * 4)
    {
        lastTriggeredAbsoluteStep = first - 1;
        initialised = true;
    }

    std::size_t count = 0;
    for (auto absoluteStep = first; absoluteStep <= last; ++absoluteStep)
    {
        if (absoluteStep <= lastTriggeredAbsoluteStep)
            continue;

        const auto step = wrapStep(absoluteStep);
        visibleStep.store(step, std::memory_order_relaxed);

        const auto boundaryBeat = static_cast<double>(absoluteStep) / stepsPerBeat;
        const auto exactOffset = (boundaryBeat - timing.beat) * 60.0 * sampleRate / timing.tempo;
        const auto sampleOffset = std::clamp(static_cast<int>(std::llround(exactOffset)),
                                             0,
                                             numSamples - 1);

        for (int lane = 0; lane < Pattern::lanes && count < events.size(); ++lane)
        {
            if (! pattern.isActive(lane, step))
                continue;

            const auto accent = step % 4 == 0 ? 1.08f : 1.0f;
            events[count++] = { sampleOffset,
                                lane,
                                laneNotes[static_cast<std::size_t>(lane)] + pattern.transpose(),
                                std::min(1.0f,
                                         laneVelocities[static_cast<std::size_t>(lane)] * accent) };
        }

        lastTriggeredAbsoluteStep = absoluteStep;
    }

    return count;
}

void Sequencer::reset() noexcept
{
    initialised = false;
}

int Sequencer::currentStep() const noexcept
{
    return visibleStep.load(std::memory_order_relaxed);
}
} // namespace yarmi
