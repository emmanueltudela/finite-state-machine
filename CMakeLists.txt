cmake_minimum_required(VERSION 3.30)
set(CMAKE_C_FLAGS "-std=c99 -Wall")

# Configure project and include dir
project(finite-state-machine)
include_directories($CMAKE_CURRENT_SOURCE_DIR)

# Compile library for easy use
add_library(fstatem fstatem.c)

# Main executable to test
add_executable(main main.c)
target_link_libraries(main fstatem)
