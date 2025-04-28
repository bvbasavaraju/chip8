#pragma once

#include <array>
#include <vector>

namespace chip8 {

namespace detail {

template <uint8_t REG_COUNT = 16, uint16_t RAM_SIZE = 4096>
struct resources_t {
    private:
    std::uint16_t ram_index;
    std::uint16_t pc;
    std::uint16_t reg_i;
    std::stack<std::uint16_t> sp; 
    std::array<std::uint8_t, REG_COUNT> vx;
    std::array<std::uint8_t, RAM_SIZE> ram;

    auto load_instruction(std::uint16_t inst) {
        if (ram_index >= 4094) {
            //TODO: log error
            return;   // ran out of memory
        }

        ram[ram_index++] = ((inst & 0xFF00) >> 8);
        ram[ram_index++] = (inst & 0xFF);
    }

    public:
    resources_t() 
    : ram_index(0),
    pc(0),
    reg_i(0),
    vx{0},
    ram{0} {}

    auto read_instruction() -> std::uint16_t {
        if(pc > 4094) {
            return 0;
        }

        return ((ram[pc++] << 8) | (ram[pc++]));
    }

    auto load_program(std::vector<std::uint16_t> const& pgm) -> bool {
        auto len = pgm.size();
        if (ram_index > 0 || len <= 0 || len >= 4096) {
            return false;
        }

        for (auto inst : pgm) {
            load_instruction(inst);
        }

        return true;
    }
    auto reset(bool erase_ram = true) -> void {
        ram_index = 0;
        pc = 0;
        reg_i = 0;
        while(!sp.empty()) {
            sp.pop();
        }

        vx = {0};
        if(erase_ram) {
            ram = {0};
        }
    }
};

}

using resources_t = detail::resources_t<>;

} // namespace chip8
