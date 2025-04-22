#pragma once

#include <concepts>

// Call operation
template <typename T>
concept HasPerform = requires {
    { T::perform() };
};

template <typename T>
concept HasCallOperation = requires {
    typename T::call_t;
    requires HasPerform<typename T::call_t>;
};

// Display operation
template <typename T>
concept HasDisplayOperation = requires {
    typename T::display_t;
    { T::display_t::clear_screen() };
    { T::display_t::draw(std::uint8_t{}, std::uint8_t{}, std::uint8_t{})};
};

// Flow operation
template <typename T>
concept HasFlowOperation = requires {
    typename T::flow_t;
    { T::flow_t::function_return() };
    { T::flow_t::jump(std::uint16_t{}) };
    { T::flow_t::jump_with_offset(std::uint16_t{}) };
    { T::flow_t::function_call_at(std::uint16_t{}) };
};

// Conditional operation
template <typename T>
concept HasConditionalOperation = requires {
    typename T::conditional_t;
    { T::conditional_t::skip_if_reg_equal_to_val(std::uint8_t{}, std::uint8_t{}) };
    { T::conditional_t::skip_if_reg_not_equal_to_val(std::uint8_t{}, std::uint8_t{}) };
    { T::conditional_t::skip_if_reg_equal_to_reg(std::uint8_t{}, std::uint8_t{}) };
    { T::conditional_t::skip_if_reg_not_equal_to_reg(std::uint8_t{}, std::uint8_t{}) };
};

// Assignment operation
template <typename T>
concept HasAssignmentOperation = requires {
    typename T::assign_t;
    { T::assign_t::set_reg_to_val(std::uint8_t{}, std::uint8_t{}) };
    { T::assign_t::set_reg_to_reg(std::uint8_t{}, std::uint8_t{}) };
    { T::assign_t::set_reg_to_rand(std::uint8_t{}, std::uint8_t{}) };
};

// Math operation
template <typename T>
concept HasMathOperation = requires {
    typename T::math_t;
    { T::math_t::add_reg_with_val_with_carry(std::uint8_t{}, std::uint8_t{}) };
    { T::math_t::add_reg_with_val_without_carry(std::uint8_t{}, std::uint8_t{}) };
    { T::math_t::add_reg_with_reg_with_carry(std::uint8_t{}, std::uint8_t{}) };
    { T::math_t::add_reg_with_reg_without_carry(std::uint8_t{}, std::uint8_t{}) };
    { T::math_t::sub_reg_with_reg_with_carry(std::uint8_t{}, std::uint8_t{}) };
    { T::math_t::sub_reg_with_reg_with_carry2(std::uint8_t{}, std::uint8_t{}) };
};

// Bitwise Operation
template <typename T>
concept HasBitwiseOperation = requires {
    typename T::bitwise_t;
    { T::bitwise_t::or_op(std::uint8_t{}, std::uint8_t{}) };
    { T::bitwise_t::and_op(std::uint8_t{}, std::uint8_t{}) };
    { T::bitwise_t::xor_op(std::uint8_t{}, std::uint8_t{}) };
    { T::bitwise_t::right_shift(std::uint8_t{}, std::uint8_t{}) };
    { T::bitwise_t::left_shift(std::uint8_t{}, std::uint8_t{}) };
};

// Key Operation
template <typename T>
concept HasKeyOperation = requires {
    typename T::keyop_t;
    { T::keyop_t::skip_if_key_eq_to_reg(std::uint8_t{}) };
    { T::keyop_t::skip_if_key_not_eq_to_reg(std::uint8_t{}) };
    { T::keyop_t::read_key_stroke(std::uint8_t{}) };
};

// Mem Operation
template <typename T>
concept HasMemOperation = requires {
    typename T::mem_t;
    { T::mem_t::set_to_address(std::uint16_t{}) };
    { T::mem_t::add_reg(std::uint8_t{}) };
    { T::mem_t::set_to_sprite_char(std::uint8_t{}) };
    { T::mem_t::reg_dump(std::uint8_t{}) };
    { T::mem_t::reg_load(std::uint8_t{}) };
};

// Timer Operation
template <typename T>
concept HasTimerOperation = requires {
    typename T::timer_t;
    { T::timer_t::get_delay(std::uint8_t{}) };
    { T::timer_t::set_delay(std::uint8_t{}) };
    { T::timer_t::set_sound_timer(std::uint8_t{}) };
};

// BCD operation
template <typename T>
concept HasBcdOperation = requires {
    typename T::bcd_t;
    { T::bcd_t::set(std::uint8_t{}) };
};

// Invalid operation
template <typename T>
concept InvalidOperation = requires {
    typename T::invalid_t;
    { T::invalid_t::handle() };
};

template <typename T>
concept SupportsChip8Ops = requires {
    requires HasCallOperation<T>;
    requires HasDisplayOperation<T>;
    requires HasFlowOperation<T>;
    requires HasConditionalOperation<T>;
    requires HasAssignmentOperation<T>;
    requires HasMathOperation<T>;
    requires HasBitwiseOperation<T>;
    requires HasKeyOperation<T>;
    requires HasMemOperation<T>;
    requires HasTimerOperation<T>;
    requires HasBcdOperation<T>;
    requires InvalidOperation<T>;
};
