#include "chip8/details/operands.hpp"
#include "show_type.hpp"

#include <gtest/gtest.h>

#include <type_traits>

class operands_test : public ::testing::Test {
  protected:
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
    using u8_error_code = chip8::error_code_t<std::uint8_t>;
    using i16_error_code = chip8::error_code_t<std::int16_t>;
    using u16_error_code = chip8::error_code_t<std::uint16_t>;
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
