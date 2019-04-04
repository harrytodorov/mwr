# CMake version check
cmake_minimum_required(VERSION 3.7)

# Project name
project(ManyWeekendsRayTracer)

# Enable C++17 standard and set the comiler options
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)

# Enable adress sanitizer
add_compile_options("-fsanitize=address")
link_libraries("-fsanitize=address -fno-omit-frame-pointer")

set(SOURCES src/Main.cpp
            src/Vec3.h
            src/Ray.h
            src/Hitable.h
            src/HitableList.h
            src/Sphere.h
            src/Camera.h
            src/Material.h
            src/Utils.h
            src/Lambertian.h
            src/Metal.h
            src/Dialectic.h
            src/AABB.h
            src/BVH.h)

# Create executable
add_executable(ManyWeekendsRayTracer src/Main.cpp)
