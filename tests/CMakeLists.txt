
cmake_minimum_required (VERSION 3.8)

add_executable (Test  "doctest.h" "tests.cpp")

#target_compile_features(Test PUBLIC cxx_std_20)

configure_file(bom_example_no_res.csv bom_example_no_res.csv @ONLY)
configure_file(bom_example.csv bom_example.csv @ONLY)