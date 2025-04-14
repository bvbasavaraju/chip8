#include "chip8/details/opcodes.hpp"
#include "chip8/details/operands.hpp"
#include "show_type.hpp"

#include <gtest/gtest.h>

#include <type_traits>

struct operations_t {
    struct call_t {
        static bool flag;
        static auto perform() -> void { flag = true; }
    };

    struct display_t {
        static bool clear_screen_flag;
        static auto clear_screen() -> void { clear_screen_flag = true; }
    };
    
    struct flow_t {
        static bool function_return_flag;
        static auto function_return() -> void { function_return_flag = true; }
    };

    struct invalid_t {
        static bool flag;
        static auto handle() -> void { flag = true; }
    };  

    // struct bcd_t;
    // struct assign_t;
    // struct bitwise_t;
    // struct conditional_t;
    // struct math_t;
    // struct mem_t;
    // struct rand_t;
    // struct timer_t;
};

bool operations_t::call_t::flag = false;
bool operations_t::display_t::clear_screen_flag = false;
bool operations_t::flow_t::function_return_flag = false;
bool operations_t::invalid_t::flag = false;

template <typename Opcode_t>
static auto decode_execute_validate(std::uint16_t inst, auto &flag) -> void {
    chip8::operands_t operands;
    Opcode_t::decode_operands(inst, operands);

    ASSERT_FALSE(flag);
    Opcode_t::template execute<operations_t>(operands);
    ASSERT_TRUE(flag);
    flag = false;
}

class opcodes_test : public ::testing::Test {
  protected:
    using op0 = chip8::opcode_t<0>;
    using op1 = chip8::opcode_t<1>;
    using op2 = chip8::opcode_t<2>;
    using op3 = chip8::opcode_t<3>;
    using op4 = chip8::opcode_t<4>;
    using op5 = chip8::opcode_t<5>;
    using op6 = chip8::opcode_t<6>;
    using op7 = chip8::opcode_t<7>;
    using op8 = chip8::opcode_t<8>;
    using op9 = chip8::opcode_t<9>;
    using opA = chip8::opcode_t<0xA>;
    using opB = chip8::opcode_t<0xB>;
    using opC = chip8::opcode_t<0xC>;
    using opD = chip8::opcode_t<0xD>;
    using opE = chip8::opcode_t<0xE>;
    using opF = chip8::opcode_t<0xF>;


    void SetUp() override {
        // Add Test setup code here!
    }

    void TearDown() override {
        // Add Test teardown code here!
    }
};

TEST_F(opcodes_test, opcode_0) {
    // 0x0NNN
    decode_execute_validate<op0>(0xFAB, operations_t::call_t::flag);
    decode_execute_validate<op0>(0x1E0, operations_t::call_t::flag);
    decode_execute_validate<op0>(0x234, operations_t::call_t::flag);
    decode_execute_validate<op0>(0x543, operations_t::call_t::flag);
    
    // 00E0
    decode_execute_validate<op0>(0xE0, operations_t::display_t::clear_screen_flag);
    
    // 00EE
    decode_execute_validate<op0>(0xEE, operations_t::flow_t::function_return_flag);

    // 0xNN - invalid
    decode_execute_validate<op0>(0x23, operations_t::invalid_t::flag);
    decode_execute_validate<op0>(0x99, operations_t::invalid_t::flag);
    decode_execute_validate<op0>(0xAA, operations_t::invalid_t::flag);
}
