#include "Core/Pattern.h"
#include "Core/Sequencer.h"

#include <array>
#include <cstdlib>
#include <iostream>

namespace
{
void require(const bool condition, const char* message)
{
    if (! condition)
    {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(1);
    }
}
}

int main()
{
    yarmi::Pattern pattern;
    pattern.clear();
    require(! pattern.isActive(0, 0), "clear removes steps");
    pattern.toggle(0, 0);
    require(pattern.isActive(0, 0), "toggle activates a step");
    pattern.setTranspose(99);
    require(pattern.transpose() == 24, "transpose is bounded");

    yarmi::Sequencer sequencer;
    std::array<yarmi::TriggerEvent, yarmi::Sequencer::maxEventsPerBlock> events {};
    yarmi::TimingSnapshot timing { 0.0, 0.0, 120.0, 0, true };
    const auto eventCount = sequencer.schedule(timing, 48000.0, 512, pattern, events);
    require(eventCount == 1, "active first step schedules one voice");
    require(events[0].sampleOffset == 0, "first event begins at buffer start");
    require(events[0].midiNote == 72, "transpose is applied to the lane pitch");

    pattern.setActive(0, 0, false);
    pattern.setActive(1, 1, true);
    sequencer.reset();
    timing.beat = 0.24;
    const auto boundaryCount = sequencer.schedule(timing, 48000.0, 1024, pattern, events);
    require(boundaryCount == 1, "a sixteenth boundary inside the block is scheduled");
    require(events[0].sampleOffset > 0, "boundary has a positive sample offset");

    std::cout << "YARMI core tests passed\n";
    return 0;
}
