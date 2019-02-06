# CMake version check
cmake_minimum_required(VERSION 3.7)

# Project name
project(ManyWeekendsRayTracer)

# Enable C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Set the comiler options
add_compile_options(-Wall -Wextra -pedantic -Werror)

# Add Google's C++ lint
include(include/cpplint.cmake)

# Add source code directories
cpplint_add_subdirectory(src)

# Create executable
add_executable(ManyWeekendsRayTracer src/Main.cpp)
