#pragma once

#include <operands.hpp>

namespace chip8 {

struct bitwise_t {
    static auto operator|(X_t const& reg1, Y_t const& reg2) -> void {
        //TODO
    }

    static auto operator&(X_t const& reg1, Y_t const& reg2) -> void {
        //TODO
    }

    static auto operator^(X_t const& reg1, Y_t const& reg2) -> void {
        //TODO
    }

    static auto operator>>(X_t const& reg) -> void {
        //TODO
    }

    static auto operator<<(X_t const& reg) -> void {
        //TODO
    }
};
}   // namespace chip8
