#pragma once

/*
    Font is represented in 5 bytes. 4 pixel wide and 5 pixel tall
    1 ==> pixel ON
    0 ==> pixel OFF

    0 == 11110000
         10010000
         10010000
         10010000
         11110000
    
    1 == 00100000
         01100000
         00100000
         00100000
         01110000

         .
         .
         .

    F == 11110000
         10000000
         11110000
         10000000
         10000000

         If above technique is followed then fonts for numbers from 0 to F will have the following values.
 */
namespace chip8 {
    constinit inline std::array<std::array<std::uint8_t, 0x05>, 0x0F> font_sprites = {
        {0xF0, 0x90, 0x90, 0x90, 0xF0}, // 0
        {0x20, 0x60, 0x20, 0x20, 0x70}, // 1
        {0xF0, 0x10, 0xF0, 0x80, 0xF0}, // 2
        {0xF0, 0x10, 0xF0, 0x10, 0xF0}, // 3
        {0x90, 0x90, 0xF0, 0x10, 0x10}, // 4
        {0xF0, 0x80, 0xF0, 0x10, 0xF0}, // 5
        {0xF0, 0x80, 0xF0, 0x90, 0xF0}, // 6
        {0xF0, 0x10, 0x20, 0x40, 0x40}, // 7
        {0xF0, 0x90, 0xF0, 0x90, 0xF0}, // 8
        {0xF0, 0x90, 0xF0, 0x10, 0xF0}, // 9
        {0xF0, 0x90, 0xF0, 0x90, 0x90}, // A
        {0xE0, 0x90, 0xE0, 0x90, 0xE0}, // B
        {0xF0, 0x80, 0x80, 0x80, 0xF0}, // C
        {0xE0, 0x90, 0x90, 0x90, 0xE0}, // D
        {0xF0, 0x80, 0xF0, 0x80, 0xF0}, // E
        {0xF0, 0x80, 0xF0, 0x80, 0x80}  // F
    };
}   // namespace chip8
