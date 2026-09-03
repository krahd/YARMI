#pragma once

#include "Audio/AudioDiagnostics.h"
#include "Audio/LibPdBackend.h"
#include "Core/Pattern.h"
#include "Core/Sequencer.h"
#include "Timing/LinkTimingService.h"

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_extra/juce_gui_extra.h>

#include <array>
#include <atomic>
#include <memory>

namespace yarmi
{
class MainComponent final : public juce::AudioAppComponent,
                            private juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;

private:
    void timerCallback() override;
    [[nodiscard]] juce::Rectangle<float> gridBounds() const;
    [[nodiscard]] std::pair<int, int> cellAt(juce::Point<float> point) const;
    void editAt(juce::Point<float> point);
    void styleButton(juce::TextButton& button);

    Pattern pattern;
    Sequencer sequencer;
    LibPdBackend backend;
    AudioDiagnostics diagnostics;
    std::unique_ptr<LinkTimingService> timing;
    std::array<TriggerEvent, Sequencer::maxEventsPerBlock> eventBuffer {};

    juce::TextButton linkButton;
    juce::TextButton evolveButton { "EVOLVE" };
    juce::TextButton clearButton { "CLEAR" };
    juce::Slider tempoSlider;
    juce::Slider transposeSlider;
    juce::Slider cutoffSlider;

    TimingSnapshot visibleTiming;
    DiagnosticsSnapshot visibleDiagnostics;
    juce::String midiSummary;
    juce::String audioError;
    std::atomic<double> currentSampleRate { 0.0 };
    std::atomic<int> outputLatencySamples { 0 };
    std::uint32_t evolutionSeed = 0x5941524du;
    int lastEditedCell = -1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
} // namespace yarmi
