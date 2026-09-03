#include "LinkTimingService.h"

#import <ABLLink.h>
#import <ABLLinkSettingsViewController.h>
#import <UIKit/UIKit.h>
#import <mach/mach_time.h>

#include <algorithm>

namespace yarmi
{
namespace
{
UIViewController* topViewController()
{
    UIWindow* keyWindow = nil;
    for (UIScene* scene in UIApplication.sharedApplication.connectedScenes)
    {
        if (scene.activationState != UISceneActivationStateForegroundActive
            || ! [scene isKindOfClass:UIWindowScene.class])
            continue;

        for (UIWindow* window in static_cast<UIWindowScene*>(scene).windows)
            if (window.isKeyWindow)
                keyWindow = window;
    }

    UIViewController* controller = keyWindow.rootViewController;
    while (controller.presentedViewController != nil)
        controller = controller.presentedViewController;
    return controller;
}
}

class LinkTimingService::Impl
{
public:
    explicit Impl(const double tempo) : link(ABLLinkNew(tempo))
    {
        mach_timebase_info(&timebase);
        ABLLinkSetActive(link, true);
    }

    ~Impl()
    {
        ABLLinkSetActive(link, false);
        ABLLinkDelete(link);
    }

    TimingSnapshot captureAudio(const double latency) noexcept
    {
        auto state = ABLLinkCaptureAudioSessionState(link);
        const auto ticks = latency * 1'000'000'000.0
                           * static_cast<double>(timebase.denom)
                           / static_cast<double>(timebase.numer);
        const auto atOutput = mach_absolute_time()
                              + static_cast<uint64_t>(std::max(0.0, ticks));
        return { ABLLinkBeatAtTime(state, atOutput, 4.0),
                 ABLLinkPhaseAtTime(state, atOutput, 4.0),
                 ABLLinkGetTempo(state),
                 ABLLinkIsConnected(link) ? 1u : 0u,
                 ABLLinkIsEnabled(link) };
    }

    TimingSnapshot captureApp()
    {
        auto state = ABLLinkCaptureAppSessionState(link);
        const auto now = mach_absolute_time();
        return { ABLLinkBeatAtTime(state, now, 4.0),
                 ABLLinkPhaseAtTime(state, now, 4.0),
                 ABLLinkGetTempo(state),
                 ABLLinkIsConnected(link) ? 1u : 0u,
                 ABLLinkIsEnabled(link) };
    }

    ABLLinkRef link;
    mach_timebase_info_data_t timebase {};
};

LinkTimingService::LinkTimingService(const double initialTempo)
    : implementation(std::make_unique<Impl>(initialTempo))
{
}

LinkTimingService::~LinkTimingService() = default;

TimingSnapshot LinkTimingService::captureAudio(const double outputLatencySeconds) noexcept
{
    return implementation->captureAudio(outputLatencySeconds);
}

TimingSnapshot LinkTimingService::captureApp()
{
    return implementation->captureApp();
}

void LinkTimingService::setTempo(const double bpm)
{
    auto state = ABLLinkCaptureAppSessionState(implementation->link);
    ABLLinkSetTempo(state, std::clamp(bpm, 40.0, 240.0), mach_absolute_time());
    ABLLinkCommitAppSessionState(implementation->link, state);
}

void LinkTimingService::setEnabled(const bool)
{
    // LinkKit owns this preference. It is changed in the required settings sheet.
}

bool LinkTimingService::supportsDirectEnable() const noexcept
{
    return false;
}

void LinkTimingService::showSettings()
{
    auto* presenter = topViewController();
    if (presenter == nil)
        return;

    auto* settings = [ABLLinkSettingsViewController instance:implementation->link];
    settings.modalPresentationStyle = UIModalPresentationPopover;
    settings.popoverPresentationController.sourceView = presenter.view;
    settings.popoverPresentationController.sourceRect
        = CGRectMake(CGRectGetMidX(presenter.view.bounds),
                     CGRectGetMidY(presenter.view.bounds),
                     1.0,
                     1.0);
    [presenter presentViewController:settings animated:YES completion:nil];
}
} // namespace yarmi
