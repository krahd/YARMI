#pragma once

#include <atomic>
#include <cstdint>

namespace yarmi
{
struct DiagnosticsSnapshot
{
    double sampleRate = 0.0;
    int bufferSize = 0;
    int inputLatencySamples = 0;
    int outputLatencySamples = 0;
    double averageLoadPercent = 0.0;
    double maximumLoadPercent = 0.0;
    std::uint64_t callbacks = 0;
    std::uint64_t estimatedXruns = 0;
};

class AudioDiagnostics
{
public:
    void configure(double sampleRate,
                   int bufferSize,
                   int inputLatencySamples,
                   int outputLatencySamples) noexcept;
    void recordCallback(double elapsedSeconds, int renderedSamples) noexcept;
    [[nodiscard]] DiagnosticsSnapshot snapshot() const noexcept;

private:
    std::atomic<double> rate { 0.0 };
    std::atomic<int> block { 0 };
    std::atomic<int> inputLatency { 0 };
    std::atomic<int> outputLatency { 0 };
    std::atomic<double> averageLoad { 0.0 };
    std::atomic<double> maximumLoad { 0.0 };
    std::atomic<std::uint64_t> callbackCount { 0 };
    std::atomic<std::uint64_t> xrunCount { 0 };
};
} // namespace yarmi
