cmake_minimum_required (VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(resistor-divider CXX)

include(CTest)
enable_testing()

add_subdirectory(resistor-divider-logic)
add_subdirectory(resistor-divider)
add_subdirectory(third-party)
