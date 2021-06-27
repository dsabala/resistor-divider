add_executable(test-rescode-parser)
target_sources(test-rescode-parser PRIVATE test_rescode_parser.cpp)
add_test(NAME test-rescode-parser COMMAND test-rescode-parser)
target_link_libraries(test-rescode-parser 
    PRIVATE 
        doctest::doctest
        logic
)
target_include_directories(test-rescode-parser PRIVATE $<TARGET_PROPERTY:logic,INCLUDE_DIRECTORIES>)

add_executable(test-resistor-pair)
target_sources(test-resistor-pair PRIVATE test_resistor_pair.cpp)
add_test(NAME test-resistor-pair COMMAND test-resistor-pair)
target_link_libraries(test-resistor-pair 
    PRIVATE 
        doctest::doctest
        logic
)
target_include_directories(test-resistor-pair PRIVATE $<TARGET_PROPERTY:logic,INCLUDE_DIRECTORIES>)

add_executable(test-pairs-finder)
target_sources(test-pairs-finder PRIVATE test_pairs_finder.cpp)
add_test(NAME test-pairs-finder COMMAND test-pairs-finder)
target_link_libraries(test-pairs-finder 
    PRIVATE 
        doctest::doctest
        logic
)
target_include_directories(test-pairs-finder PRIVATE $<TARGET_PROPERTY:logic,INCLUDE_DIRECTORIES>)

add_executable(test-resistor-divider-logic)
target_sources(test-resistor-divider-logic PRIVATE test_resistor_divider_logic.cpp)
add_test(NAME test-resistor-divider-logic COMMAND test-resistor-divider-logic)
target_link_libraries(test-resistor-divider-logic 
    PRIVATE 
        doctest::doctest
        logic
)
target_include_directories(test-resistor-divider-logic PRIVATE $<TARGET_PROPERTY:logic,INCLUDE_DIRECTORIES>)