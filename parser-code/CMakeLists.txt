cmake_minimum_required (VERSION 3.13)

add_library(parser-code)
add_library(resistor-divider::parser-code ALIAS parser-code)

target_sources(parser-code
    PRIVATE
        parser-code.cpp
    PUBLIC
        parser-code.hpp
)

target_include_directories(parser-code
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
