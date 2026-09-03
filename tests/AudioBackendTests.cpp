#include "Audio/LibPdBackend.h"

#include <array>
#include <cmath>
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
    constexpr int frames = 2048;
    yarmi::LibPdBackend backend;
    require(backend.prepare(48000.0, 512, 2), "embedded Pd backend prepares");
    require(backend.health().ready, "backend reports ready");
    require(backend.health().processingQuantum == 64, "Pd uses its 64-frame quantum");

    std::array<float, frames> left {};
    std::array<float, frames> right {};
    std::array<float*, 2> outputs { left.data(), right.data() };
    const yarmi::TriggerEvent trigger { 0, 0, 48, 1.0f };

    backend.setCutoff(3200.0f);
    backend.render(outputs.data(), 2, frames, &trigger, 1);

    double energy = 0.0;
    for (int sample = 0; sample < frames; ++sample)
    {
        require(std::isfinite(left[static_cast<std::size_t>(sample)]),
                "left output remains finite");
        require(std::isfinite(right[static_cast<std::size_t>(sample)]),
                "right output remains finite");
        energy += std::abs(left[static_cast<std::size_t>(sample)]);
        require(std::abs(left[static_cast<std::size_t>(sample)]
                         - right[static_cast<std::size_t>(sample)]) < 1.0e-6f,
                "embedded patch produces matched stereo output");
    }

    require(energy > 0.1, "a scheduled trigger produces non-silent audio");
    std::cout << "YARMI embedded audio test passed\n";
    return 0;
}
