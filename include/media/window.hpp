#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

namespace media {

class window_t {
  private:
    SDL_Window * window_ptr;
    SDL_Renderer * renderer_ptr;    //TODO: move it to its own class!

    bool create_(char const * title, config_t const & config) {
        if((window_ptr != nullptr) || (renderer_ptr != nullptr)) {
            return false;
        }

        window_ptr = SDL_CreateWindow(title, config::x, config::y, config::w, config::h, 0);
        if(!window_ptr) {
            return false;
        }

        renderer_ptr = SDL_CreateRenderer(window_ptr, -1, 0);
        return (renderer_ptr == nullptr) ? false : true;
    }

  public:
    struct config_t {
        constinit static std::size_t x{SDL_WINDOWPOS_CENTERED};
        constinit static std::size_t y{SDL_WINDOWPOS_CENTERED};
        constinit static std::size_t w{64};
        constinit static std::size_t h{32};
        //TODO: add Window flags!
        //TODO: add window scaling!
    };

    window_t()
    : window_ptr(nullptr),
    renderer_ptr(nullptr)
    {}

    ~window_t() {
        if (renderer_ptr) {
            SDL_DestroyRenderer(renderer_ptr);
        }

        if (window_ptr) {
            SDL_DestroyWindow(window_ptr);
        }
    }

    bool create(config_t const & config){
        return create_("SDL2.0", config);
    }

    bool create(const char* title, config_t const & config){
        return create_(title, config);
    }
};

}   // namespace media
