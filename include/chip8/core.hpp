#pragma once

#include "details/resources.hpp"
#include "details/memory.hpp"
#include "details/instruction.hpp"

#include <memory>

/*
 * Followed the instructions from: https://en.wikipedia.org/wiki/CHIP-8
 */
namespace chip8 {
template <typename operations_t>
requires SupportsChip8Ops<operations_t>
struct core_t {
    private:
    operations_t& ops;
    std::shared_ptr<resources_t> res;

    public:
    core_t(operations_t &ops_)
    : ops(ops_), res(std::make_shared<resources_t>()) {
        while (res == nullptr) {
            // As resources was not able to set, There is no way to access this instance of Chip!!
        }

        ops.resources(res);
    };

    ~core_t() {
        res.reset();
    }

    [[nodiscard]] auto fetch() -> std::uint16_t {
        return res->read_instruction();
    }

    [[nodiscard]] auto decode(auto const instruction) const -> instruction_t {
        return instruction_t::decode(instruction);
    }

    auto execute(instruction_t const& inst) -> void {
        inst.execute(ops);
    }

    [[nodiscard]] auto load_program(std::vector<std::uint16_t> const& pgm) -> bool {
        return res->load_program(pgm);
    }

    [[nodiscard]] auto resources() -> resources_t& {
        return *res;
    }

    [[nodiscard]] auto resources() const -> const resources_t& {
        return *res;
    }
};

}   // namespace chip8
