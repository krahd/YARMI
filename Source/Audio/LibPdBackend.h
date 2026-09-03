#pragma once

#include "AudioBackend.h"

#include <array>
#include <atomic>

namespace yarmi
{
class LibPdBackend final : public AudioBackend
{
public:
    LibPdBackend() = default;
    ~LibPdBackend() override;

    bool prepare(double sampleRate, int maximumBlockSize, int outputChannels) override;
    void release() noexcept override;
    void setCutoff(float hz) noexcept override;
    void render(float* const* outputs,
                int outputChannels,
                int numSamples,
                const TriggerEvent* events,
                std::size_t eventCount) noexcept override;
    [[nodiscard]] BackendHealth health() const override;

private:
    static constexpr int quantum = 64;
    static constexpr int channels = 2;

    void sendEvent(const TriggerEvent& event) noexcept;
    void generateQuantum() noexcept;

    void* patchHandle = nullptr;
    bool initialised = false;
    std::string status = "not initialised";
    std::array<float, quantum> silentInput {};
    std::array<float, quantum * channels> interleavedOutput {};
    int bufferedReadPosition = 0;
    int bufferedSamples = 0;
    std::atomic<float> requestedCutoff { 4200.0f };
    float appliedCutoff = -1.0f;
};
} // namespace yarmi
