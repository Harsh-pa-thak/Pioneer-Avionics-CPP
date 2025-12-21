cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

project(pioneer_root C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

pico_sdk_init()

set(ARK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ARK)

file(GLOB_RECURSE ARK_SOURCES 
    "${ARK_PATH}/ark.cpp"
    "${ARK_PATH}/kernel/*.cpp"
    "${ARK_PATH}/system/*.cpp"
    "${ARK_PATH}/modules/*/*.cpp"
)

add_executable(pioneer 
    user/main.cpp
    ${ARK_SOURCES}
)

target_include_directories(pioneer PRIVATE
    ${ARK_PATH}
    ${ARK_PATH}/kernel
    ${ARK_PATH}/libs
    ${ARK_PATH}/modules
    ${ARK_PATH}/system
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_SOURCE_DIR}/user
)

target_link_libraries(pioneer 
    pico_stdlib 
    hardware_i2c 
    m
)

pico_enable_stdio_usb(pioneer 1)
pico_enable_stdio_uart(pioneer 1)

pico_add_extra_outputs(pioneer)