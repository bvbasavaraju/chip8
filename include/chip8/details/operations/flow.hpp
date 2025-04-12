#pragma once

#include <cstdint>

namespace chip8 {

struct flow_t {
    static auto operator()() -> void {
        //TODO: return from subroutine
    }

    static auto operator()(NNN_t const& address, std::uint8_t reg0) -> void {
        //TODO: return from subroutine
    }

    static auto operator()(NNN_t const& address, bool just_jump = false) -> void {
        if(just_jump) {
            //TODO: jumps to address
        } else {
            //TODO: Call subroutine at address
        }
    }
};
}   // namespace chip8
