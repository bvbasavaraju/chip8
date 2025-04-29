#pragma once

#include "opcodes.hpp"

namespace chip8 {

struct instruction_t {
private:
    std::uint8_t opcode;
    std::uint16_t operands_;

    instruction_t(std::uint16_t inst)
    : opcode(((inst & 0xF000) >> 12)),
    operands_((inst & 0x0FFF)) {}

public:
    static auto decode(std::uint16_t inst) -> instruction_t {
        return instruction_t{(inst)};
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    const auto execute() const {

        operands_t operands;
        auto run  = [&]<std::uint8_t op_val>() -> void {
            auto status = opcode_t<op_val>::decode_operands(operands_, operands);
            if(!status) {
                // TODO: Log status
            }

            opcode_t<op_val>::template validate_operands_and_execute<Operations_t>(operands);
        };

        switch (opcode)
        {
        case 0:
            run.template operator()<0>();
            break;

        case 1:
            run.template operator()<1>();
            break;

        case 2:
            run.template operator()<2>();
            break;

        case 3:
            run.template operator()<3>();
            break;

        case 4:
            run.template operator()<4>();
            break;

        case 5:
            run.template operator()<5>();
            break;

        case 6:
            run.template operator()<6>();
            break;

        case 7:
            run.template operator()<7>();
            break;

        case 8:
            run.template operator()<8>();
            break;

        case 9:
            run.template operator()<9>();
            break;

        case 0xA:
            run.template operator()<0xA>();
            break;

        case 0xB:
            run.template operator()<0xB>();
            break;
            

        case 0xC:
            run.template operator()<0xC>();
            break;

        case 0xD:
            run.template operator()<0xD>();
            break;

        case 0xE:
            run.template operator()<0xE>();
            break;

        case 0xF:
            run.template operator()<0xF>();
            break;
        
        default:
            Operations_t::invalid_t::handle();
            break;
        }
    }
}; 

}   // namespace chip8
