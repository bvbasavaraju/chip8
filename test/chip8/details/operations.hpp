#pragma once

struct ops_t {
    struct call_t {
        static bool flag;

        static auto perform() -> void { flag = true; }
    };

    struct display_t {
        static bool clear_screen_flag;
        static bool draw_flag;

        static auto clear_screen() -> void { clear_screen_flag = true; }
        static auto draw(std::uint8_t pos_x, std::uint8_t pos_y, std::uint8_t height) -> void { draw_flag = true; }
    };
    
    struct flow_t {
        static bool jump_flag;
        static bool jump_with_offset_flag;
        static bool function_return_flag;
        static bool function_call_at_flag;

        static auto jump(std::uint16_t address) -> void { jump_flag = true; }
        static auto jump_with_offset(std::uint16_t address) -> void { jump_with_offset_flag = true; }
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
        static bool set_reg_to_rand_flag;

        static auto set_reg_to_val(std::uint8_t x, std::uint8_t val) { set_reg_to_val_flag = true; }
        static auto set_reg_to_reg(std::uint8_t x, std::uint8_t y) { set_reg_to_reg_flag = true; }
        static auto set_reg_to_rand(std::uint8_t x, std::uint8_t mask) { set_reg_to_rand_flag = true; }
    };

    struct math_t {
        static bool add_reg_with_val_with_carry_flag;
        static bool add_reg_with_val_without_carry_flag;
        static bool add_reg_with_reg_with_carry_flag;
        static bool add_reg_with_reg_without_carry_flag;
        static bool sub_reg_with_reg_with_carry_flag;
        static bool sub_reg_with_reg_with_carry2_flag;

        static auto add_reg_with_val_with_carry(std::uint8_t x, std::uint8_t val) { add_reg_with_val_with_carry_flag = true; }
        static auto add_reg_with_val_without_carry(std::uint8_t x, std::uint8_t val) { add_reg_with_val_without_carry_flag = true; }
        static auto add_reg_with_reg_with_carry(std::uint8_t x, std::uint8_t val) { add_reg_with_reg_with_carry_flag = true; }
        static auto add_reg_with_reg_without_carry(std::uint8_t x, std::uint8_t val) { add_reg_with_reg_without_carry_flag = true; }
        static auto sub_reg_with_reg_with_carry(std::uint8_t x, std::uint8_t val) { sub_reg_with_reg_with_carry_flag = true; }
        static auto sub_reg_with_reg_with_carry2(std::uint8_t x, std::uint8_t val) { sub_reg_with_reg_with_carry2_flag = true; }
    };

    struct bitwise_t {
        static bool or_flag;
        static bool and_flag;
        static bool xor_flag;
        static bool right_shift_flag;
        static bool left_shift_flag;

        static auto or_op(std::uint8_t x, std::uint8_t y) { or_flag = true; }
        static auto and_op(std::uint8_t x, std::uint8_t y) { and_flag = true; }
        static auto xor_op(std::uint8_t x, std::uint8_t y) { xor_flag = true; }
        static auto right_shift(std::uint8_t x, std::uint8_t y) { right_shift_flag = true; }
        static auto left_shift(std::uint8_t x, std::uint8_t y) { left_shift_flag = true; }
    };

    struct keyop_t {
        static bool skip_if_key_eq_to_reg_flag;
        static bool skip_if_key_not_eq_to_reg_flag;
        static bool read_key_stroke_flag;

        static auto skip_if_key_eq_to_reg(std::uint8_t x) { skip_if_key_eq_to_reg_flag = true; }
        static auto skip_if_key_not_eq_to_reg(std::uint8_t x) { skip_if_key_not_eq_to_reg_flag = true; }
        static auto read_key_stroke(std::uint8_t x) { read_key_stroke_flag = true; }
    };

    struct mem_t {
        static bool set_to_address_flag;
        static bool add_reg_flag;
        static bool set_to_sprite_char_flag;
        static bool reg_dump_flag;
        static bool reg_load_flag;

        static auto set_to_address(std::uint16_t address) { set_to_address_flag = true; }
        static auto add_reg(std::uint8_t x) { add_reg_flag = true; }
        static auto set_to_sprite_char(std::uint8_t x) { set_to_sprite_char_flag = true; }
        static auto reg_dump(std::uint8_t x) { reg_dump_flag = true; }
        static auto reg_load(std::uint8_t x) { reg_load_flag = true; }
    };

    struct timer_t {
        static bool get_delay_flag;
        static bool set_delay_flag;
        static bool set_sound_timer_flag;

        static auto get_delay(std::uint8_t x) { get_delay_flag = true; }
        static auto set_delay(std::uint8_t x) { set_delay_flag = true; }
        static auto set_sound_timer(std::uint8_t x) { set_sound_timer_flag = true; }
    };

    struct bcd_t {
        static bool flag;

        static auto set(std::uint8_t x) { flag = true; }
    };

    call_t call;
    display_t display;
    flow_t flow;
    conditional_t conditional;
    assign_t assign;
    math_t math;
    bitwise_t bitwise;
    keyop_t keyop;
    mem_t mem;
    timer_t timer;
    bcd_t bcd;
    invalid_t invalid;
};
