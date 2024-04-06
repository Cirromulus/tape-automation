cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
include(pico-sdk/pico_sdk_init.cmake)

project(hkwire_bridge)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
file(GLOB LIBs
        "lib/*.h"
        "lib/*.c"
)

file(GLOB SRCs
        "src/*.h"
        "src/*.cpp"
)

file(GLOB PIOs
        "lib/*.pio"
        "src/*.pio"
)
add_executable(hkwire_bridge
        ${SRCs}
        ${LIBs}
)
target_include_directories(hkwire_bridge
        PRIVATE
        "include"
        "lib"
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hkwire_bridge
        pico_stdlib
)

# enable USB serial output
pico_enable_stdio_usb(hkwire_bridge 1)
pico_enable_stdio_uart(hkwire_bridge 0)

# compile pio file
if(PIOs)
        pico_generate_pio_header(hkwire_bridge
                ${PIOs}
                OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated
        )
endif()
# make hardware pio available for interpreting pio file
target_link_libraries(hkwire_bridge
        hardware_pio
        hardware_dma
        hardware_irq
        pico_multicore
        )

pico_set_program_name(hkwire_bridge "HK Onewire USB bridge")
pico_set_program_version(hkwire_bridge "0.1")

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hkwire_bridge)