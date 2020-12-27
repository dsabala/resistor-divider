cmake_minimum_required (VERSION 3.8)
add_executable (ResistorDivider main.cpp)

configure_file("${CMAKE_SOURCE_DIR}/tests/bom_example_no_res.csv" bom_example_no_res.csv @ONLY)
configure_file("${CMAKE_SOURCE_DIR}/tests/bom_example.csv" bom_example.csv @ONLY)