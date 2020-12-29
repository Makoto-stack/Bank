cmake_minimum_required(VERSION 3.9)
project(ass5_banker)

set(CMAKE_CXX_STANDARD 14)

# need to load data files from current directory as cpp files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ass5_banker account.cpp main.cpp accounttree.cpp bank.cpp transaction.cpp)