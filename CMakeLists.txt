# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
  CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file"
)

project(
  Tromino
  LANGUAGES C CXX
)

add_library(
  tromino
  SHARED
  "include/tromino/core/tromino.h"
  "src/core/tromino.c"
)
target_include_directories(
  tromino
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include/tromino/core"
)

find_package(nameof CONFIG REQUIRED)
find_package(nanobench CONFIG REQUIRED)
add_executable(
  benchmark
  "benchmark/core/tromino_bechmark.cpp"
)
target_link_libraries(
  benchmark
  PRIVATE nameof::nameof
  PRIVATE nanobench::nanobench
  PRIVATE tromino
)
