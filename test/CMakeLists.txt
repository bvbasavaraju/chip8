enable_testing()

set(CHIP8_TEST chip8_test)

add_executable(
    ${CHIP8_TEST} 
    chip8/details/instruction.cpp
    chip8/details/operands.cpp
    chip8/details/opcodes.cpp
    chip8/details/operations.cpp)

target_include_directories(
    ${CHIP8_TEST} 
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(
    ${CHIP8_TEST} 
    PUBLIC 
    GTest::gtest_main 
    chip8)

include(GoogleTest)

gtest_discover_tests(${CHIP8_TEST})
