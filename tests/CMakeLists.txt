
cmake_minimum_required (VERSION 3.8)

add_executable (Test  "doctest.h" "tests.cpp")

target_compile_features(Test PUBLIC cxx_std_20)