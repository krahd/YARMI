#include "LibPdBackend.h"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

extern "C"
{
#include <z_libpd.h>
}

#include <algorithm>
#include <cmath>

namespace yarmi
{
LibPdBackend::~LibPdBackend()
{
    release();
}

bool LibPdBackend::prepare(const double sampleRate,
                           const int,
                           const int outputChannels)
{
    release();

    if (outputChannels < channels || sampleRate <= 0.0)
    {
        status = "requires stereo output and a valid sample rate";
        return false;
    }

    const auto patchDirectory = juce::File::getSpecialLocation(juce::File::tempDirectory)
                                    .getChildFile("YARMI-pd");
    if (patchDirectory.createDirectory().failed())
    {
        status = "could not create the embedded patch directory";
        return false;
    }

    const auto mainPatch = patchDirectory.getChildFile("yarmi.pd");
    const auto voicePatch = patchDirectory.getChildFile("yarmi_voice.pd");
    if (! mainPatch.replaceWithData(YarmiBinaryData::yarmi_pd,
                                    YarmiBinaryData::yarmi_pdSize)
        || ! voicePatch.replaceWithData(YarmiBinaryData::yarmi_voice_pd,
                                        YarmiBinaryData::yarmi_voice_pdSize))
    {
        status = "could not unpack the embedded Pd patches";
        return false;
    }

    if (libpd_init() != 0 || libpd_init_audio(0, channels, static_cast<int>(sampleRate)) != 0)
    {
        status = "libpd audio initialisation failed";
        return false;
    }

    patchHandle = libpd_openfile(mainPatch.getFileName().toRawUTF8(),
                                 patchDirectory.getFullPathName().toRawUTF8());
    if (patchHandle == nullptr)
    {
        status = "the embedded yarmi.pd patch did not open";
        return false;
    }

    libpd_start_message(1);
    libpd_add_float(1.0f);
    libpd_finish_message("pd", "dsp");
    initialised = true;
    status = "embedded Pd synth ready";
    bufferedReadPosition = 0;
    bufferedSamples = 0;
    appliedCutoff = -1.0f;
    return true;
}

void LibPdBackend::release() noexcept
{
    if (patchHandle != nullptr)
    {
        libpd_start_message(1);
        libpd_add_float(0.0f);
        libpd_finish_message("pd", "dsp");
        libpd_closefile(patchHandle);
        patchHandle = nullptr;
    }

    initialised = false;
    bufferedReadPosition = 0;
    bufferedSamples = 0;
}

void LibPdBackend::setCutoff(const float hz) noexcept
{
    requestedCutoff.store(hz, std::memory_order_relaxed);
}

void LibPdBackend::sendEvent(const TriggerEvent& event) noexcept
{
    if (libpd_start_message(3) != 0)
        return;

    libpd_add_float(static_cast<float>(event.lane));
    libpd_add_float(static_cast<float>(event.midiNote));
    libpd_add_float(event.velocity * 127.0f);
    libpd_finish_list("yarmi-note");
}

void LibPdBackend::generateQuantum() noexcept
{
    const auto cutoff = requestedCutoff.load(std::memory_order_relaxed);
    if (std::abs(cutoff - appliedCutoff) >= 1.0f)
    {
        libpd_float("yarmi-cutoff", cutoff);
        appliedCutoff = cutoff;
    }

    std::fill(interleavedOutput.begin(), interleavedOutput.end(), 0.0f);
    if (libpd_process_float(1, silentInput.data(), interleavedOutput.data()) != 0)
        std::fill(interleavedOutput.begin(), interleavedOutput.end(), 0.0f);

    bufferedReadPosition = 0;
    bufferedSamples = quantum;
}

void LibPdBackend::render(float* const* outputs,
                          const int outputChannels,
                          const int numSamples,
                          const TriggerEvent* events,
                          const std::size_t eventCount) noexcept
{
    if (! initialised || outputs == nullptr || outputChannels <= 0 || numSamples <= 0)
        return;

    int destination = 0;
    std::size_t nextEvent = 0;

    while (destination < numSamples)
    {
        if (bufferedSamples == 0)
        {
            // Pd can only process 64-frame quanta. Events are placed at the nearest
            // quantum, which bounds scheduling error to 63 samples on any device.
            while (nextEvent < eventCount
                   && events[nextEvent].sampleOffset < destination + quantum)
                sendEvent(events[nextEvent++]);

            generateQuantum();
        }

        const auto toCopy = std::min(bufferedSamples, numSamples - destination);
        for (int channel = 0; channel < outputChannels; ++channel)
        {
            auto* target = outputs[channel];
            if (target == nullptr)
                continue;

            if (channel < channels)
            {
                for (int sample = 0; sample < toCopy; ++sample)
                    target[destination + sample]
                        = interleavedOutput[static_cast<std::size_t>(
                            (bufferedReadPosition + sample) * channels + channel)];
            }
            else
            {
                std::fill_n(target + destination, toCopy, 0.0f);
            }
        }

        destination += toCopy;
        bufferedReadPosition += toCopy;
        bufferedSamples -= toCopy;
    }

    // If the current callback ended inside a pre-rendered Pd quantum, retain the
    // event so its envelope begins in the very next generated quantum.
    while (nextEvent < eventCount)
        sendEvent(events[nextEvent++]);
}

BackendHealth LibPdBackend::health() const
{
    return { initialised, quantum, status };
}
} // namespace yarmi
