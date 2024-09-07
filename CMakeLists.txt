cmake_minimum_required(VERSION 3.30)
set(CMAKE_C_FLAGS "-std=c99 -Wall -g -O3")

# Configure project and include dir
project(finite-state-machine)
include_directories($CMAKE_CURRENT_SOURCE_DIR)

enable_testing()
include(CTest)

# Compile library for easy use
add_library(fstatem fstatem.c)

# Main executable for debugging
add_executable(main main.c)
target_link_libraries(main fstatem)

# Main executable to test libfstatem
add_executable(testfstatem testfstatem.c)
target_link_libraries(testfstatem fstatem)

add_test(NAME freeStates COMMAND ./testfstatem freeStates)
