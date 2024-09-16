cmake_minimum_required(VERSION 3.30)
set(CMAKE_C_FLAGS "-std=c99 -Wall -g -O3 -flarge-source-files")

# Configure project and include dir
project(finite-state-machine)
include_directories($CMAKE_CURRENT_SOURCE_DIR)

enable_testing()
include(CTest)

# Compile library for easy use
add_library(fstatem fstatem.c regexpr.c)
add_library(regexpr regexpr.c)

# Main executable for debugging
add_executable(main main.c)
target_link_libraries(main fstatem regexpr)

# Tests executables
add_executable(testfstatem testfstatem.c)
target_link_libraries(testfstatem fstatem)

add_executable(testregexpr testregexpr.c)
target_link_libraries(testregexpr regexpr)

# Tests fstatem
add_test(NAME freeStates COMMAND ./testfstatem freeStates)
add_test(NAME createStates COMMAND ./testfstatem createStates)
add_test(NAME createMachine COMMAND ./testfstatem createMachine)
add_test(NAME freeMachine COMMAND ./testfstatem freeMachine)
add_test(NAME connectStates COMMAND ./testfstatem connectStates)
add_test(NAME computeWord COMMAND ./testfstatem computeWord)
