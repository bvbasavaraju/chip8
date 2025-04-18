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
};

// Flow operation
template <typename T>
concept HasFlowOperation = requires {
    typename T::flow_t;
    { T::flow_t::function_return() };
    { T::flow_t::jump(std::uint16_t{}) };
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
};

// Math operation
template <typename T>
concept HasMathOperation = requires {
    typename T::math_t;
    { T::math_t::add_reg_with_val_with_carry(std::uint8_t{}, std::uint8_t{}) };
    { T::math_t::add_reg_with_val_without_carry(std::uint8_t{}, std::uint8_t{}) };
    { T::math_t::add_reg_with_reg_with_carry(std::uint8_t{}, std::uint8_t{}) };
    { T::math_t::add_reg_with_reg_without_carry(std::uint8_t{}, std::uint8_t{}) };
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
    requires InvalidOperation<T>;


    //  TODO
    // typename T::assign_t;
    // typename T::bcd_t;
    // typename T::bitwise_t;
    // typename T::math_t;
    // typename T::mem_t;
    // typename T::rand_t;
    // typename T::timer_t;
};
