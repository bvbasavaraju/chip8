set(MAIN main)

set(SRC_FILES ./main.cpp)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_executable(
    ${MAIN} 
    ${SRC_FILES})

target_include_directories(
    ${MAIN} 
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(
    ${MAIN} 
    PUBLIC 
    chip8)

# Enable when ready to include the SDL library
# target_include_directories(
#     ${MAIN} 
#     PUBLIC 
#     ${PROJECT_SOURCE_DIR}/include
#     ${PROJECT_SOURCE_DIR}/lib/SDL/include)

# target_link_libraries(
#     ${MAIN} 
#     PUBLIC 
#     chip8
#     SDL3::SDL3)
