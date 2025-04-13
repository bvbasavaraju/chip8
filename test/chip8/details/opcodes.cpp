#include "chip8/details/opcodes.hpp"
#include "chip8/details/operands.hpp"
#include "show_type.hpp"

#include <gtest/gtest.h>

#include <type_traits>

struct operations_t {
    struct call_t {
        static uint32_t count;
        // auto operator()() -> void {
        //     count++;
        // };
        static auto perform() -> void {
            count++;
        }
    };

    // struct bcd_t;
    // struct assign_t;
    // struct bitwise_t;
    // struct conditional_t;
    // struct display_t;
    // struct flow_t;
    // struct math_t;
    // struct mem_t;
    // struct rand_t;
    // struct timer_t;
};

uint32_t operations_t::call_t::count = 0;

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
    static_assert(true);

    chip8::operands_t operands;
    op0::decode_operands(0xFE0, operands);
    ASSERT_TRUE(op0::validate_operands(operands));

    ASSERT_FALSE(operands.X_is_valid());
    ASSERT_FALSE(operands.Y_is_valid());
    ASSERT_FALSE(operands.N_is_valid());
    ASSERT_FALSE(operands.NN_is_valid());
    ASSERT_TRUE(operands.NNN_is_valid());

    ASSERT_TRUE(operations_t::call_t::count == 0);
    op0::execute<operations_t>(operands);
    ASSERT_TRUE(operations_t::call_t::count == 1);
}
