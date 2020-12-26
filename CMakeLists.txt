
cmake_minimum_required (VERSION 3.8)

project (ResistorDivider)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)


include_directories ("src")

add_subdirectory ("tests")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)