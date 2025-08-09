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
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Tarefa_13_2_Lora C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(${PROJECT_NAME} main.c
        lib/button/button.c # Button library
        lib/led/led.c # LED library
        lib/ssd1306/ssd1306.c # SSD1306 library
        lib/ssd1306/display.c # Display library
        lib/buzzer/buzzer.c # Buzzer library)
        lib/matrix_leds/matrix_leds.c # Matrix LEDs library
        lib/aht20/aht20.c # AHT20 sensor library
        lib/bmp280/bmp280.c # BMP280 sensor library
        lib/sensors/sensors.c # Sensor management library
)

pico_set_program_name(Tarefa_13_2_Lora "Tarefa_13_2_Lora")
pico_set_program_version(Tarefa_13_2_Lora "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Tarefa_13_2_Lora 1)
pico_enable_stdio_usb(Tarefa_13_2_Lora 1)

# Add the standard library to the build
target_link_libraries(Tarefa_13_2_Lora
        pico_stdlib)

# Generate PIO header
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/lib/matrix_leds/pio_matrix.pio)

# Add the standard include files to the build
target_include_directories(Tarefa_13_2_Lora PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/lib
)

# Add any user requested libraries
target_link_libraries(Tarefa_13_2_Lora 
        hardware_i2c
        hardware_pio
        hardware_timer
        hardware_clocks
        hardware_adc
        hardware_pwm

        )

pico_add_extra_outputs(Tarefa_13_2_Lora)

