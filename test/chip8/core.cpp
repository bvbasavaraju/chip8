#include "chip8/core.hpp"
#include "show_type.hpp"

#include "details/operations.hpp"

#include <gtest/gtest.h>

#include <type_traits>

class core_test : public ::testing::Test {
  protected:
    void SetUp() override {
        // Add Test setup code here!
    }

    void TearDown() override {
        // Add Test teardown code here!
    }
};

TEST_F(core_test, dummy) {
    ASSERT_TRUE(true);
}
