
cmake_minimum_required (VERSION 3.8)

add_executable (Test  "doctest.h" "tests.cpp")

target_compile_features(Test PUBLIC cxx_std_20)
target_compile_options(Test PUBLIC -fconstexpr-ops-limit=4294967296)