#pragma once

#include "details/resources.hpp"

#include <concepts>
#include <memory>

// Has resources
// TODO: needed/every operation should have API called resources, so that resources can be passed in!!
template <typename T>
concept HasResources = requires(T t) {
    { t.resources(std::shared_ptr<chip8::resources_t>{}) } ;
};

// Call operation
template <typename T>
concept HasCallOperation = requires(T t) {
    { t.call };
    { t.call.perform() };
};

// Display operation
template <typename T>
concept HasDisplayOperation = requires(T t) {
    { t.display };
    { t.display.clear_screen() };
    { t.display.draw(std::uint8_t{}, std::uint8_t{}, std::uint8_t{})};
};

// Flow operation
template <typename T>
concept HasFlowOperation = requires(T t) {
    { t.flow };
    { t.flow.function_return() };
    { t.flow.jump(std::uint16_t{}) };
    { t.flow.jump_with_offset(std::uint16_t{}) };
    { t.flow.function_call_at(std::uint16_t{}) };
};

// Conditional operation
template <typename T>
concept HasConditionalOperation = requires(T t) {
    { t.conditional };
    { t.conditional.skip_if_reg_equal_to_val(std::uint8_t{}, std::uint8_t{}) };
    { t.conditional.skip_if_reg_not_equal_to_val(std::uint8_t{}, std::uint8_t{}) };
    { t.conditional.skip_if_reg_equal_to_reg(std::uint8_t{}, std::uint8_t{}) };
    { t.conditional.skip_if_reg_not_equal_to_reg(std::uint8_t{}, std::uint8_t{}) };
};

// Assignment operation
template <typename T>
concept HasAssignmentOperation = requires(T t) {
    { t.assign };
    { t.assign.set_reg_to_val(std::uint8_t{}, std::uint8_t{}) };
    { t.assign.set_reg_to_reg(std::uint8_t{}, std::uint8_t{}) };
    { t.assign.set_reg_to_rand(std::uint8_t{}, std::uint8_t{}) };
};

// Math operation
template <typename T>
concept HasMathOperation = requires(T t) {
    { t.math };
    { t.math.add_reg_with_val_with_carry(std::uint8_t{}, std::uint8_t{}) };
    { t.math.add_reg_with_val_without_carry(std::uint8_t{}, std::uint8_t{}) };
    { t.math.add_reg_with_reg_with_carry(std::uint8_t{}, std::uint8_t{}) };
    { t.math.add_reg_with_reg_without_carry(std::uint8_t{}, std::uint8_t{}) };
    { t.math.sub_reg_with_reg_with_carry(std::uint8_t{}, std::uint8_t{}) };
    { t.math.sub_reg_with_reg_with_carry2(std::uint8_t{}, std::uint8_t{}) };
};

// Bitwise Operation
template <typename T>
concept HasBitwiseOperation = requires(T t) {
    { t.bitwise };
    { t.bitwise.or_op(std::uint8_t{}, std::uint8_t{}) };
    { t.bitwise.and_op(std::uint8_t{}, std::uint8_t{}) };
    { t.bitwise.xor_op(std::uint8_t{}, std::uint8_t{}) };
    { t.bitwise.right_shift(std::uint8_t{}, std::uint8_t{}) };
    { t.bitwise.left_shift(std::uint8_t{}, std::uint8_t{}) };
};

// Key Operation
template <typename T>
concept HasKeyOperation = requires(T t) {
    { t.keyop };
    { t.keyop.skip_if_key_eq_to_reg(std::uint8_t{}) };
    { t.keyop.skip_if_key_not_eq_to_reg(std::uint8_t{}) };
    { t.keyop.read_key_stroke(std::uint8_t{}) };
};

// Mem Operation
template <typename T>
concept HasMemOperation = requires(T t) {
    { t.mem };
    { t.mem.set_to_address(std::uint16_t{}) };
    { t.mem.add_reg(std::uint8_t{}) };
    { t.mem.set_to_sprite_char(std::uint8_t{}) };
    { t.mem.reg_dump(std::uint8_t{}) };
    { t.mem.reg_load(std::uint8_t{}) };
};

// Timer Operation
template <typename T>
concept HasTimerOperation = requires(T t) {
    { t.timer };
    { t.timer.get_delay(std::uint8_t{}) };
    { t.timer.set_delay(std::uint8_t{}) };
    { t.timer.set_sound_timer(std::uint8_t{}) };
};

// BCD operation
template <typename T>
concept HasBcdOperation = requires(T t) {
    { t.bcd };
    { t.bcd.set(std::uint8_t{}) };
};

// Invalid operation
template <typename T>
concept InvalidOperation = requires(T t) {
    { t.invalid };
    { t.invalid.handle() };
};

template <typename T>
concept SupportsChip8Ops = requires {
    requires HasResources<T>;
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
