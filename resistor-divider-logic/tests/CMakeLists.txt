cmake_minimum_required (VERSION 3.13)

add_executable(test-rescode-parser)
target_sources(test-rescode-parser PRIVATE test_rescode_parser.cpp)
add_test(NAME test-rescode-parser COMMAND test-rescode-parser)
target_link_libraries(test-rescode-parser 
    PRIVATE 
        doctest::doctest
        resistor-divider::logic
)