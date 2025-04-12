#pragma once

// #include <cstdint>
#include <SDL3/SDL_init.h>

namespace media {

enum class sub_system {
    AUDIO = SDL_INIT_AUDIO,
    VIDEO = SDL_INIT_VIDEO,
    JOYSTICK = SDL_INIT_JOYSTICK,
    HAPTIC = SDL_INIT_HAPTIC,
    GAMEPAD = SDL_INIT_GAMEPAD,
    EVENTS = SDL_INIT_EVENTS,
    SENSOR = SDL_INIT_SENSOR,
    CAMERA = SDL_INIT_CAMERA
};

class sdl {
  private:
    std::uint32_t flags;

    bool init_(sub_system sub_sys) {
        uint32_t sub_sys_ = static_cast<uint32_t>(sub_sys);
        if(flags & ~sub_sys_) {
            return 0;
        }

        flags |= sub_sys_;
        return SDL_Init(sub_sys_);
    }

    void close_(sub_system sub_sys) {
        uint32_t sub_sys_ = static_cast<uint32_t>(sub_sys);
        if(!(flags & ~sub_sys_)) {
            return;
        }

        flags ^= sub_sys_;
        SDL_QuitSubSystem(sub_sys_);
    }

  public:
    sdl()
     : flags(0)
    {}

    ~sdl() {
        if(flags) {
            SDL_QuitSubSystem(flags);
        }

        SDL_Quit();
    }

    bool init(sub_system sub_sys) {
        return init_(sub_sys);
    }

    bool init_audio() {
        return init_(sub_system::AUDIO);
    }

    bool init_video() {
        return init_(sub_system::VIDEO);
    }

    bool init_joystick() {
        return init_(sub_system::JOYSTICK);
    }

    bool init_haptic() {
        return init_(sub_system::HAPTIC);
    }

    bool init_gamepad() {
        return init_(sub_system::GAMEPAD);
    }

    bool init_events() {
        return init_(sub_system::EVENTS);
    }

    bool init_sensor() {
        return init_(sub_system::SENSOR);
    }

    bool init_camera() {
        return init_(sub_system::CAMERA);
    }

    void close(sub_system sub_sys) {
        close_(sub_sys);
    }

    void close_audio() {
        close_(sub_system::AUDIO);
    }

    void close_video() {
        close_(sub_system::VIDEO);
    }

    void close_joystick() {
        close_(sub_system::JOYSTICK);
    }

    void close_haptic() {
        close_(sub_system::HAPTIC);
    }

    void close_gamepad() {
        close_(sub_system::GAMEPAD);
    }

    void close_events() {
        close_(sub_system::EVENTS);
    }

    void close_sensor() {
        close_(sub_system::SENSOR);
    }

    void close_camera() {
        close_(sub_system::CAMERA);
    }
};

}   // namespace sdl
