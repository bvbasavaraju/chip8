#pragma once

#include <cstdint>
#include <details/registers>
#include <details/memory.hpp>
#include <details/instruction.hpp>


/*
 * Followed the instructions from: https://en.wikipedia.org/wiki/CHIP-8
 */
namespace chip8 {

    struct core_t {
        vx regs;

        auto fetch() -> std::uint16_t {
            std::uint16_t inst = (RAM[pc] << 8) | (RAM[pc+1]);
            pc += 2;

            return instruction;
        }

        auto decode(auto const instruction) -> intruction_t {
            return instruction_t::decode(instruction);
        }
    };

}   // namespace chip8
