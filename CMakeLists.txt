#                                                                                                 
#                                     ::                                                          
#                                     ::                                                          
#                                     ::                                                          
#                                     ::                                                          
#                                     ::                                                          
#   ..    ..........    :.      ::      ::     .........  ..    ..........    ...      .        
#   ::    ::            : .:.   ::     .::.       ::      ::    ::       :    :: :.    :        
#   ::    ::   ..:::    :   .:. ::    ::::::      ::      ::    ::       :    ::   ::  :        
#   ::    ::......::    :      :::    ::::::      ::      ::    ::.......:    ::     :::        
#                                     ::::::                                                      
#                                     :.::.:                                                      
#                         .::::         ::          ::::.                                         
#                       .::::::::.       ::       .:::::::::                                      
#                       ::::::::::::....::::.....:::::::::::                                      
#                        .:::::::::::::::::::::::::::::::::.                                      
#
#                  © Copyright of Ignition Avionics
#
# **************************************************************************************************
# * File:        CMakeLists.txt
# * Author:      Kunsh Jain
# * Created On:  2025-12-22
# * Brief:       Main build configuration.
# * Description: CMake build script for the Pioneer project.
# **************************************************************************************************
# * HISTORY:
# * +----- (NEW | MODify | ADD | DELete)
# * |
# * No#   |       when       |      who      |             what
# ******+******************+***************+********************************************************
# * 000   |    2025-12-22    |   Kunsh Jain  | Wrote the initial version of CMakeLists.txt.
# **************************************************************************************************


# Minimum CMake version required for this project
cmake_minimum_required(VERSION 3.13)

# Export `compile_commands.json` for editor tooling (code navigation, linters)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Import Raspberry Pi Pico SDK integration for CMake
include(pico_sdk_import.cmake)

# Define project name and languages (C, C++, ASM)
project(pioneer_root C CXX ASM)

# Set language standards for C and C++ compilation
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Initialize the Pico SDK (required before using SDK functions)
pico_sdk_init()

# Path to ARK module sources inside the repository
set(ARK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ARK)

# Collect ARK source files recursively for inclusion in the build
file(GLOB_RECURSE ARK_SOURCES 
    "${ARK_PATH}/ark.cpp"
    "${ARK_PATH}/kernel/*.cpp"
    "${ARK_PATH}/system/*.cpp"
    "${ARK_PATH}/modules/*/*.cpp"
)

# Add the new usercode directory to ARK_SOURCES or include it directly
add_executable(pioneer 
    user/main.cpp
    user/usercode/usercode.cpp  # Added your logic implementation here
    ${ARK_SOURCES}
)

# Add the usercode folder to include directories
target_include_directories(pioneer PRIVATE
    ${ARK_PATH}
    ${ARK_PATH}/kernel
    ${ARK_PATH}/libs
    ${ARK_PATH}/modules
    ${ARK_PATH}/system
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_SOURCE_DIR}/user
    ${CMAKE_CURRENT_SOURCE_DIR}/user/usercode # Added for #include "usercode.h"
)

# Link libraries required by the firmware (Pico stdlib and hardware drivers)
target_link_libraries(pioneer 
    pico_stdlib 
    hardware_i2c
    hardware_spi   
    hardware_pwm  
    hardware_uart  
    m              
)

# Enable stdio over USB and UART for logging and console access
pico_enable_stdio_usb(pioneer 1)
pico_enable_stdio_uart(pioneer 1)

# Produce UF2/HEX outputs for flashing the Pico
pico_add_extra_outputs(pioneer)