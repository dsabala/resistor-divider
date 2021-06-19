add_subdirectory(tests)

add_library(logic)
add_library(resistor-divider::logic ALIAS logic)

target_sources(logic
    PRIVATE
        src/rescode_parser.cpp
        src/pairs_finder.cpp
        src/rescode_parser.hpp
        src/resistor_pair.hpp
        src/pairs_finder.hpp
    PUBLIC
        include/resistor-divider-logic/interface.hpp
)

target_include_directories(logic
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/resistor-divider-logic>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
