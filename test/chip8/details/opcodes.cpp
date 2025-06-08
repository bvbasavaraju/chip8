#include "chip8/details/opcodes.hpp"
#include "chip8/details/operands.hpp"
#include "show_type.hpp"

#include "ops.hpp"

#include <gtest/gtest.h>

#include <type_traits>

// decode and execute and validate
static auto decode_execute_and_validate(std::uint16_t inst, auto &flag, bool expected_decode_operands_status = true) -> void {
    std::uint8_t opcode = (inst & 0xF000) >> 12;

    ASSERT_FALSE(flag);

    ops_t ops;
    chip8::operands_t operands;
    auto operand_work  = [&]<std::uint8_t op_val>() -> void {
        auto decode_status = chip8::opcode_t<op_val>::decode_operands(inst, operands);
        if(expected_decode_operands_status) {
            ASSERT_TRUE(decode_status);
        } else {
            ASSERT_FALSE(decode_status);
        }
        
        chip8::opcode_t<op_val>::template validate_operands_and_execute(operands, ops);
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
    
    // 00E0
    decode_execute_and_validate(0xE0, ops_t::display_t::clear_screen_flag);
    
    // 00EE
    decode_execute_and_validate(0xEE, ops_t::flow_t::function_return_flag);

    // 0xNN - invalid
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
    decode_execute_and_validate(0x8120, ops_t::assign_t::set_reg_to_reg_flag);
    decode_execute_and_validate(0x8AB0, ops_t::assign_t::set_reg_to_reg_flag);
    decode_execute_and_validate(0x8FE0, ops_t::assign_t::set_reg_to_reg_flag);
    decode_execute_and_validate(0x8020, ops_t::assign_t::set_reg_to_reg_flag);

    decode_execute_and_validate(0x8121, ops_t::bitwise_t::or_flag);
    decode_execute_and_validate(0x8AB1, ops_t::bitwise_t::or_flag);
    decode_execute_and_validate(0x8FE1, ops_t::bitwise_t::or_flag);
    decode_execute_and_validate(0x8021, ops_t::bitwise_t::or_flag);

    decode_execute_and_validate(0x8122, ops_t::bitwise_t::and_flag);
    decode_execute_and_validate(0x8AB2, ops_t::bitwise_t::and_flag);
    decode_execute_and_validate(0x8FE2, ops_t::bitwise_t::and_flag);
    decode_execute_and_validate(0x8022, ops_t::bitwise_t::and_flag);

    decode_execute_and_validate(0x8123, ops_t::bitwise_t::xor_flag);
    decode_execute_and_validate(0x8AB3, ops_t::bitwise_t::xor_flag);
    decode_execute_and_validate(0x8FE3, ops_t::bitwise_t::xor_flag);
    decode_execute_and_validate(0x8023, ops_t::bitwise_t::xor_flag);

    decode_execute_and_validate(0x8124, ops_t::math_t::add_reg_with_reg_with_carry_flag);
    decode_execute_and_validate(0x8AB4, ops_t::math_t::add_reg_with_reg_with_carry_flag);
    decode_execute_and_validate(0x8FE4, ops_t::math_t::add_reg_with_reg_with_carry_flag);
    decode_execute_and_validate(0x8024, ops_t::math_t::add_reg_with_reg_with_carry_flag);

    decode_execute_and_validate(0x8125, ops_t::math_t::sub_reg_with_reg_with_carry_flag);
    decode_execute_and_validate(0x8AB5, ops_t::math_t::sub_reg_with_reg_with_carry_flag);
    decode_execute_and_validate(0x8FE5, ops_t::math_t::sub_reg_with_reg_with_carry_flag);
    decode_execute_and_validate(0x8025, ops_t::math_t::sub_reg_with_reg_with_carry_flag);

    decode_execute_and_validate(0x8126, ops_t::bitwise_t::right_shift_flag);
    decode_execute_and_validate(0x8AB6, ops_t::bitwise_t::right_shift_flag);
    decode_execute_and_validate(0x8FE6, ops_t::bitwise_t::right_shift_flag);
    decode_execute_and_validate(0x8026, ops_t::bitwise_t::right_shift_flag);

    decode_execute_and_validate(0x8127, ops_t::math_t::sub_reg_with_reg_with_carry2_flag);
    decode_execute_and_validate(0x8AB7, ops_t::math_t::sub_reg_with_reg_with_carry2_flag);
    decode_execute_and_validate(0x8FE7, ops_t::math_t::sub_reg_with_reg_with_carry2_flag);
    decode_execute_and_validate(0x8027, ops_t::math_t::sub_reg_with_reg_with_carry2_flag);

    decode_execute_and_validate(0x812E, ops_t::bitwise_t::left_shift_flag);
    decode_execute_and_validate(0x8ABE, ops_t::bitwise_t::left_shift_flag);
    decode_execute_and_validate(0x8FEE, ops_t::bitwise_t::left_shift_flag);
    decode_execute_and_validate(0x802E, ops_t::bitwise_t::left_shift_flag);

    decode_execute_and_validate(0x8128, ops_t::invalid_t::flag);
    decode_execute_and_validate(0x8AB9, ops_t::invalid_t::flag);
    decode_execute_and_validate(0x8FEA, ops_t::invalid_t::flag);
    decode_execute_and_validate(0x802B, ops_t::invalid_t::flag);
    decode_execute_and_validate(0x802C, ops_t::invalid_t::flag);
    decode_execute_and_validate(0x802D, ops_t::invalid_t::flag);
    decode_execute_and_validate(0x802F, ops_t::invalid_t::flag);
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
    decode_execute_and_validate(0xA123, ops_t::mem_t::set_to_address_flag);
    decode_execute_and_validate(0xAABC, ops_t::mem_t::set_to_address_flag);
    decode_execute_and_validate(0xAFEE, ops_t::mem_t::set_to_address_flag);
    decode_execute_and_validate(0xA023, ops_t::mem_t::set_to_address_flag);
}

TEST_F(opcodes_test, opcode_B) {
    decode_execute_and_validate(0xB123, ops_t::flow_t::jump_with_offset_flag);
    decode_execute_and_validate(0xBABC, ops_t::flow_t::jump_with_offset_flag);
    decode_execute_and_validate(0xBFEE, ops_t::flow_t::jump_with_offset_flag);
    decode_execute_and_validate(0xB023, ops_t::flow_t::jump_with_offset_flag);
}

TEST_F(opcodes_test, opcode_C) {
    decode_execute_and_validate(0xC123, ops_t::assign_t::set_reg_to_rand_flag);
    decode_execute_and_validate(0xCABC, ops_t::assign_t::set_reg_to_rand_flag);
    decode_execute_and_validate(0xCFEE, ops_t::assign_t::set_reg_to_rand_flag);
    decode_execute_and_validate(0xC023, ops_t::assign_t::set_reg_to_rand_flag);
}

TEST_F(opcodes_test, opcode_D) {
    decode_execute_and_validate(0xD123, ops_t::display_t::draw_flag);
    decode_execute_and_validate(0xDABC, ops_t::display_t::draw_flag);
    decode_execute_and_validate(0xDFEE, ops_t::display_t::draw_flag);
    decode_execute_and_validate(0xD023, ops_t::display_t::draw_flag);
}

TEST_F(opcodes_test, opcode_E) {
    decode_execute_and_validate(0xE19E, ops_t::keyop_t::skip_if_key_eq_to_reg_flag);
    decode_execute_and_validate(0xEA9E, ops_t::keyop_t::skip_if_key_eq_to_reg_flag);
    decode_execute_and_validate(0xEF9E, ops_t::keyop_t::skip_if_key_eq_to_reg_flag);
    decode_execute_and_validate(0xE09E, ops_t::keyop_t::skip_if_key_eq_to_reg_flag);

    decode_execute_and_validate(0xE1A1, ops_t::keyop_t::skip_if_key_not_eq_to_reg_flag);
    decode_execute_and_validate(0xEAA1, ops_t::keyop_t::skip_if_key_not_eq_to_reg_flag);
    decode_execute_and_validate(0xEFA1, ops_t::keyop_t::skip_if_key_not_eq_to_reg_flag);
    decode_execute_and_validate(0xE0A1, ops_t::keyop_t::skip_if_key_not_eq_to_reg_flag);

    decode_execute_and_validate(0xE123, ops_t::invalid_t::flag);
    decode_execute_and_validate(0xEABC, ops_t::invalid_t::flag);
    decode_execute_and_validate(0xEFEE, ops_t::invalid_t::flag);
    decode_execute_and_validate(0xE023, ops_t::invalid_t::flag);
}

TEST_F(opcodes_test, opcode_F) {
    decode_execute_and_validate(0xF107, ops_t::timer_t::get_delay_flag);
    decode_execute_and_validate(0xFA07, ops_t::timer_t::get_delay_flag);
    decode_execute_and_validate(0xFF07, ops_t::timer_t::get_delay_flag);
    decode_execute_and_validate(0xF007, ops_t::timer_t::get_delay_flag);

    decode_execute_and_validate(0xF10A, ops_t::keyop_t::read_key_stroke_flag);
    decode_execute_and_validate(0xFA0A, ops_t::keyop_t::read_key_stroke_flag);
    decode_execute_and_validate(0xFF0A, ops_t::keyop_t::read_key_stroke_flag);
    decode_execute_and_validate(0xF00A, ops_t::keyop_t::read_key_stroke_flag);

    decode_execute_and_validate(0xF115, ops_t::timer_t::set_delay_flag);
    decode_execute_and_validate(0xFA15, ops_t::timer_t::set_delay_flag);
    decode_execute_and_validate(0xFF15, ops_t::timer_t::set_delay_flag);
    decode_execute_and_validate(0xF015, ops_t::timer_t::set_delay_flag);

    decode_execute_and_validate(0xF118, ops_t::timer_t::set_sound_timer_flag);
    decode_execute_and_validate(0xFA18, ops_t::timer_t::set_sound_timer_flag);
    decode_execute_and_validate(0xFF18, ops_t::timer_t::set_sound_timer_flag);
    decode_execute_and_validate(0xF018, ops_t::timer_t::set_sound_timer_flag);

    decode_execute_and_validate(0xF11E, ops_t::mem_t::add_reg_flag);
    decode_execute_and_validate(0xFA1E, ops_t::mem_t::add_reg_flag);
    decode_execute_and_validate(0xFF1E, ops_t::mem_t::add_reg_flag);
    decode_execute_and_validate(0xF01E, ops_t::mem_t::add_reg_flag);

    decode_execute_and_validate(0xF129, ops_t::mem_t::set_to_sprite_char_flag);
    decode_execute_and_validate(0xFA29, ops_t::mem_t::set_to_sprite_char_flag);
    decode_execute_and_validate(0xFF29, ops_t::mem_t::set_to_sprite_char_flag);
    decode_execute_and_validate(0xF029, ops_t::mem_t::set_to_sprite_char_flag);

    decode_execute_and_validate(0xF133, ops_t::bcd_t::flag);
    decode_execute_and_validate(0xFA33, ops_t::bcd_t::flag);
    decode_execute_and_validate(0xFF33, ops_t::bcd_t::flag);
    decode_execute_and_validate(0xF033, ops_t::bcd_t::flag);

    decode_execute_and_validate(0xF155, ops_t::mem_t::reg_dump_flag);
    decode_execute_and_validate(0xFA55, ops_t::mem_t::reg_dump_flag);
    decode_execute_and_validate(0xFF55, ops_t::mem_t::reg_dump_flag);
    decode_execute_and_validate(0xF055, ops_t::mem_t::reg_dump_flag);

    decode_execute_and_validate(0xF165, ops_t::mem_t::reg_load_flag);
    decode_execute_and_validate(0xFA65, ops_t::mem_t::reg_load_flag);
    decode_execute_and_validate(0xFF65, ops_t::mem_t::reg_load_flag);
    decode_execute_and_validate(0xF065, ops_t::mem_t::reg_load_flag);

    decode_execute_and_validate(0xF123, ops_t::invalid_t::flag);
    decode_execute_and_validate(0xFABC, ops_t::invalid_t::flag);
    decode_execute_and_validate(0xFFEE, ops_t::invalid_t::flag);
    decode_execute_and_validate(0xF073, ops_t::invalid_t::flag);
}
