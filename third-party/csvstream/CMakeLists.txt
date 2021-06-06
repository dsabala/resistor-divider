cmake_minimum_required(VERSION 3.14)
add_library(csvstream INTERFACE)
add_library(csvstream::csvstream ALIAS csvstream)
target_include_directories(csvstream INTERFACE csvtream)
