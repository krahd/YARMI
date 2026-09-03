#include "UI/MainComponent.h"

#include <juce_gui_extra/juce_gui_extra.h>

namespace yarmi
{
class Application final : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return JUCE_APPLICATION_NAME_STRING; }
    const juce::String getApplicationVersion() override { return JUCE_APPLICATION_VERSION_STRING; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String&) override
    {
        window = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        window.reset();
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    class MainWindow final : public juce::DocumentWindow
    {
    public:
        explicit MainWindow(const juce::String& name)
            : DocumentWindow(name,
                             juce::Colour(0xff10131a),
                             juce::DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);

           #if JUCE_IOS
            setFullScreen(true);
           #else
            setResizable(true, true);
            setResizeLimits(760, 540, 1800, 1200);
            centreWithSize(1080, 720);
           #endif
            setVisible(true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };

private:
    std::unique_ptr<MainWindow> window;
};
} // namespace yarmi

START_JUCE_APPLICATION(yarmi::Application)
