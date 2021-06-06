cmake_minimum_required (VERSION 3.13)

add_executable(test-parser-code)

target_sources(test-parser-code PRIVATE test-parser-code.cpp)

add_test(NAME parser-code COMMAND test-parser-code)

target_link_libraries(test-parser-code 
    PRIVATE 
        doctest::doctest
        parser-code
)