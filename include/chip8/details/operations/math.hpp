#pragma once

#include <operands.hpp>

namespace chip8 {

struct math_t {
    static auto operator+(X_t const& reg1, Y_t const& reg2) -> void {
        //TODO
    }

    static auto operator+(X_t const& reg, NN_t const& val) -> void {
        //TODO
    }

    static auto operator-(X_t const& reg1, Y_t const& reg2) -> void {
        //TODO
    }

    static auto operator-(Y_t const& reg2, X_t const& reg) -> void {
        //TODO
    }
};
}   // namespace chip8
