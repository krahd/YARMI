#pragma once

#include <array>
#include <atomic>
#include <cstdint>

namespace yarmi
{
class Pattern
{
public:
    static constexpr int lanes = 4;
    static constexpr int steps = 16;

    Pattern() noexcept;

    [[nodiscard]] bool isActive(int lane, int step) const noexcept;
    void setActive(int lane, int step, bool active) noexcept;
    void toggle(int lane, int step) noexcept;
    void clear() noexcept;
    void evolve(std::uint32_t seed) noexcept;

    [[nodiscard]] int transpose() const noexcept;
    void setTranspose(int semitones) noexcept;
    [[nodiscard]] float cutoff() const noexcept;
    void setCutoff(float hz) noexcept;

private:
    static bool valid(int lane, int step) noexcept;

    std::array<std::atomic<std::uint16_t>, lanes> rows {};
    std::atomic<int> transposeSemitones { 0 };
    std::atomic<float> cutoffHz { 4200.0f };
};
} // namespace yarmi
