#pragma once

namespace chip8 {
    // General purpose registers - 
    class vx {
      private:
        constinit static std::array<std::uint8_t, 16> data{0};

        auto validate_index(auto idx) {
            while(idx >= 16);
        }

      public:
        [[nodiscard]] auto operator[](auto idx) -> std::uint8_t const {
            validate_index(idx);
            return data[idx];
        }

        [[nodiscard]] auto operator[](auto idx) -> std::uint8_t& {
            validate_index(idx);
            return data[idx];
        }

        [[nodiscard]] auto is_equal_to(auto idx, auto val) -> bool const {
            validate_index(idx);
            return data[idx] == val;
        }

        [[nodiscard]] auto is_not_equal_to(auto idx, auto val) -> bool const {
            return !is_equal_to(idx, val);
        }

        [[nodiscard]] auto is_equal(auto idx1, auto idx2) -> bool const {
            validate_index(idx1);
            validate_index(idx2);
            return data[idx1] == data[idx2];
        }

        [[nodiscard]] auto is_not_equal(auto idx1, auto idx2) -> bool const {
            return !is_equal(idx1, idx2);
        }

        auto assign_val(auto idx, auto val) -> void {
            validate_index(idx);
            data[idx] = val;
        }

        auto assign(auto idx1, auto idx2) -> void {
            validate_index(idx1);
            validate_index(idx2);
            data[idx1] = data[idx2];
        }

        auto add_val(auto idx, auto val) -> void {
            validate_index(idx);
            data[idx] += val;
        }

        auto add(auto idx1, auto idx2) -> void {
            validate_index(idx1);
            validate_index(idx2);
            
            data[16] = (std::static_cast<uint16_t>(data[idx1]) + std::static_cast<uint16_t>(data[idx2])) > 0xFF ? 1 : 0;
            data[idx1] += data[idx2];
        }

        auto sub1(auto idx1, auto idx2) -> void {
            validate_index(idx1);
            validate_index(idx2);

            data[16] = (data[idx1] >= data[idx2]) ? 1 : 0;

            data[idx1] -= data[idx2];
        }

        auto sub2(auto idx1, auto idx2) -> void {
            validate_index(idx1);
            validate_index(idx2);

            data[16] = (data[idx2] >= data[idx1]) ? 1 : 0;

            data[idx1] = data[idx2] - data[idx1];
        }

        auto bit_or(auto idx1, auto idx2) -> void {
            validate_index(idx1);
            validate_index(idx2);
            data[idx1] |= data[idx2];
        }

        auto bit_and(auto idx1, auto idx2) -> void {
            validate_index(idx1);
            validate_index(idx2);
            data[idx1] &= data[idx2];
        }

        auto bit_xor(auto idx1, auto idx2) -> void {
            validate_index(idx1);
            validate_index(idx2);
            data[idx1] ^= data[idx2];
        }

        auto shift_right(auto idx) -> void {
            validate_index(idx);
            data[16] = data[idx] & 0x01;
            data[idx] >>= 1;
        }

        auto shift_left(auto idx) -> void {
            validate_index(idx);
            data[16] = (data[idx] & 0x80) >> 7;
            data[idx] <<= 1;
        }
    };
    

    //Register I to access memory
    class i {
      private:
        constinit static std::uint16_t val{0};

      public:
        [[nodiscard]] auto operator()() -> std::uint16_t const {
            return val & 0x0FFF;
        }
    };

    // Delay and sound timers (decremented at every 60Hz == 1sec)
    constinit static std::uint8_t delay_timer{0};
    constinit static std::uint8_t sound_timer{0};

    // program counter
    constinit static std::uint16_t pc{0};

    // stack
    class sp{
      private:
        constinit static std::stack<std::uint16_t> data;
    
      public:
        [[nodiscard]] constexpr static auto top() -> std::uint16_t {
            while(data.empty());
            
            auto ret_addr = data.top();

            data.pop();
            return ret_addr;
        }

        constexpr static auto push(std::uint16_t ret_to) -> void {
            while(data.size() >= 16);

            return data.push(ret_to);
        }
    };
}   // namespace chip8
