#include "MainComponent.h"

#include <chrono>
#include <cmath>

namespace yarmi
{
namespace
{
constexpr auto background = 0xff10131a;
constexpr auto panel = 0xff191e29;
constexpr auto text = 0xffe8edf2;
constexpr auto mutedText = 0xff84909d;
constexpr std::array<juce::uint32, Pattern::lanes> laneColours {
    0xffff5d73, 0xffffb454, 0xff45d6a9, 0xff5fa8ff
};
constexpr std::array<const char*, Pattern::lanes> laneNames { "LOW", "FIFTH", "ROOT", "AIR" };
}

MainComponent::MainComponent()
    : timing(std::make_unique<LinkTimingService>(120.0))
{
    setOpaque(true);
    setWantsKeyboardFocus(true);

    for (auto* button : { &linkButton, &evolveButton, &clearButton })
    {
        addAndMakeVisible(*button);
        styleButton(*button);
    }

    linkButton.onClick = [this]
    {
        if (timing->supportsDirectEnable())
            timing->setEnabled(! visibleTiming.enabled);
        else
            timing->showSettings();
    };

    evolveButton.onClick = [this]
    {
        evolutionSeed = evolutionSeed * 1664525u + 1013904223u;
        pattern.evolve(evolutionSeed);
        repaint();
    };
    clearButton.onClick = [this]
    {
        pattern.clear();
        repaint();
    };

    const auto configureSlider = [this](juce::Slider& slider)
    {
        slider.setSliderStyle(juce::Slider::LinearHorizontal);
        slider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 70, 28);
        slider.setColour(juce::Slider::trackColourId, juce::Colour(0xff5fa8ff));
        slider.setColour(juce::Slider::thumbColourId, juce::Colour(0xffe8edf2));
        slider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(text));
        slider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
        slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        addAndMakeVisible(slider);
    };

    configureSlider(tempoSlider);
    tempoSlider.setRange(40.0, 240.0, 0.1);
    tempoSlider.setValue(120.0, juce::dontSendNotification);
    tempoSlider.setTextValueSuffix(" bpm");
    tempoSlider.onValueChange = [this] { timing->setTempo(tempoSlider.getValue()); };

    configureSlider(transposeSlider);
    transposeSlider.setRange(-24.0, 24.0, 1.0);
    transposeSlider.setValue(0.0, juce::dontSendNotification);
    transposeSlider.setTextValueSuffix(" st");
    transposeSlider.onValueChange = [this]
    {
        pattern.setTranspose(static_cast<int>(transposeSlider.getValue()));
    };

    configureSlider(cutoffSlider);
    cutoffSlider.setRange(250.0, 12000.0, 1.0);
    cutoffSlider.setSkewFactorFromMidPoint(2400.0);
    cutoffSlider.setValue(pattern.cutoff(), juce::dontSendNotification);
    cutoffSlider.setTextValueSuffix(" Hz");
    cutoffSlider.onValueChange = [this]
    {
        pattern.setCutoff(static_cast<float>(cutoffSlider.getValue()));
    };

    const auto midiInputs = juce::MidiInput::getAvailableDevices();
    const auto midiOutputs = juce::MidiOutput::getAvailableDevices();
    midiSummary = juce::String(midiInputs.size()) + " MIDI in / "
                  + juce::String(midiOutputs.size()) + " out";

    setSize(1024, 720);
    setAudioChannels(0, 2);
    startTimerHz(30);
}

MainComponent::~MainComponent()
{
    stopTimer();
    shutdownAudio();
}

void MainComponent::styleButton(juce::TextButton& button)
{
    button.setColour(juce::TextButton::buttonColourId, juce::Colour(panel));
    button.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xff275c52));
    button.setColour(juce::TextButton::textColourOffId, juce::Colour(text));
    button.setColour(juce::TextButton::textColourOnId, juce::Colour(text));
}

void MainComponent::prepareToPlay(const int samplesPerBlockExpected, const double sampleRate)
{
    currentSampleRate.store(sampleRate, std::memory_order_relaxed);

    auto inputLatency = 0;
    auto outputLatency = 0;
    if (auto* device = deviceManager.getCurrentAudioDevice())
    {
        inputLatency = device->getInputLatencyInSamples();
        outputLatency = device->getOutputLatencyInSamples();
    }

    outputLatencySamples.store(outputLatency, std::memory_order_relaxed);
    diagnostics.configure(sampleRate, samplesPerBlockExpected, inputLatency, outputLatency);
    sequencer.reset();

    if (! backend.prepare(sampleRate, samplesPerBlockExpected, 2))
        audioError = backend.health().detail;
    else
        audioError.clear();
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& info)
{
    const auto started = std::chrono::steady_clock::now();
    info.clearActiveBufferRegion();

    const auto sampleRate = currentSampleRate.load(std::memory_order_relaxed);
    if (info.buffer == nullptr || sampleRate <= 0.0)
        return;

    const auto latencySeconds = static_cast<double>(
                                    outputLatencySamples.load(std::memory_order_relaxed))
                                / sampleRate;
    const auto audioTiming = timing->captureAudio(latencySeconds);
    const auto eventCount = sequencer.schedule(audioTiming,
                                               sampleRate,
                                               info.numSamples,
                                               pattern,
                                               eventBuffer);

    backend.setCutoff(pattern.cutoff());
    std::array<float*, 32> outputPointers {};
    const auto channels = std::min(info.buffer->getNumChannels(),
                                   static_cast<int>(outputPointers.size()));
    for (int channel = 0; channel < channels; ++channel)
        outputPointers[static_cast<std::size_t>(channel)]
            = info.buffer->getWritePointer(channel, info.startSample);

    backend.render(outputPointers.data(),
                   channels,
                   info.numSamples,
                   eventBuffer.data(),
                   eventCount);

    const auto elapsed = std::chrono::duration<double>(
                             std::chrono::steady_clock::now() - started)
                             .count();
    diagnostics.recordCallback(elapsed, info.numSamples);
}

void MainComponent::releaseResources()
{
    backend.release();
}

juce::Rectangle<float> MainComponent::gridBounds() const
{
    return getLocalBounds().toFloat().reduced(24.0f).withTrimmedTop(98.0f).withTrimmedBottom(150.0f);
}

std::pair<int, int> MainComponent::cellAt(const juce::Point<float> point) const
{
    auto bounds = gridBounds();
    constexpr float labelWidth = 64.0f;
    bounds.removeFromLeft(labelWidth);
    if (! bounds.contains(point))
        return { -1, -1 };

    const auto step = static_cast<int>((point.x - bounds.getX())
                                       / (bounds.getWidth() / Pattern::steps));
    const auto lane = static_cast<int>((point.y - bounds.getY())
                                       / (bounds.getHeight() / Pattern::lanes));
    if (lane < 0 || lane >= Pattern::lanes || step < 0 || step >= Pattern::steps)
        return { -1, -1 };
    return { lane, step };
}

void MainComponent::editAt(const juce::Point<float> point)
{
    const auto [lane, step] = cellAt(point);
    if (lane < 0)
        return;

    const auto cell = lane * Pattern::steps + step;
    if (cell == lastEditedCell)
        return;

    pattern.toggle(lane, step);
    lastEditedCell = cell;
    repaint();
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    lastEditedCell = -1;
    editAt(event.position);
}

void MainComponent::mouseDrag(const juce::MouseEvent& event)
{
    editAt(event.position);
}

void MainComponent::paint(juce::Graphics& graphics)
{
    juce::ColourGradient wash(juce::Colour(0xff17202d),
                              0.0f,
                              0.0f,
                              juce::Colour(background),
                              0.0f,
                              static_cast<float>(getHeight()),
                              false);
    graphics.setGradientFill(wash);
    graphics.fillAll();

    auto content = getLocalBounds().toFloat().reduced(24.0f);
    auto header = content.removeFromTop(82.0f);

    graphics.setColour(juce::Colour(text));
    graphics.setFont(juce::FontOptions(32.0f, juce::Font::bold));
    graphics.drawText("YARMI", header.removeFromTop(40.0f), juce::Justification::centredLeft);
    graphics.setColour(juce::Colour(mutedText));
    graphics.setFont(juce::FontOptions(13.0f));
    const auto linkState = visibleTiming.enabled
                               ? (visibleTiming.peers > 0 ? "LINKED" : "LINK SOLO")
                               : "LOCAL TIME";
    graphics.drawText(linkState + juce::String("  /  ")
                          + juce::String(visibleTiming.tempo, 1) + " BPM  /  "
                          + midiSummary,
                      header,
                      juce::Justification::centredLeft);

    auto grid = gridBounds();
    constexpr float labelWidth = 64.0f;
    auto labels = grid.removeFromLeft(labelWidth);
    const auto cellWidth = grid.getWidth() / Pattern::steps;
    const auto cellHeight = grid.getHeight() / Pattern::lanes;
    const auto playhead = sequencer.currentStep();

    graphics.setColour(juce::Colour(0x185fa8ff));
    graphics.fillRoundedRectangle(grid.getX() + static_cast<float>(playhead) * cellWidth + 2.0f,
                                  grid.getY(),
                                  cellWidth - 4.0f,
                                  grid.getHeight(),
                                  6.0f);

    for (int lane = 0; lane < Pattern::lanes; ++lane)
    {
        const auto laneColour = juce::Colour(laneColours[static_cast<std::size_t>(lane)]);
        graphics.setFont(juce::FontOptions(11.0f, juce::Font::bold));
        graphics.setColour(laneColour.withAlpha(0.85f));
        const auto laneLabel = juce::Rectangle<float>(
            labels.getX(),
            labels.getY() + static_cast<float>(lane) * cellHeight,
            labels.getWidth() - 8.0f,
            cellHeight);
        graphics.drawText(laneNames[static_cast<std::size_t>(lane)],
                          laneLabel,
                          juce::Justification::centredRight);

        for (int step = 0; step < Pattern::steps; ++step)
        {
            auto cell = juce::Rectangle<float>(grid.getX()
                                                    + static_cast<float>(step) * cellWidth,
                                                grid.getY()
                                                    + static_cast<float>(lane) * cellHeight,
                                                cellWidth,
                                                cellHeight)
                            .reduced(4.0f);
            const auto active = pattern.isActive(lane, step);
            const auto downbeat = step % 4 == 0;
            graphics.setColour(active ? laneColour
                                      : juce::Colour(downbeat ? 0xff303847 : 0xff252b36));
            graphics.fillRoundedRectangle(cell, 7.0f);
            if (active)
            {
                graphics.setColour(juce::Colours::white.withAlpha(0.24f));
                graphics.fillEllipse(cell.withSizeKeepingCentre(5.0f, 5.0f));
            }
        }
    }

    auto footer = getLocalBounds().toFloat().reduced(24.0f).removeFromBottom(126.0f);
    graphics.setColour(juce::Colour(mutedText));
    graphics.setFont(juce::FontOptions(11.0f, juce::Font::bold));
    auto controlLabels = footer.removeFromTop(18.0f);
    const auto third = controlLabels.getWidth() / 3.0f;
    graphics.drawText("TEMPO", controlLabels.removeFromLeft(third),
                      juce::Justification::centredLeft);
    graphics.drawText("TRANSPOSE", controlLabels.removeFromLeft(third),
                      juce::Justification::centredLeft);
    graphics.drawText("COLOUR", controlLabels,
                      juce::Justification::centredLeft);

    const auto backendState = backend.health();
    const auto diagnosticLine
        = juce::String(visibleDiagnostics.sampleRate / 1000.0, 1) + " kHz  /  "
          + juce::String(visibleDiagnostics.bufferSize) + " frames  /  out "
          + juce::String(visibleDiagnostics.outputLatencySamples) + " smp  /  load "
          + juce::String(visibleDiagnostics.averageLoadPercent, 1) + "% / peak "
          + juce::String(visibleDiagnostics.maximumLoadPercent, 1) + "%  /  xruns~ "
          + juce::String(visibleDiagnostics.estimatedXruns) + "  /  Pd q"
          + juce::String(backendState.processingQuantum);
    graphics.setColour(audioError.isEmpty() ? juce::Colour(mutedText) : juce::Colour(0xffff5d73));
    graphics.setFont(juce::FontOptions(11.0f));
    graphics.drawText(audioError.isEmpty() ? diagnosticLine : audioError,
                      getLocalBounds().toFloat().reduced(24.0f).removeFromBottom(18.0f),
                      juce::Justification::centredLeft);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced(24);
    auto top = bounds.removeFromTop(56);
    clearButton.setBounds(top.removeFromRight(82).reduced(3));
    evolveButton.setBounds(top.removeFromRight(94).reduced(3));
    linkButton.setBounds(top.removeFromRight(126).reduced(3));

    auto footer = getLocalBounds().reduced(24).removeFromBottom(126);
    footer.removeFromTop(20);
    footer.removeFromBottom(22);
    const auto columnWidth = footer.getWidth() / 3;
    tempoSlider.setBounds(footer.removeFromLeft(columnWidth).reduced(4, 8));
    transposeSlider.setBounds(footer.removeFromLeft(columnWidth).reduced(4, 8));
    cutoffSlider.setBounds(footer.reduced(4, 8));
}

void MainComponent::timerCallback()
{
    visibleTiming = timing->captureApp();
    visibleDiagnostics = diagnostics.snapshot();

    if (! tempoSlider.isMouseButtonDown())
        tempoSlider.setValue(visibleTiming.tempo, juce::dontSendNotification);

    if (timing->supportsDirectEnable())
        linkButton.setButtonText(visibleTiming.enabled ? "LINK ON" : "LINK OFF");
    else
        linkButton.setButtonText("LINK SETTINGS");
    linkButton.setToggleState(visibleTiming.enabled, juce::dontSendNotification);
    repaint();
}
} // namespace yarmi
