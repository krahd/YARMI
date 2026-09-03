#include "AudioDiagnostics.h"

#include <algorithm>

namespace yarmi
{
void AudioDiagnostics::configure(const double sampleRate,
                                 const int bufferSize,
                                 const int inputLatencySamples,
                                 const int outputLatencySamples) noexcept
{
    rate.store(sampleRate, std::memory_order_relaxed);
    block.store(bufferSize, std::memory_order_relaxed);
    inputLatency.store(inputLatencySamples, std::memory_order_relaxed);
    outputLatency.store(outputLatencySamples, std::memory_order_relaxed);
    averageLoad.store(0.0, std::memory_order_relaxed);
    maximumLoad.store(0.0, std::memory_order_relaxed);
    callbackCount.store(0, std::memory_order_relaxed);
    xrunCount.store(0, std::memory_order_relaxed);
}

void AudioDiagnostics::recordCallback(const double elapsedSeconds,
                                      const int renderedSamples) noexcept
{
    const auto sampleRate = rate.load(std::memory_order_relaxed);
    if (sampleRate <= 0.0 || renderedSamples <= 0)
        return;

    const auto availableSeconds = static_cast<double>(renderedSamples) / sampleRate;
    const auto load = std::max(0.0, elapsedSeconds / availableSeconds);

    auto previousAverage = averageLoad.load(std::memory_order_relaxed);
    averageLoad.store(previousAverage == 0.0 ? load : previousAverage * 0.98 + load * 0.02,
                      std::memory_order_relaxed);

    auto previousMaximum = maximumLoad.load(std::memory_order_relaxed);
    while (load > previousMaximum
           && ! maximumLoad.compare_exchange_weak(previousMaximum,
                                                   load,
                                                   std::memory_order_relaxed))
    {
    }

    callbackCount.fetch_add(1, std::memory_order_relaxed);
    if (elapsedSeconds > availableSeconds)
        xrunCount.fetch_add(1, std::memory_order_relaxed);
}

DiagnosticsSnapshot AudioDiagnostics::snapshot() const noexcept
{
    return { rate.load(std::memory_order_relaxed),
             block.load(std::memory_order_relaxed),
             inputLatency.load(std::memory_order_relaxed),
             outputLatency.load(std::memory_order_relaxed),
             averageLoad.load(std::memory_order_relaxed) * 100.0,
             maximumLoad.load(std::memory_order_relaxed) * 100.0,
             callbackCount.load(std::memory_order_relaxed),
             xrunCount.load(std::memory_order_relaxed) };
}
} // namespace yarmi
