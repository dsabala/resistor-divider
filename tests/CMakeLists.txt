cmake_minimum_required (VERSION 3.8)

include_directories ("${ResistorDivider_SOURCE_DIR}/src")
include_directories ("${ResistorDivider_SOURCE_DIR}/tests")
add_executable (UnitTests tests.cpp)

configure_file(bom_example_no_res.csv bom_example_no_res.csv @ONLY)
configure_file(bom_example.csv bom_example.csv @ONLY)