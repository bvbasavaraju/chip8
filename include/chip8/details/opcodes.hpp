#pragma once

#include <cstdint>
#include "operands.hpp"
#include "../utils.hpp"

/*
    Reference: https://chip8.gulrak.net/
 */

namespace chip8 {

namespace detail {

template <typename T>
struct opcode_base {
    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto validate_operands_and_execute(operands_t const& operands) -> void {
        if(!T::validate_operands(operands)) {
            Operations_t::invalid_t::handle();
            return;
        }

        T::template execute<Operations_t>(operands);
    }
};

}   // namespace detail

template <std::uint8_t op>
struct opcode_t;

// opcode 0 : 0NNN, 00E0, 00EE
template <> struct opcode_t<0> : detail::opcode_base<opcode_t<0>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        if (inst & 0x0F00) {
            operands.NNN(inst);
        } else {
            operands.NN(inst);
        }

        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return ( operands.NNN_is_valid() || operands.NN_is_valid({{0xE0, 0xEE}}))
                && !operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        if (operands.NNN_is_valid()) {
            Operations_t::call_t::perform();
        } else {
            switch(operands.NN()) 
            {
                case 0xE0:
                    Operations_t::display_t::clear_screen();
                    break;

                case 0xEE:
                    Operations_t::flow_t::function_return();
                    break;

                default:
                    Operations_t::invalid_t::handle();
                    break;
            }
        }
    }
};

// opcode 1 : 1NNN
template <> struct opcode_t<1> : detail::opcode_base<opcode_t<1>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.NNN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return !operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && !operands.NN_is_valid()
                && operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::flow_t::jump(operands.NNN());
    }
};

// opcode 2 : 2NNN
template <> struct opcode_t<2> : detail::opcode_base<opcode_t<2>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.NNN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return !operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && !operands.NN_is_valid()
                && operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::flow_t::function_call_at(operands.NNN());
    }
};

// opcode 3 : 3XNN
template <> struct opcode_t<3> : detail::opcode_base<opcode_t<3>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.NN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::conditional_t::skip_if_reg_equal_to_val(operands.X(), operands.NN());
    }
};

// opcode 4 : 4XNN
template <> struct opcode_t<4> : detail::opcode_base<opcode_t<4>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.NN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::conditional_t::skip_if_reg_not_equal_to_val(operands.X(), operands.NN());
    }
};

// opcode 5 : 5XY0
template <> struct opcode_t<5> : detail::opcode_base<opcode_t<5>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        if(inst & 0x000F) {
            // TODO: Fourth nibble should be 0 here! if not report error or crash
            return false;
        }

        operands.X(inst);
        operands.Y(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.Y_is_valid()
                && !operands.N_is_valid()
                && !operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::conditional_t::skip_if_reg_equal_to_reg(operands.X(), operands.Y());
    }
};

// opcode 6 : 6XNN
template <> struct opcode_t<6> : detail::opcode_base<opcode_t<6>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.NN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::assign_t::set_reg_to_val(operands.X(), operands.NN());
    }
};

// opcode 7: 7XNN
template <> struct opcode_t<7> : detail::opcode_base<opcode_t<7>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.NN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::math_t::add_reg_with_val_without_carry(operands.X(), operands.NN());
    }
};

// opcode 8: 8XY0, 8XY1, 8XY2, 8XY3, 8XY4, 8XY5, 8XY6, 8XY7, 8XYE
template <> struct opcode_t<8> : detail::opcode_base<opcode_t<8>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.Y(inst);
        operands.N(inst);

        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.Y_is_valid()
                && operands.N_is_valid({{0, 1, 2, 3, 4, 5, 6, 7, 0xE}})
                && !operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        switch (operands.N())
        {
        case 0:
            Operations_t::assign_t::set_reg_to_reg(operands.X(), operands.Y());
            break;
        case 1:
            Operations_t::bitwise_t::or_op(operands.X(), operands.Y());
            break;
        case 2:
            Operations_t::bitwise_t::and_op(operands.X(), operands.Y());
            break;
        case 3:
            Operations_t::bitwise_t::xor_op(operands.X(), operands.Y());
            break;
        case 4:
            Operations_t::math_t::add_reg_with_reg_with_carry(operands.X(), operands.Y());
            break;
        case 5:
            Operations_t::math_t::sub_reg_with_reg_with_carry(operands.X(), operands.Y());
            break;
        case 6:
            Operations_t::bitwise_t::right_shift(operands.X(), operands.Y());
            break;
        case 7:
            Operations_t::math_t::sub_reg_with_reg_with_carry2(operands.X(), operands.Y());
            break;
        case 0xE:
            Operations_t::bitwise_t::left_shift(operands.X(), operands.Y());
            break;
        default:
            Operations_t::invalid_t::handle();
            break;
        }
    }
};

// opcode 9: 9XY0
template <> struct opcode_t<9> : detail::opcode_base<opcode_t<9>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        if(inst & 0x000F) {
            // TODO: Fourth nibble should be 0 here! if not report error or crash
            return false;
        }

        operands.X(inst);
        operands.Y(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.Y_is_valid()
                && !operands.N_is_valid()
                && !operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::conditional_t::skip_if_reg_not_equal_to_reg(operands.X(), operands.Y());
    }
};

// opcode A: ANNN
template <> struct opcode_t<0xA> : detail::opcode_base<opcode_t<0xA>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.NNN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return !operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && !operands.NN_is_valid()
                && operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::mem_t::set_to_address(operands.NNN());
    }
};

// opcode B: BNNN
template <> struct opcode_t<0xB> : detail::opcode_base<opcode_t<0xB>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.NNN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return !operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && !operands.NN_is_valid()
                && operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::flow_t::jump_with_offset(operands.NNN());
    }
};

// opcode C: CXNN
template <> struct opcode_t<0xC> : detail::opcode_base<opcode_t<0xC>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.NN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::assign_t::set_reg_to_rand(operands.X(), operands.NN());
    }
};

// opcode D: DXYN
template <> struct opcode_t<0xD> : detail::opcode_base<opcode_t<0xD>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.Y(inst);
        operands.N(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.Y_is_valid()
                && operands.N_is_valid()
                && !operands.NN_is_valid()
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        Operations_t::display_t::draw(operands.X(), operands.Y(), operands.N());
    }
};

// opcode E: EX9E, EXA1
template <> struct opcode_t<0xE> : detail::opcode_base<opcode_t<0xE>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.NN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && operands.NN_is_valid({{0x9E, 0xA1}})
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        switch(operands.NN()) 
        {
            case 0x9E:
                Operations_t::keyop_t::skip_if_key_eq_to_reg(operands.X());
                break;

            case 0xA1:
                Operations_t::keyop_t::skip_if_key_not_eq_to_reg(operands.X());
                break;

            default:
                Operations_t::invalid_t::handle();
                break;
        }
    }
};

// opcode F: FX07, FX0A, FX15, FX18, FX1E, FX29, FX33, FX55, FX65
template <> struct opcode_t<0xF> : detail::opcode_base<opcode_t<0xF>> {
    // Static functions
    [[nodiscard]] static auto decode_operands(std::uint16_t inst, operands_t& operands) -> bool {
        operands.X(inst);
        operands.NN(inst);
        return true;
    };

    [[nodiscard]] static auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && !operands.Y_is_valid()
                && !operands.N_is_valid()
                && operands.NN_is_valid({{7, 0xA, 0x15, 0x18, 0x1E, 0x29, 0x33, 0x55, 0x65}})
                && !operands.NNN_is_valid();
    }

    template <typename Operations_t>
    requires SupportsChip8Ops<Operations_t>
    static auto execute(operands_t const& operands) -> void {
        switch(operands.NN()) {
            case 7:
                Operations_t::timer_t::get_delay(operands.X());
                break;
            case 0xA:
                Operations_t::keyop_t::read_key_stroke(operands.X());
                break;
            case 0x15:
                Operations_t::timer_t::set_delay(operands.X());
                break;
            case 0x18:
                Operations_t::timer_t::set_sound_timer(operands.X());
                break;
            case 0x1E:
                Operations_t::mem_t::add_reg(operands.X());
                break;
            case 0x29:
                Operations_t::mem_t::set_to_sprite_char(operands.X());
                break;
            case 0x33:
                Operations_t::bcd_t::set(operands.X());
                break;
            case 0x55:
                Operations_t::mem_t::reg_dump(operands.X());
                break;
            case 0x65:
                Operations_t::mem_t::reg_load(operands.X());
                break;

            default:
                Operations_t::invalid_t::handle();
                break;
        }
    }
};

}   // namespace chip8
