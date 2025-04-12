#pragma once

#include <operands.hpp>

namespace chip8 {

struct timer_t {
    static auto operator()(X_t const& reg, bool read_timer, bool sound_timer=false) -> void {
        //TODO
    }
};

}   // namespace chip8
