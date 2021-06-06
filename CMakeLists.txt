
cmake_minimum_required (VERSION 3.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project (ResistorDivider CXX)
add_subdirectory (src) 
add_subdirectory (tests)
enable_testing ()

include_directories(
    "src"
    "tests"
)

message("lmao ${CMAKE_SOURCE_DIR}")

add_test (
    NAME MyTest 
    COMMAND UnitTests
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




