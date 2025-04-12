#pragma once

#include <cstdint>
#include <operands.hpp>
#include <call.hpp>

/*
    Reference: https://chip8.gulrak.net/
 */

namespace chip8 {

template <std::uint16_t op>
struct opcode_t;

// opcode 0 : 0NNN, 00E0, 00EE
template <> struct opcode_t<0> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        if(!validate_operands()) {
            //TODO: Crash or log error
        }

        if (operands.NNN_is_valid()) {
            call_t{}();
        } else {
            auto val = operands.NN().value()();
            if(val == 0xE0) {
                //TODO: clear Screen
            } else if (val == 0xEE) {
                //TODO: return from subroutine
            }
        }
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        if (inst & 0x0F00) {
            operands.NNN(inst);
        } else {
            operands.NN(inst);
        }
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.NNN_is_valid() 
                || operands.NN_is_valid();
    }
};

// opcode 1 : 1NNN
template <> struct opcode_t<1> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        // TODO: Jumps to address
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.NNN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.NNN_is_valid();
    }
};

// opcode 2 : 2NNN
template <> struct opcode_t<2> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        // TODO: Calls subroutine
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.NNN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.NNN_is_valid();
    }
};

// opcode 3 : 3XNN
template <> struct opcode_t<3> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
        //Skips the next instruction if VX equals NN (usually the next instruction is a jump to skip a code block)
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.NN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid() 
                && (operands.NN_is_valid());
    }
};

// opcode 4 : 4XNN
template <> struct opcode_t<4> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
        //Skips the next instruction if VX does not equal NN (usually the next instruction is a jump to skip a code block)
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.NN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid() 
                && (operands.NN_is_valid());
    }
};

// opcode 5 : 5XY0
template <> struct opcode_t<5> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
        //Skips the next instruction if VX equals VY (usually the next instruction is a jump to skip a code block)
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.Y(inst);

        if(inst & 0x000F) {
            // TODO: N should be 0 here! if not report error or crash
        }
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid() 
                && (operands.Y_is_valid());
    }
};

// opcode 6 : 6XNN
template <> struct opcode_t<6> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO: Sets VX to NN
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.NN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.NN_is_valid();
    }
};

// opcode 7: 7XNN
template <> struct opcode_t<7> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO: Adds NN to VX (carry flag is not changed).
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.NN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.NN_is_valid();
    }
};

// opcode 8: 8XY0, 8XY1, 8XY2, 8XY3, 8XY4, 8XY5, 8XY6, 8XY7, 8XYE
template <> struct opcode_t<8> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.Y(inst);
        operands.N(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.Y_is_valid()
                && operands.N_is_valid();
    }
};

// opcode 9: 9XY0
template <> struct opcode_t<9> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.Y(inst);

        if(inst & 0x000F) {
            // TODO: N should be 0 here! if not report error or crash
        }
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.Y_is_valid();
    }
};

// opcode A: ANNN
template <> struct opcode_t<0xA> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.NNN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.NNN_is_valid();
    }
};

// opcode B: BNNN
template <> struct opcode_t<0xB> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.NNN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.NNN_is_valid();
    }
};

// opcode C: CXNN
template <> struct opcode_t<0xC> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.NN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.NN_is_valid();
    }
};

// opcode D: DXYN
template <> struct opcode_t<0xD> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.Y(inst);
        operands.N(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.Y_is_valid()
                && operands.N_is_valid();
    }
};

// opcode E: EX9E, EXA1
template <> struct opcode_t<0xE> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.NN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.Y_is_valid();
    }
};

// opcode F: FX07, FX0A, FX15, FX18, FX1E, FX29, FX33, FX55, FX65
template <> struct opcode_t<0xF> {
    public:
    // Member functions
    constexpr auto operator()(operands_t const& operands) -> void {
        execute(operands);
    }

    constexpr auto execute(operands_t const& operands) -> void {
        //TODO
    }

    // Static functions
    static const auto update_operands(std::uint16_t inst, operands_t& operands) -> void {
        operands.X(inst);
        operands.NN(inst);
    };

    [[nodiscard]] static const auto validate_operands(operands_t const& operands) -> bool {
        return operands.X_is_valid()
                && operands.NN_is_valid();
    }
};

}   // namespace chip8
