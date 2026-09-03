#include "Pattern.h"

#include <algorithm>

namespace yarmi
{
Pattern::Pattern() noexcept
{
    // A syncopated but deliberately sparse starting point: playable immediately.
    rows[0].store(0b0001000100010001u, std::memory_order_relaxed);
    rows[1].store(0b0100000101000001u, std::memory_order_relaxed);
    rows[2].store(0b0010001000100010u, std::memory_order_relaxed);
    rows[3].store(0b1000010000000100u, std::memory_order_relaxed);
}

bool Pattern::valid(const int lane, const int step) noexcept
{
    return lane >= 0 && lane < lanes && step >= 0 && step < steps;
}

bool Pattern::isActive(const int lane, const int step) const noexcept
{
    if (! valid(lane, step))
        return false;

    return (rows[static_cast<std::size_t>(lane)].load(std::memory_order_relaxed)
            & (std::uint16_t { 1 } << step)) != 0;
}

void Pattern::setActive(const int lane, const int step, const bool active) noexcept
{
    if (! valid(lane, step))
        return;

    const auto mask = static_cast<std::uint16_t>(std::uint16_t { 1 } << step);
    auto& row = rows[static_cast<std::size_t>(lane)];
    if (active)
        row.fetch_or(mask, std::memory_order_relaxed);
    else
        row.fetch_and(static_cast<std::uint16_t>(~mask), std::memory_order_relaxed);
}

void Pattern::toggle(const int lane, const int step) noexcept
{
    if (! valid(lane, step))
        return;

    rows[static_cast<std::size_t>(lane)].fetch_xor(
        static_cast<std::uint16_t>(std::uint16_t { 1 } << step),
        std::memory_order_relaxed);
}

void Pattern::clear() noexcept
{
    for (auto& row : rows)
        row.store(0, std::memory_order_relaxed);
}

void Pattern::evolve(std::uint32_t seed) noexcept
{
    // Toggle roughly one cell in eight. This keeps the current phrase recognisable.
    for (int lane = 0; lane < lanes; ++lane)
    {
        for (int step = 0; step < steps; ++step)
        {
            seed ^= seed << 13u;
            seed ^= seed >> 17u;
            seed ^= seed << 5u;
            if ((seed & 7u) == 0u)
                toggle(lane, step);
        }
    }
}

int Pattern::transpose() const noexcept
{
    return transposeSemitones.load(std::memory_order_relaxed);
}

void Pattern::setTranspose(const int semitones) noexcept
{
    transposeSemitones.store(std::clamp(semitones, -24, 24), std::memory_order_relaxed);
}

float Pattern::cutoff() const noexcept
{
    return cutoffHz.load(std::memory_order_relaxed);
}

void Pattern::setCutoff(const float hz) noexcept
{
    cutoffHz.store(std::clamp(hz, 250.0f, 12000.0f), std::memory_order_relaxed);
}
} // namespace yarmi
