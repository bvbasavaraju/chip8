#pragma once

#include <array>

namespace chip8 {

template <uint8_t REG_COUNT = 16, uint16_t RAM_SIZE = 4096>
struct resources_t {
    std::array<std::uint8_t, REG_COUNT> vx;
    std::stack<std::uint16_t> sp; 
    std::uint16_t pc;
    std::uint16_t reg_i;
    std::array<std::uint8_t, RAM_SIZE> ram;

    resources_t() 
    : vx{0},
    pc(0),
    reg_i(0),
    ram{0} {}
};

using chip8_resources_t = resources_t<>;

} // namespace chip8
