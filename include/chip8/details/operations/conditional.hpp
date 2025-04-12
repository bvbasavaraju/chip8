#pragma once

#include <operands.hpp>

namespace chip8 {

struct conditional_t {
    static auto operator()(X_t const& reg1, Y_t const& reg2, bool if_equals) -> void {
        //TODO
    }

    static auto operator==(X_t const& reg1, Y_t const& reg2) -> void {
        //TODO
    }

    static auto operator!=(X_t const& reg1, Y_t const& reg2) -> void {
        //TODO
    }

    static auto operator()(X_t const& reg, NN_t const& val, bool if_equals) -> void {
        //TODO
    }

    static auto operator==(X_t const& reg, NN_t const& val) -> void {
        //TODO
    }
    
    static auto operator!=(X_t const& reg, NN_t const& val) -> void {
        //TODO
    }
};
}   // namespace chip8
