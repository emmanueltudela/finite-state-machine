cmake_minimum_required(VERSION 3.30)

project(finite-state-machine)
include_directories($CMAKE_CURRENT_SOURCE_DIR)

# Compile library for easy use
add_library(fstatem finite-state-machine.c)

# Main executable to test
add_executable(main main.c)
target_link_libraries(main fstatem)
