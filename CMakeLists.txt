# CMake version check
cmake_minimum_required(VERSION 3.7)

# Project name
project(ManyWeekendsRayTracer)

# Enable C++17 standard and set the comiler options
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)

# Add Google's C++ lint
include(include/cpplint.cmake)
cpplint_add_subdirectory(src)

set(SOURCES src/Main.cpp
            src/Vec3.h
            src/Ray.h
            src/Hitable.h
            src/HitableList.h
            src/Sphere.h
            src/Camera.h)

# Create executable
add_executable(ManyWeekendsRayTracer src/Main.cpp)
