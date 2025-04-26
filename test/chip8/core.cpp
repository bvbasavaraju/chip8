#include "chip8/core.hpp"
#include "show_type.hpp"

#include "details/operations.hpp"

#include <gtest/gtest.h>

#include <tuple>
#include <type_traits>

using chip8_core_t = chip8::core_t<
                        ops_t::call_t,
                        ops_t::display_t,
                        ops_t::flow_t,
                        ops_t::conditional_t,
                        ops_t::assign_t,
                        ops_t::math_t,
                        ops_t::bitwise_t,
                        ops_t::keyop_t,
                        ops_t::mem_t,
                        ops_t::timer_t,
                        ops_t::bcd_t,
                        ops_t::invalid_t>;

class core_test : public ::testing::Test {
  protected:
    void SetUp() override {
    }

    void TearDown() override {
        // Add Test teardown code here!
    }
};

auto run = [](chip8::resources_t &res, chip8_core_t &c8_core, bool &flag, std::uint16_t inst) {
    ASSERT_TRUE(c8_core.load_instruction(inst));
    ASSERT_TRUE(res.read_instruction() == inst);    // verify the Ram entry

    // Reset the resources except ram for reuse of the instruction
    res.reset(false);

    auto inst_val = c8_core.fetch();
    ASSERT_TRUE(inst_val == inst);

    auto instruction = c8_core.decode(inst);
    c8_core.execute(instruction);

    // Validate the execution result
    if(!flag) {
        if(!ops_t::invalid_t::flag) {
            // even invalid is not triggered, then it is a error! Debug is needed!
            ASSERT_TRUE(false);
        } else {
            ASSERT_TRUE(ops_t::invalid_t::flag);
            ops_t::invalid_t::flag = false;
        }
    } else {
        ASSERT_TRUE(flag);
        flag = false;
    }

    // Reset all resources for following instructions
    res.reset(true);
};

template <std::uint16_t ... insts>
auto fetch_decode_execute(bool &flag) {
    chip8::resources_t res;
    chip8_core_t c8_core(res);
    (run(res, c8_core, flag, insts), ...);
}

TEST_F(core_test, empty_program_test) {
    chip8::resources_t res;
    chip8_core_t c8_core(res);
    run(res, c8_core, ops_t::call_t::flag, 0);
}

TEST_F(core_test, opcode_0) {
    fetch_decode_execute<0x123, 0x345, 0xFAB, 0x1E0, 0x234, 0x543>(ops_t::call_t::flag);
    fetch_decode_execute<0xE0, 0x23, 0x99, 0xAA>(ops_t::display_t::clear_screen_flag);
    fetch_decode_execute<0xEE, 0x23, 0x99, 0xAA>(ops_t::flow_t::function_return_flag);
}

TEST_F(core_test, opcode_1) {
    fetch_decode_execute<0x1123, 0x1ABC, 0x1FEE, 0x1023>(ops_t::flow_t::jump_flag);
}

TEST_F(core_test, opcode_2) {
    fetch_decode_execute<0x2123, 0x2ABC, 0x2FEE, 0x2023>(ops_t::flow_t::function_call_at_flag);
}

TEST_F(core_test, opcode_3) {
    fetch_decode_execute<0x3123, 0x3ABC, 0x3FEE, 0x3023>(ops_t::conditional_t::skip_if_eq_to_val_flag);
}

TEST_F(core_test, opcode_4) {
    fetch_decode_execute<0x4123, 0x4ABC, 0x4FEE, 0x4023>(ops_t::conditional_t::skip_if_not_eq_to_val_flag);
}

TEST_F(core_test, opcode_5) {
    fetch_decode_execute<0x5123, 0x5ABC, 0x5FEE, 0x5023, 0x5120, 0x5AB0, 0x5FE0, 0x5020>(ops_t::conditional_t::skip_if_eq_to_reg_flag);
}

TEST_F(core_test, opcode_6) {
    fetch_decode_execute<0x6123, 0x6ABC, 0x6FEE, 0x6023>(ops_t::assign_t::set_reg_to_val_flag);
}

TEST_F(core_test, opcode_7) {
    fetch_decode_execute<0x7123, 0x7ABC, 0x7FEE, 0x7023>(ops_t::math_t::add_reg_with_val_without_carry_flag);
}

TEST_F(core_test, opcode_8) {
    fetch_decode_execute<0x8120, 0x8AB0, 0x8FE0, 0x8020, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::assign_t::set_reg_to_reg_flag);
    fetch_decode_execute<0x8121, 0x8AB1, 0x8FE1, 0x8021, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::bitwise_t::or_flag);
    fetch_decode_execute<0x8122, 0x8AB2, 0x8FE2, 0x8022, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::bitwise_t::and_flag);
    fetch_decode_execute<0x8123, 0x8AB3, 0x8FE3, 0x8023, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::bitwise_t::xor_flag);
    fetch_decode_execute<0x8124, 0x8AB4, 0x8FE4, 0x8024, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::math_t::add_reg_with_reg_with_carry_flag);
    fetch_decode_execute<0x8125, 0x8AB5, 0x8FE5, 0x8025, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::math_t::sub_reg_with_reg_with_carry_flag);
    fetch_decode_execute<0x8126, 0x8AB6, 0x8FE6, 0x8026, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::bitwise_t::right_shift_flag);
    fetch_decode_execute<0x8127, 0x8AB7, 0x8FE7, 0x8027, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::math_t::sub_reg_with_reg_with_carry2_flag);
    fetch_decode_execute<0x812E, 0x8ABE, 0x8FEE, 0x802E, 0x8128, 0x8AB9, 0x8FEA, 0x802B, 0x802C, 0x802D, 0x802F>(ops_t::bitwise_t::left_shift_flag);
}

TEST_F(core_test, opcode_9) {
    fetch_decode_execute<0x9123, 0x9ABC, 0x9FEE, 0x9023, 0x9120, 0x9AB0, 0x9FE0, 0x9020>(ops_t::conditional_t::skip_if_not_eq_to_reg_flag);
}

TEST_F(core_test, opcode_A) {
    fetch_decode_execute<0xA123, 0xAABC, 0xAFEE, 0xA023>(ops_t::mem_t::set_to_address_flag);
}

TEST_F(core_test, opcode_B) {
    fetch_decode_execute<0xB123, 0xBABC, 0xBFEE, 0xB023>(ops_t::flow_t::jump_with_offset_flag);
}

TEST_F(core_test, opcode_C) {
    fetch_decode_execute<0xC123, 0xCABC, 0xCFEE, 0xC023>(ops_t::assign_t::set_reg_to_rand_flag);
}

TEST_F(core_test, opcode_D) {
    fetch_decode_execute<0xD123, 0xDABC, 0xDFEE, 0xD023>(ops_t::display_t::draw_flag);
}

TEST_F(core_test, opcode_E) {
    fetch_decode_execute<0xE19E, 0xEA9E, 0xEF9E, 0xE09E, 0xE123, 0xEABC, 0xEFEE, 0xE023>(ops_t::keyop_t::skip_if_key_eq_to_reg_flag);
    fetch_decode_execute<0xE1A1, 0xEAA1, 0xEFA1, 0xE0A1, 0xE123, 0xEABC, 0xEFEE, 0xE023>(ops_t::keyop_t::skip_if_key_not_eq_to_reg_flag);
}

TEST_F(core_test, opcode_F) {
    fetch_decode_execute<0xF107, 0xFA07, 0xFF07, 0xF007, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::timer_t::get_delay_flag);
    fetch_decode_execute<0xF10A, 0xFA0A, 0xFF0A, 0xF00A, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::keyop_t::read_key_stroke_flag);
    fetch_decode_execute<0xF115, 0xFA15, 0xFF15, 0xF015, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::timer_t::set_delay_flag);
    fetch_decode_execute<0xF118, 0xFA18, 0xFF18, 0xF018, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::timer_t::set_sound_timer_flag);
    fetch_decode_execute<0xF11E, 0xFA1E, 0xFF1E, 0xF01E, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::mem_t::add_reg_flag);
    fetch_decode_execute<0xF129, 0xFA29, 0xFF29, 0xF029, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::mem_t::set_to_sprite_char_flag);
    fetch_decode_execute<0xF133, 0xFA33, 0xFF33, 0xF033, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::bcd_t::flag);
    fetch_decode_execute<0xF155, 0xFA55, 0xFF55, 0xF055, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::mem_t::reg_dump_flag);
    fetch_decode_execute<0xF165, 0xFA65, 0xFF65, 0xF065, 0xF123, 0xFABC, 0xFFEE, 0xF073>(ops_t::mem_t::reg_load_flag);
}
