# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-ssd1306+sd C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src)

# Add executable. Default name is the project name, version 0.1
add_executable(pico-ssd1306+sd
    main.c
    hw_config.c
)

pico_set_program_name(pico-ssd1306+sd "pico-ssd1306+sd")
pico_set_program_version(pico-ssd1306+sd "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico-ssd1306+sd 1)
pico_enable_stdio_usb(pico-ssd1306+sd 0)

# Add the standard library and FatFS/SPI to the build
target_link_libraries(pico-ssd1306+sd
    pico_stdlib
    no-OS-FatFS-SD-SDIO-SPI-RPi-Pico
)

# Add the standard include files to the build
target_include_directories(pico-ssd1306+sd PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(pico-ssd1306+sd 
        
        )

pico_add_extra_outputs(pico-ssd1306+sd)

