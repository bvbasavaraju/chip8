#pragma once

#include <cstdint>
#include <optional>
#include <vector>
#include <algorithm>

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

    auto is_acceptable(std::optional<std::vector<T>> acceptable_values) const -> bool {
        if (!acceptable_values.has_value()) {
            return true;
        }
        

        T val = op.value();
        return std::any_of(acceptable_values.value().begin(), acceptable_values.value().end(), 
            [val](T acceptable_val) -> bool {
                return (val == acceptable_val);
            });
    };

    public:
    operand_t() {}

    operand_t(T val)
    : op(val) {}

    auto operator=(T val) -> void {
        op = val;
    }

    [[nodiscard]] auto operator()(T error_code = error_code_t<T>::val) const -> T {
        return op.value_or(error_code);
    }

    [[nodiscard]] auto is_valid(std::optional<std::vector<T>> acceptable_values = {}) const -> bool {
        return (op.has_value() &&  is_acceptable(acceptable_values));
    }
};

using X_t = operand_t<uint8_t>;
using Y_t = operand_t<uint8_t>;
using N_t = operand_t<uint8_t>;
using NN_t = operand_t<uint8_t>;
using NNN_t = operand_t<uint16_t>;

// Operands
struct operands_t {
private:
    using u8_acceptable_t = std::optional<std::vector<std::uint8_t>>;
    using u16_acceptable_t = std::optional<std::vector<std::uint16_t>>;

    std::optional<X_t> _X;
    std::optional<Y_t> _Y;
    std::optional<N_t> _N;
    std::optional<NN_t> _NN;
    std::optional<NNN_t> _NNN;

public:
    auto X(std::uint16_t inst) -> void {
        _X = {((inst & 0x0F00) >> 8)};
    }

    [[nodiscard]] auto X() const -> std::uint8_t {
        return _X.value_or(X_t{})();
    }

    [[nodiscard]] auto X_is_valid(u8_acceptable_t acceptable_values = {}) const -> bool {
        return _X.has_value() && _X.value().is_valid(acceptable_values);
    }

    auto Y(std::uint16_t inst) -> void {
        _Y = {((inst & 0x00F0) >> 4)};
    }

    [[nodiscard]] auto Y() const -> std::uint8_t {
        return _Y.value_or(Y_t{})();
    }

    [[nodiscard]] auto Y_is_valid(u8_acceptable_t acceptable_values = {}) const -> bool {
        return _Y.has_value() && _Y.value().is_valid(acceptable_values);
    }

    auto N(std::uint16_t inst) -> void {
        _N = {inst & 0x000F};
    }

    [[nodiscard]] auto N() const -> std::uint8_t {
        return _N.value_or(N_t{})();
    }

    [[nodiscard]] auto N_is_valid(u8_acceptable_t acceptable_values = {}) const -> bool {
        return _N.has_value() && _N.value().is_valid(acceptable_values);
    }

    auto NN(std::uint16_t inst) -> void {
        _NN = {inst & 0x00FF};
    }

    [[nodiscard]] auto NN() const -> std::uint8_t {
        return _NN.value_or(NN_t{})();
    }

    [[nodiscard]] auto NN_is_valid(u8_acceptable_t acceptable_values = {}) const -> bool {
        return _NN.has_value() && _NN.value().is_valid(acceptable_values);
    }

    auto NNN(std::uint16_t inst) -> void {
        _NNN = {inst & 0x0FFF};
    }

    [[nodiscard]] auto NNN() const -> std::uint16_t {
        return _NNN.value_or(NNN_t{})();
    }

    [[nodiscard]] auto NNN_is_valid(u16_acceptable_t acceptable_values = {}) const -> bool {
        return _NNN.has_value() && _NNN.value().is_valid(acceptable_values);
    }
};
}   // chip8
