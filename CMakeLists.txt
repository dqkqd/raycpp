cmake_minimum_required(VERSION 3.10)

project(raycpp CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LIB_SOURCES
    src/color.cpp
    src/ray.cpp
    src/vec3.cpp
    src/point.cpp
    src/sphere.cpp
    src/hit.cpp
    src/world.cpp
    src/interval.cpp
    src/camera.cpp
    src/progress.cpp
    src/material.cpp)

add_executable(raycpp src/main.cpp ${LIB_SOURCES})

target_include_directories(raycpp PRIVATE include)
target_compile_options(
  raycpp
  PRIVATE -Wall
          -Wextra
          -Wpedantic
          -Wshadow
          -Wundef
          -Wdouble-promotion
          -Wvla
          $<$<CONFIG:Release>:-O2>
          $<$<CONFIG:Debug>:-fsanitize=address,undefined>)

target_link_options(raycpp PRIVATE
                    $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
