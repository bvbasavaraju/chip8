#pragma once

#include <operands.hpp>

namespace chip8 {

struct key_operation_t {
    static auto operator()(X_t const& reg, bool is_equal) -> void {
        //TODO
    }

    static auto operator==(X_t const& reg) -> void {
        //TODO
    }

    static auto operator!=(X_t const& reg) -> void {
        //TODO
    }

    static auto operator()(X_t const& reg) -> void {
        //TODO
    }

    static auto operator=(X_t const& reg) -> void {
        //TODO
    }
};

}   // namespace chip8
