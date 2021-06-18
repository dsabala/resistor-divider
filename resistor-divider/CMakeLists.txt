cmake_minimum_required(VERSION 3.16)

add_executable(resistor-divider)

target_sources(resistor-divider
    PRIVATE
        main.cpp    
)

target_link_libraries(resistor-divider
    PRIVATE
        bfg::Lyra
)