#include "chip8/details/opcodes.hpp"
#include "chip8/details/operands.hpp"
#include "show_type.hpp"

#include <gtest/gtest.h>

#include <type_traits>

struct ops_t {
    struct call_t {
        static bool flag;

        static auto perform() -> void { flag = true; }
    };

    struct display_t {
        static bool clear_screen_flag;

        static auto clear_screen() -> void { clear_screen_flag = true; }
    };
    
    struct flow_t {
        static bool jump_flag;
        static bool function_return_flag;
        static bool function_call_at_flag;

        static auto jump(std::uint16_t address) -> void { jump_flag = true; }
        static auto function_return() -> void { function_return_flag = true; }
        static auto function_call_at(std::uint16_t address) -> void { function_call_at_flag = true; }
    };

    struct invalid_t {
        static bool flag;

        static auto handle() -> void { flag = true; }
    };

    struct conditional_t {
        static bool skip_if_eq_to_val_flag;
        static bool skip_if_not_eq_to_val_flag;
        static bool skip_if_eq_to_reg_flag;
        static bool skip_if_not_eq_to_reg_flag;

        static auto skip_if_reg_equal_to_val(std::uint8_t x, std::uint8_t val) { skip_if_eq_to_val_flag = true; }
        static auto skip_if_reg_not_equal_to_val(std::uint8_t x, std::uint8_t val) { skip_if_not_eq_to_val_flag = true; }
        static auto skip_if_reg_equal_to_reg(std::uint8_t x, std::uint8_t y) { skip_if_eq_to_reg_flag = true; }
        static auto skip_if_reg_not_equal_to_reg(std::uint8_t x, std::uint8_t y) { skip_if_not_eq_to_reg_flag = true; }
    };

    struct assign_t {
        static bool set_reg_to_val_flag;
        static bool set_reg_to_reg_flag;

        static auto set_reg_to_val(std::uint8_t x, std::uint8_t val) { set_reg_to_val_flag = true; }
        static auto set_reg_to_reg(std::uint8_t x, std::uint8_t y) { set_reg_to_reg_flag = true; }
    };

    struct math_t {
        static bool add_reg_with_val_with_carry_flag;
        static bool add_reg_with_val_without_carry_flag;
        static bool add_reg_with_reg_with_carry_flag;
        static bool add_reg_with_reg_without_carry_flag;

        static auto add_reg_with_val_with_carry(std::uint8_t x, std::uint8_t val) { add_reg_with_val_with_carry_flag = true; }
        static auto add_reg_with_val_without_carry(std::uint8_t x, std::uint8_t val) { add_reg_with_val_without_carry_flag = true; }
        static auto add_reg_with_reg_with_carry(std::uint8_t x, std::uint8_t val) { add_reg_with_reg_with_carry_flag = true; }
        static auto add_reg_with_reg_without_carry(std::uint8_t x, std::uint8_t val) { add_reg_with_reg_without_carry_flag = true; }
    };

    // struct bcd_t;
    // struct assign_t;
    // struct bitwise_t;
    // struct math_t;
    // struct mem_t;
    // struct rand_t;
    // struct timer_t;
};

//initialize the flags 
bool ops_t::call_t::flag = false;
bool ops_t::display_t::clear_screen_flag = false;
bool ops_t::flow_t::jump_flag = false;
bool ops_t::flow_t::function_return_flag = false;
bool ops_t::flow_t::function_call_at_flag = false;
bool ops_t::invalid_t::flag = false;
bool ops_t::conditional_t::skip_if_eq_to_val_flag = false;
bool ops_t::conditional_t::skip_if_not_eq_to_val_flag = false;
bool ops_t::conditional_t::skip_if_eq_to_reg_flag = false;
bool ops_t::conditional_t::skip_if_not_eq_to_reg_flag = false;
bool ops_t::assign_t::set_reg_to_val_flag = false;
bool ops_t::assign_t::set_reg_to_reg_flag = false;
bool ops_t::math_t::add_reg_with_val_with_carry_flag = false;
bool ops_t::math_t::add_reg_with_val_without_carry_flag = false;
bool ops_t::math_t::add_reg_with_reg_with_carry_flag = false;
bool ops_t::math_t::add_reg_with_reg_without_carry_flag = false;

// decode and execute and validate
static auto decode_execute_and_validate(std::uint16_t inst, auto &flag, bool expected_decode_operands_status = true) -> void {
    std::uint8_t opcode = (inst & 0xF000) >> 12;

    ASSERT_FALSE(flag);

    chip8::operands_t operands;
    auto operand_work  = [&]<std::uint8_t op_val>() -> void {
        auto decode_status = chip8::opcode_t<op_val>::decode_operands(inst, operands);
        if(expected_decode_operands_status) {
            ASSERT_TRUE(decode_status);
        } else {
            ASSERT_FALSE(decode_status);
        }
        
        chip8::opcode_t<op_val>::template validate_operands_and_execute<ops_t>(operands);
    };

    switch (opcode)
    {
        case 0:
            operand_work.template operator()<0>();
            break;

        case 1:
            operand_work.template operator()<1>();
            break;

        case 2:
            operand_work.template operator()<2>();
            break;

        case 3:
            operand_work.template operator()<3>();
            break;

        case 4:
            operand_work.template operator()<4>();
            break;

        case 5:
            operand_work.template operator()<5>();
            break;

        case 6:
            operand_work.template operator()<6>();
            break;

        case 7:
            operand_work.template operator()<7>();
            break;

        case 8:
            operand_work.template operator()<8>();
            break;

        case 9:
            operand_work.template operator()<9>();
            break;

        case 0xA:
            operand_work.template operator()<0xA>();
            break;

        case 0xB:
            operand_work.template operator()<0xB>();
            break;
            

        case 0xC:
            operand_work.template operator()<0xC>();
            break;

        case 0xD:
            operand_work.template operator()<0xD>();
            break;

        case 0xE:
            operand_work.template operator()<0xE>();
            break;

        case 0xF:
            operand_work.template operator()<0xF>();
            break;
    
    default:
        break;
    }

    if (expected_decode_operands_status) {
        ASSERT_TRUE(flag);
    } else {
        ASSERT_TRUE(ops_t::invalid_t::flag);
        ops_t::invalid_t::flag = false;
    }
    
    flag = false;
}

class opcodes_test : public ::testing::Test {
  protected:
    void SetUp() override {
        // Add Test setup code here!
    }

    void TearDown() override {
        // Add Test teardown code here!
    }
};

TEST_F(opcodes_test, opcode_0) {
    // 0x0NNN
    decode_execute_and_validate(0xFAB, ops_t::call_t::flag);
    decode_execute_and_validate(0x1E0, ops_t::call_t::flag);
    decode_execute_and_validate(0x234, ops_t::call_t::flag);
    decode_execute_and_validate(0x543, ops_t::call_t::flag);
    
    // // 00E0
    decode_execute_and_validate(0xE0, ops_t::display_t::clear_screen_flag);
    
    // // 00EE
    decode_execute_and_validate(0xEE, ops_t::flow_t::function_return_flag);

    // // 0xNN - invalid
    decode_execute_and_validate(0x23, ops_t::invalid_t::flag);
    decode_execute_and_validate(0x99, ops_t::invalid_t::flag);
    decode_execute_and_validate(0xAA, ops_t::invalid_t::flag);
}

TEST_F(opcodes_test, opcode_1) {
    decode_execute_and_validate(0x1123, ops_t::flow_t::jump_flag);
    decode_execute_and_validate(0x1ABC, ops_t::flow_t::jump_flag);
    decode_execute_and_validate(0x1FEE, ops_t::flow_t::jump_flag);
    decode_execute_and_validate(0x1023, ops_t::flow_t::jump_flag);
}

TEST_F(opcodes_test, opcode_2) {
    decode_execute_and_validate(0x2123, ops_t::flow_t::function_call_at_flag);
    decode_execute_and_validate(0x2ABC, ops_t::flow_t::function_call_at_flag);
    decode_execute_and_validate(0x2FEE, ops_t::flow_t::function_call_at_flag);
    decode_execute_and_validate(0x2023, ops_t::flow_t::function_call_at_flag);
}

TEST_F(opcodes_test, opcode_3) {
    decode_execute_and_validate(0x3123, ops_t::conditional_t::skip_if_eq_to_val_flag);
    decode_execute_and_validate(0x3ABC, ops_t::conditional_t::skip_if_eq_to_val_flag);
    decode_execute_and_validate(0x3FEE, ops_t::conditional_t::skip_if_eq_to_val_flag);
    decode_execute_and_validate(0x3023, ops_t::conditional_t::skip_if_eq_to_val_flag);
}

TEST_F(opcodes_test, opcode_4) {
    decode_execute_and_validate(0x4123, ops_t::conditional_t::skip_if_not_eq_to_val_flag);
    decode_execute_and_validate(0x4ABC, ops_t::conditional_t::skip_if_not_eq_to_val_flag);
    decode_execute_and_validate(0x4FEE, ops_t::conditional_t::skip_if_not_eq_to_val_flag);
    decode_execute_and_validate(0x4023, ops_t::conditional_t::skip_if_not_eq_to_val_flag);
}

TEST_F(opcodes_test, opcode_5) {
    decode_execute_and_validate(0x5123, ops_t::conditional_t::skip_if_eq_to_reg_flag, false);
    decode_execute_and_validate(0x5ABC, ops_t::conditional_t::skip_if_eq_to_reg_flag, false);
    decode_execute_and_validate(0x5FEE, ops_t::conditional_t::skip_if_eq_to_reg_flag, false);
    decode_execute_and_validate(0x5023, ops_t::conditional_t::skip_if_eq_to_reg_flag, false);

    decode_execute_and_validate(0x5120, ops_t::conditional_t::skip_if_eq_to_reg_flag);
    decode_execute_and_validate(0x5AB0, ops_t::conditional_t::skip_if_eq_to_reg_flag);
    decode_execute_and_validate(0x5FE0, ops_t::conditional_t::skip_if_eq_to_reg_flag);
    decode_execute_and_validate(0x5020, ops_t::conditional_t::skip_if_eq_to_reg_flag);
}

TEST_F(opcodes_test, opcode_6) {
    decode_execute_and_validate(0x6123, ops_t::assign_t::set_reg_to_val_flag);
    decode_execute_and_validate(0x6ABC, ops_t::assign_t::set_reg_to_val_flag);
    decode_execute_and_validate(0x6FEE, ops_t::assign_t::set_reg_to_val_flag);
    decode_execute_and_validate(0x6023, ops_t::assign_t::set_reg_to_val_flag);
}

TEST_F(opcodes_test, opcode_7) {
    decode_execute_and_validate(0x7123, ops_t::math_t::add_reg_with_val_without_carry_flag);
    decode_execute_and_validate(0x7ABC, ops_t::math_t::add_reg_with_val_without_carry_flag);
    decode_execute_and_validate(0x7FEE, ops_t::math_t::add_reg_with_val_without_carry_flag);
    decode_execute_and_validate(0x7023, ops_t::math_t::add_reg_with_val_without_carry_flag);
}

TEST_F(opcodes_test, opcode_8) {
    // TODO
}

TEST_F(opcodes_test, opcode_9) {
    decode_execute_and_validate(0x9123, ops_t::conditional_t::skip_if_not_eq_to_reg_flag, false);
    decode_execute_and_validate(0x9ABC, ops_t::conditional_t::skip_if_not_eq_to_reg_flag, false);
    decode_execute_and_validate(0x9FEE, ops_t::conditional_t::skip_if_not_eq_to_reg_flag, false);
    decode_execute_and_validate(0x9023, ops_t::conditional_t::skip_if_not_eq_to_reg_flag, false);

    decode_execute_and_validate(0x9120, ops_t::conditional_t::skip_if_not_eq_to_reg_flag);
    decode_execute_and_validate(0x9AB0, ops_t::conditional_t::skip_if_not_eq_to_reg_flag);
    decode_execute_and_validate(0x9FE0, ops_t::conditional_t::skip_if_not_eq_to_reg_flag);
    decode_execute_and_validate(0x9020, ops_t::conditional_t::skip_if_not_eq_to_reg_flag);
}

TEST_F(opcodes_test, opcode_A) {
    // TODO
}

TEST_F(opcodes_test, opcode_B) {
    // TODO
}

TEST_F(opcodes_test, opcode_C) {
    // TODO
}

TEST_F(opcodes_test, opcode_D) {
    // TODO
}

TEST_F(opcodes_test, opcode_E) {
    // TODO
}

TEST_F(opcodes_test, opcode_F) {
    // TODO
}
