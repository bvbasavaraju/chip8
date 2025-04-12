#include "chip8/details/operands.hpp"
#include "show_type.hpp"

#include <gtest/gtest.h>

#include <type_traits>

template <typename opt, typename error_code>
constexpr static auto validate_op_type = [](auto construct_val, auto assignment_val, auto invalid_error_val) -> void {
    {
        opt op;
        ASSERT_TRUE(op() == error_code::val); // getting default value as error
        ASSERT_FALSE(op.is_valid());
        ASSERT_TRUE(op(invalid_error_val) == invalid_error_val); // assigning the error code
        
        op = assignment_val;
        ASSERT_TRUE(op() == assignment_val);
        ASSERT_TRUE(op.is_valid());
    }

    {
        opt op(construct_val);
        ASSERT_TRUE(op() == construct_val);
        ASSERT_TRUE(op.is_valid());
        ASSERT_TRUE(op(invalid_error_val) == construct_val);    // as it is valid, error code is ignored
        
        op = assignment_val;
        ASSERT_TRUE(op() == assignment_val);
        ASSERT_TRUE(op.is_valid());
    }
};

class operands_test : public ::testing::Test {
  protected:
    using u8_error_code = chip8::error_code_t<std::uint8_t>;
    using u16_error_code = chip8::error_code_t<std::uint16_t>;

    void SetUp() override {
        // Add Test setup code here!
    }

    void TearDown() override {
        // Add Test teardown code here!
    }
};

struct dummy_t{};

TEST_F(operands_test, error_code) {
    using i8_error_code = chip8::error_code_t<std::int8_t>;
    using i16_error_code = chip8::error_code_t<std::int16_t>;
    using i32_error_code = chip8::error_code_t<std::int32_t>;
    using u32_error_code = chip8::error_code_t<std::uint32_t>;
    using dummy_error_code = chip8::error_code_t<dummy_t>;

    //Verify the val
    static_assert(i8_error_code::val == 0xDEADC0DE);
    static_assert(u8_error_code::val == 0xFF);
    static_assert(i16_error_code::val == 0xDEADC0DE);
    static_assert(u16_error_code::val == 0xFFFF);
    static_assert(i32_error_code::val == 0xDEADC0DE);
    static_assert(u32_error_code::val == 0xDEADC0DE);
    static_assert(dummy_error_code::val == 0xDEADC0DE);

    //Verify the val type!
    static_assert(std::is_same_v<decltype(i8_error_code::val), const std::uint32_t>);
    static_assert(std::is_same_v<decltype(u8_error_code::val), const std::uint8_t>);

    static_assert(std::is_same_v<decltype(i16_error_code::val), const std::uint32_t>);
    static_assert(std::is_same_v<decltype(u16_error_code::val), const std::uint16_t>);

    static_assert(std::is_same_v<decltype(i32_error_code::val), const std::uint32_t>);
    static_assert(std::is_same_v<decltype(u32_error_code::val), const std::uint32_t>);

    static_assert(std::is_same_v<decltype(dummy_error_code::val), const std::uint32_t>);
}

TEST_F(operands_test, chip8_operand) {
    validate_op_type<chip8::X_t, u8_error_code>(76, 23, 1);
    validate_op_type<chip8::Y_t, u8_error_code>(21, 45, 2);
    validate_op_type<chip8::N_t, u8_error_code>(89, 67, 3);
    validate_op_type<chip8::NN_t, u8_error_code>(109, 87, 4);
    validate_op_type<chip8::NNN_t, u16_error_code>(0xDEAD, 290, 5);
}

TEST_F(operands_test, chip8_operands) {
    //No operands are provided!
    chip8::operands_t ops;
    ASSERT_FALSE(ops.X_is_valid());
    ASSERT_FALSE(ops.Y_is_valid());
    ASSERT_FALSE(ops.N_is_valid());
    ASSERT_FALSE(ops.NN_is_valid());
    ASSERT_FALSE(ops.NNN_is_valid());

    ASSERT_TRUE(ops.X() == u8_error_code::val);
    ASSERT_TRUE(ops.Y() == u8_error_code::val);
    ASSERT_TRUE(ops.N() == u8_error_code::val);
    ASSERT_TRUE(ops.NN() == u8_error_code::val);
    ASSERT_TRUE(ops.NNN() == u16_error_code::val);

    // X is provided!
    ops.X(0x1F23);
    ASSERT_TRUE(ops.X_is_valid());
    ASSERT_FALSE(ops.Y_is_valid());
    ASSERT_FALSE(ops.N_is_valid());
    ASSERT_FALSE(ops.NN_is_valid());
    ASSERT_FALSE(ops.NNN_is_valid());

    ASSERT_TRUE(ops.X() == 0xF);
    ASSERT_TRUE(ops.Y() == u8_error_code::val);
    ASSERT_TRUE(ops.N() == u8_error_code::val);
    ASSERT_TRUE(ops.NN() == u8_error_code::val);
    ASSERT_TRUE(ops.NNN() == u16_error_code::val);

    // Y is provided!
    ops.Y(0x1F23);
    ASSERT_TRUE(ops.X_is_valid());
    ASSERT_TRUE(ops.Y_is_valid());
    ASSERT_FALSE(ops.N_is_valid());
    ASSERT_FALSE(ops.NN_is_valid());
    ASSERT_FALSE(ops.NNN_is_valid());

    ASSERT_TRUE(ops.X() == 0xF);
    ASSERT_TRUE(ops.Y() == 0x2);
    ASSERT_TRUE(ops.N() == u8_error_code::val);
    ASSERT_TRUE(ops.NN() == u8_error_code::val);
    ASSERT_TRUE(ops.NNN() == u16_error_code::val);

    // N is provided!
    ops.N(0x1F23);
    ASSERT_TRUE(ops.X_is_valid());
    ASSERT_TRUE(ops.Y_is_valid());
    ASSERT_TRUE(ops.N_is_valid());
    ASSERT_FALSE(ops.NN_is_valid());
    ASSERT_FALSE(ops.NNN_is_valid());

    ASSERT_TRUE(ops.X() == 0xF);
    ASSERT_TRUE(ops.Y() == 0x2);
    ASSERT_TRUE(ops.N() == 0x3);
    ASSERT_TRUE(ops.NN() == u8_error_code::val);
    ASSERT_TRUE(ops.NNN() == u16_error_code::val);

    // NN is provided!
    ops.NN(0x1F23);
    ASSERT_TRUE(ops.X_is_valid());
    ASSERT_TRUE(ops.Y_is_valid());
    ASSERT_TRUE(ops.N_is_valid());
    ASSERT_TRUE(ops.NN_is_valid());
    ASSERT_FALSE(ops.NNN_is_valid());

    ASSERT_TRUE(ops.X() == 0xF);
    ASSERT_TRUE(ops.Y() == 0x2);
    ASSERT_TRUE(ops.N() == 0x3);
    ASSERT_TRUE(ops.NN() == 0x23);
    ASSERT_TRUE(ops.NNN() == u16_error_code::val);

    // NNN is provided!
    ops.NNN(0x1F23);
    ASSERT_TRUE(ops.X_is_valid());
    ASSERT_TRUE(ops.Y_is_valid());
    ASSERT_TRUE(ops.N_is_valid());
    ASSERT_TRUE(ops.NN_is_valid());
    ASSERT_TRUE(ops.NNN_is_valid());

    ASSERT_TRUE(ops.X() == 0xF);
    ASSERT_TRUE(ops.Y() == 0x2);
    ASSERT_TRUE(ops.N() == 0x3);
    ASSERT_TRUE(ops.NN() == 0x23);
    ASSERT_TRUE(ops.NNN() == 0x0F23);
}
