cmake_minimum_required (VERSION 3.13)

add_subdirectory(tests)

add_library(logic)
add_library(resistor-divider::logic ALIAS logic)

target_sources(logic
    PRIVATE
        rescode_parser.cpp
    PUBLIC
        rescode_parser.hpp
        resistor_pair.hpp
)

target_include_directories(logic
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
