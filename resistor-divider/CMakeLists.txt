cmake_minimum_required(VERSION 3.16)

add_executable(resistor-divider)

target_sources(resistor-divider
    PRIVATE
        cli.cpp
        cli.hpp
        main.cpp
)

target_link_libraries(resistor-divider
    PRIVATE
        bfg::Lyra
        logic
)

target_include_directories(resistor-divider
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)