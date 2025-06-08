project(trail_error)

set(SRC_FILES ./main.cpp)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_executable(
    ${PROJECT_NAME} 
    ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/lib/sdl/include
)

# target_link_directories(
#    ${PROJECT_NAME} 
#    PRIVATE lib/sdl
# )

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC 
    chip8
    SDL3::SDL3)
