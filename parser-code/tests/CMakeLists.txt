cmake_minimum_required (VERSION 3.13)

add_executable(test-parser-code test-parser-code.cpp)

add_test(NAME parser-code COMMAND test-parser-code)