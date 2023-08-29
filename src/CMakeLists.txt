cmake_minimum_required(VERSION 3.20.0)

project(chapter6design)
set(target_name "test")

include_directories($ENV{GTEST_HOME}/googlemock/include $ENV{GTEST_HOME}/googletest/include)
link_directories($ENV{GTEST_HOME}/out/build/lib)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(sources
   main.cpp
   PortfolioTest.cpp
   Portfolio.cpp)

add_executable(${target_name} ${sources})

target_link_libraries(test pthread)
target_link_libraries(test gmock)
target_link_libraries(test gtest)

target_compile_features(${target_name} PUBLIC cxx_std_17)
