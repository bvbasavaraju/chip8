
#include <cstdint>
#include "operations.hpp"

//initialize the flags 
bool ops_t::call_t::flag = false;
bool ops_t::display_t::clear_screen_flag = false;
bool ops_t::display_t::draw_flag = false;
bool ops_t::flow_t::jump_flag = false;
bool ops_t::flow_t::jump_with_offset_flag = false;
bool ops_t::flow_t::function_return_flag = false;
bool ops_t::flow_t::function_call_at_flag = false;
bool ops_t::invalid_t::flag = false;
bool ops_t::conditional_t::skip_if_eq_to_val_flag = false;
bool ops_t::conditional_t::skip_if_not_eq_to_val_flag = false;
bool ops_t::conditional_t::skip_if_eq_to_reg_flag = false;
bool ops_t::conditional_t::skip_if_not_eq_to_reg_flag = false;
bool ops_t::assign_t::set_reg_to_val_flag = false;
bool ops_t::assign_t::set_reg_to_reg_flag = false;
bool ops_t::assign_t::set_reg_to_rand_flag = false;
bool ops_t::math_t::add_reg_with_val_with_carry_flag = false;
bool ops_t::math_t::add_reg_with_val_without_carry_flag = false;
bool ops_t::math_t::add_reg_with_reg_with_carry_flag = false;
bool ops_t::math_t::add_reg_with_reg_without_carry_flag = false;
bool ops_t::math_t::sub_reg_with_reg_with_carry_flag = false;
bool ops_t::math_t::sub_reg_with_reg_with_carry2_flag = false;
bool ops_t::bitwise_t::or_flag = false;
bool ops_t::bitwise_t::and_flag = false;
bool ops_t::bitwise_t::xor_flag = false;
bool ops_t::bitwise_t::right_shift_flag = false;
bool ops_t::bitwise_t::left_shift_flag = false;
bool ops_t::keyop_t::skip_if_key_eq_to_reg_flag = false;
bool ops_t::keyop_t::skip_if_key_not_eq_to_reg_flag = false;
bool ops_t::keyop_t::read_key_stroke_flag = false;
bool ops_t::mem_t::set_to_address_flag = false;
bool ops_t::mem_t::add_reg_flag = false;
bool ops_t::mem_t::set_to_sprite_char_flag = false;
bool ops_t::mem_t::reg_dump_flag = false;
bool ops_t::mem_t::reg_load_flag = false;
bool ops_t::timer_t::get_delay_flag = false;
bool ops_t::timer_t::set_delay_flag = false;
bool ops_t::timer_t::set_sound_timer_flag = false;
bool ops_t::bcd_t::flag = false;
