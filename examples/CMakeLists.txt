
option(INCLUDE_SDL_EXAMPLE "Include example SDL example" ON)

if (INCLUDE_SDL_EXAMPLE)
    add_subdirectory(with_sdl)
endif()
