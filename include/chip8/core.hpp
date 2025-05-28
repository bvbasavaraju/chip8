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
        // TODO initialise the same instance resources to other operations!
        Call call;
        Display display;
        Flow flow;
        Conditional conditional;
        Assignment assign;
        Math math;
        Bitwise bitwise;
        KeyOp keyop;
        Mem mem;
        Timer timer;
        Bcd bcd;
        Invalid invalid;
    };

    private:
    resources_t& res;
    operations_t ops;

    public:
    core_t(resources_t& res_)
    : res(res_) {};

    [[nodiscard]] auto fetch() -> std::uint16_t {
        return res.read_instruction();
    }

    [[nodiscard]] auto decode(auto const instruction) const -> instruction_t {
        return instruction_t::decode(instruction);
    }

    auto execute(instruction_t const& inst) -> void {
        inst.execute(ops);
    }

    auto load_program(std::vector<std::uint16_t> const& pgm) -> bool {
        return res.load_program(pgm);
    }
};

}   // namespace chip8
