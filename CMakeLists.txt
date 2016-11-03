# DEBUG: Debugging flag
# BUILD_TESTS: Tests building flag

cmake_minimum_required(VERSION 2.6)
project(RSRL)

option(DEBUG
       "Debug switch" OFF)

if (DEBUG)
    set(CMAKE_CXX_FLAGS "-std=c++11 -g")
else (DEBUG)
    set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
endif (DEBUG)

aux_source_directory(./source RSRL_SOURCE)
include_directories(./include)

add_library(RSRL SHARED ${RSRL_SOURCE})

option(BUILD_TESTS
       "Determine whether build the tests" OFF)

if (BUILD_TESTS)
    add_executable(ColorTest ./tests/ColorTest.cpp)
    target_link_libraries(ColorTest RSRL)
    add_executable(MatrixTest ./tests/MatrixTest.cpp)
    target_link_libraries(MatrixTest RSRL)
    add_executable(VectorTest ./tests/VectorTest.cpp)
    target_link_libraries(VectorTest RSRL)
endif (BUILD_TESTS)