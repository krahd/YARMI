#pragma once

#include "Core/Sequencer.h"

#include <cstddef>
#include <string>

namespace yarmi
{
struct BackendHealth
{
    bool ready = false;
    int processingQuantum = 0;
    std::string detail;
};

class AudioBackend
{
public:
    virtual ~AudioBackend() = default;

    virtual bool prepare(double sampleRate, int maximumBlockSize, int outputChannels) = 0;
    virtual void release() noexcept = 0;
    virtual void setCutoff(float hz) noexcept = 0;
    virtual void render(float* const* outputs,
                        int outputChannels,
                        int numSamples,
                        const TriggerEvent* events,
                        std::size_t eventCount) noexcept = 0;
    [[nodiscard]] virtual BackendHealth health() const = 0;
};
} // namespace yarmi
