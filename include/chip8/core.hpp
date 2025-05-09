#pragma once

#include <cstdint>
#include <array>
#include <stack>
#include "details/resources.hpp"
#include "details/memory.hpp"
#include "details/instruction.hpp"


/*
 * Followed the instructions from: https://en.wikipedia.org/wiki/CHIP-8
 */
namespace chip8 {

template <
    typename Call,
    typename Display,
    typename Flow,
    typename Conditional,
    typename Assignment,
    typename Math,
    typename Bitwise,
    typename KeyOp,
    typename Mem,
    typename Timer,
    typename Bcd,
    typename Invalid >
struct core_t {
    public:
    //Operations
    struct operations_t {
        using call_t = Call;
        using display_t = Display;
        using flow_t = Flow;
        using conditional_t = Conditional;
        using assign_t = Assignment;
        using math_t = Math;
        using bitwise_t = Bitwise;
        using keyop_t = KeyOp;
        using mem_t = Mem;
        using timer_t = Timer;
        using bcd_t = Bcd;
        using invalid_t = Invalid;
    };

    private:
    resources_t& res;

    public:
    core_t(resources_t& res_)
    : res(res_) {};

    auto fetch() -> std::uint16_t {
        return res.read_instruction();
    }

    auto decode(auto const instruction) const -> instruction_t {
        return instruction_t::decode(instruction);
    }

    auto execute(instruction_t const& inst) -> void {
        inst.execute<operations_t>();
    }

    auto load_instruction(std::uint16_t inst) -> bool {
        return res.load_instruction(inst);
    }

    auto load_program() -> bool {
        return res.load_program();
    }
};

}   // namespace chip8
