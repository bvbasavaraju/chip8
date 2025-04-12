#pragma once

#include <operands.hpp>

namespace chip8 {

struct display_t {
    static auto operator()() -> void {
        //TODO: Clear Display
    }

    static auto operator()(X_t const& pos_x, Y_t const& pos_y, N_t const& pixel_height) -> void {
        //TODO: draw
    }
};

}   // namespace chip8
