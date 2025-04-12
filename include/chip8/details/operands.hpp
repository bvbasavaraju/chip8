#pragma once

#include <cstdint>
#include <optional>

namespace chip8 {

// Error Code
template <typename T>
struct error_code_t {
    constexpr static auto val = 0xDEADC0DE;
};

template <> struct error_code_t<std::uint8_t> {
    constexpr static std::uint8_t val = 0xFF;
};

template <> struct error_code_t<std::uint16_t> {
    constexpr static std::uint16_t val = 0xFFFF;
};

// Operand
template <typename T>
struct operand_t {
    private:
    std::optional<T> op;

    public:
    operand_t(T val)
    : op(val) {}

    auto operator=(T val) {
        op = val;
    }

    [[nodiscard]] auto operator()(T error_code = error_code_t<T>::val) const -> T {
        return op.value_or(error_code);
    }

    [[nodiscard]] auto is_valid() const -> bool {
        return op.has_value();
    }
};

struct X_t : operand_t<uint8_t> {};
struct Y_t : operand_t<uint8_t> {};
struct N_t : operand_t<uint8_t> {};
struct NN_t : operand_t<uint8_t> {};
struct NNN_t : operand_t<uint16_t> {};

// Operands
struct operands_t {
private:
    std::optional<X_t> _X;
    std::optional<Y_t> _Y;
    std::optional<N_t> _N;
    std::optional<NN_t> _NN;
    std::optional<NNN_t> _NNN;

public:
    auto X(std::uint16_t inst) -> void {
        _X = {((inst & 0x0F00) >> 8)};
    }

    [[nodiscard]] auto X() const -> std::optional<X_t> {
        return _X;
    }

    [[nodiscard]] auto X_is_valid() const -> bool {
        return _X.has_value() && _X.value().is_valid();
    }

    auto Y(std::uint16_t inst) -> void {
        _Y = {((inst & 0x00F0) >> 4)};
    }

    [[nodiscard]] auto Y() const -> std::optional<Y_t> {
        return _Y;
    }

    [[nodiscard]] auto Y_is_valid() const -> bool {
        return _Y.has_value() && _Y.value().is_valid();
    }

    auto N(std::uint16_t inst) -> void {
        _N = {inst & 0x000F};
    }

    [[nodiscard]] auto N() const -> std::optional<N_t> {
        return _N;
    }

    [[nodiscard]] auto N_is_valid() const -> bool {
        return _N.has_value() && _N.value().is_valid();
    }

    auto NN(std::uint16_t inst) -> void {
        _NN = {inst & 0x00FF};
    }

    [[nodiscard]] auto NN() const -> std::optional<NN_t> {
        return _NN;
    }

    [[nodiscard]] auto NN_is_valid() const -> bool {
        return _NN.has_value() && _NN.value().is_valid();
    }

    auto NNN(std::uint16_t inst) -> void {
        _NNN = {inst & 0x0FFF};
    }

    [[nodiscard]] auto NNN() const -> std::optional<NNN_t> {
        return _NNN;
    }

    [[nodiscard]] auto NNN_is_valid() const -> bool {
        return _NNN.has_value() && _NNN.value().is_valid();
    }
};
}   // chip8
