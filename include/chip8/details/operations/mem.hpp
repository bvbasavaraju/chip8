#pragma once

#include <operands.hpp>

namespace chip8 {

struct mem_t {
    static auto operator()(NNN_t const& address) -> void {
        //TODO
    }

    static auto operator()(X_t const& reg) -> void {
        //TODO
    }

    static auto font_sprite(X_t const& reg) -> void {
        // TODO
    }

    static auto reg_dump(X_t const& reg) -> void {
        // TODO
    }

    static auto reg_load(X_t const& reg) -> void {
        // TODO
    }
};
}   // namespace chip8
