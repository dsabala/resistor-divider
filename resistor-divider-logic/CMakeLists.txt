# https://github.com/dsabala/resistor-divider
# License: MIT

add_subdirectory(tests)

add_library(logic)
add_library(resistor-divider::logic ALIAS logic)

target_sources(logic
    PRIVATE
        src/resistor_divider_logic.cpp
        src/rescode_parser.cpp
        src/pairs_finder.cpp
    PRIVATE
        src/e_serie_consts.hpp
        src/rescode_parser.hpp
        src/pairs_finder.hpp
    PUBLIC
        include/resistor-divider-logic/resistor_divider_logic.hpp
        include/resistor-divider-logic/resistor_pair.hpp
)

target_include_directories(logic
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
