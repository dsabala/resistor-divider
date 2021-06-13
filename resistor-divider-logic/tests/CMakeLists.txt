cmake_minimum_required (VERSION 3.13)

add_executable(test-rescode-parser)
target_sources(test-rescode-parser PRIVATE test_rescode_parser.cpp)
add_test(NAME test-rescode-parser COMMAND test-rescode-parser)
target_link_libraries(test-rescode-parser 
    PRIVATE 
        doctest::doctest
        resistor-divider::logic
)

add_executable(test-resistor-pair)
target_sources(test-resistor-pair PRIVATE test_resistor_pair.cpp)
add_test(NAME test-resistor-pair COMMAND test-resistor-pair)
target_link_libraries(test-resistor-pair 
    PRIVATE 
        doctest::doctest
        resistor-divider::logic
)