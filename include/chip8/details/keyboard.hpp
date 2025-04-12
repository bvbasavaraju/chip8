#pragma once

namespace chip8 {

template <std::uint8_t val>
struct key;

template <> key<48> { constexpr static auto value = 48 - '0'; };

template <> key<49> { constexpr static auto value = 49 - '0'; };

template <> key<50> { constexpr static auto value = 50 - '0'; };

template <> key<51> { constexpr static auto value = 51 - '0'; };

template <> key<52> { constexpr static auto value = 52 - '0'; };

template <> key<53> { constexpr static auto value = 53 - '0'; };

template <> key<54> { constexpr static auto value = 54 - '0'; };

template <> key<55> { constexpr static auto value = 55 - '0'; };

template <> key<56> { constexpr static auto value = 56 - '0'; };

template <> key<57> { constexpr static auto value = 57 - '0'; };

template <> key<65> { constexpr static auto value = 65 - 'A'; };

template <> key<66> { constexpr static auto value = 66 - 'A'; };

template <> key<67> { constexpr static auto value = 67 - 'A'; };

template <> key<68> { constexpr static auto value = 68 - 'A'; };

template <> key<69> { constexpr static auto value = 69 - 'A'; };

template <> key<70> { constexpr static auto value = 70 - 'A'; };

template <std::uint8_t val>
constexpr static auto key_v = key<val>::value;

}   // namespace chip8
