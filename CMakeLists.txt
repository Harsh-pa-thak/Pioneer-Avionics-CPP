/*
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
                                        ::                                                      
    ..    ..........    :.      ::      ::     .........  ..    ..........    ...      .        
    ::    ::            : .:.   ::     .::.       ::      ::    ::       :    :: :.    :        
    ::    ::   ..:::    :   .:. ::    ::::::      ::      ::    ::       :    ::   ::  :        
    ::    ::......::    :      :::    ::::::      ::      ::    ::.......:    ::     :::        
                                      ::::::                                                    
                                      :.::.:                                                    
                         .::::          ::          ::::.                                       
                       .::::::::.       ::       .:::::::::                                   
                       ::::::::::::....::::.....:::::::::::                                   
                        .:::::::::::::::::::::::::::::::::.        

                  © Copyright of Ignition Avionics
*/

/**************************************************************************************************
* File:        loops.h
* Author:      Kunsh Jain
* Created On:  2025-12-22
* Brief:       Main loop declarations.
* Description: Contains the `Loops` class used to run periodic tasks.
***************************************************************************************************
* HISTORY:
* +----- (NEW | MODify | ADD | DELete)
* |
* No#   |       when       who                  what
******+*********+**********+********************+**************************************************
* 000  NEW      2025-12-22   Kunsh Jain           Added header and Doxygen
**************************************************************************************************/


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

# Define the `pioneer` executable and the list of source files to compile
add_executable(pioneer 
    user/main.cpp
    ${ARK_SOURCES}
)

# Add include directories used during compilation (private to this target)
target_include_directories(pioneer PRIVATE
    ${ARK_PATH}
    ${ARK_PATH}/kernel
    ${ARK_PATH}/libs
    ${ARK_PATH}/modules
    ${ARK_PATH}/system
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_SOURCE_DIR}/user
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