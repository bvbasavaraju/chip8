#pragma once

#include <opcodes.hpp>

namespace chip8 {

struct instruction_t {
private:
    std::uint8_t opcode_val;
    operands_t operands;

    instruction_t(std::uint8_t op_val)
    : opcode_val(val) {}

public:
    static const auto decode(std::uin16_t inst) {
        auto ret_val = instruction_t{(inst & 0xF000)};
        opcode_t<opcode_val>::decode_operands(inst & 0x0FFF, ret_val.operands);
        return inst;
    }

    const auto execute() const {
        opcode_t<inst>{}(operands);
    }
}; 

}   // namespace chip8
