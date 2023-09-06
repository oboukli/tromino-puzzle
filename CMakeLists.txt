# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(
  Tromino
  LANGUAGES C
)

add_library(
  libtromino
  SHARED
  "include/tromino/core/tromino.h"
  "src/core/tromino.c"
)
target_include_directories(
  libtromino
  PUBLIC
  "${CMAKE_SOURCE_DIR}/include/tromino/core"
)
