# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.29)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TROMINO2D "Build Tromino2D library and executable" ON)
option(BUILD_TEST_DRIVER "Build development test driver" ON)
option(BUILD_BENCHMARK_DRIVER "Build development benchmark driver" ON)

if(BUILD_TROMINO2D)
  list(APPEND VCPKG_MANIFEST_FEATURES "tromino2d")
endif()

if(BUILD_TEST_DRIVER)
  list(APPEND VCPKG_MANIFEST_FEATURES "test-driver")
endif()

if(BUILD_BENCHMARK_DRIVER)
  list(APPEND VCPKG_MANIFEST_FEATURES "benchmark-driver")
endif()

project(
  Tromino
  LANGUAGES C CXX
)

add_library(
  tromino_core
  SHARED
)
target_sources(
  tromino_core
  PUBLIC
    FILE_SET HEADERS
    FILES
      "${CMAKE_SOURCE_DIR}/include/tromino/core/tromino.h"
)
target_sources(
  tromino_core
  PRIVATE
    "${CMAKE_SOURCE_DIR}/src/core/tromino.c"
)
target_include_directories(
  tromino_core
  PRIVATE
    "${CMAKE_SOURCE_DIR}/include/tromino/core/"
)
target_include_directories(
  tromino_core
  PUBLIC
    "${CMAKE_SOURCE_DIR}/include/"
)
get_target_property(
  tromino_core_headers
  tromino_core
  HEADER_SET
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/tromino/core/"
  PREFIX "Header files"
  FILES ${tromino_core_headers}
)
get_target_property(
  tromino_core_sources
  tromino_core
  SOURCES
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/core/"
  PREFIX "Source files"
  FILES ${tromino_core_sources}
)

add_library(
  tromino_validation
  SHARED
)
target_sources(
  tromino_validation
  PUBLIC
    FILE_SET HEADERS
    FILES
      "${CMAKE_SOURCE_DIR}/include/tromino/validation/validation.h"
)
target_sources(
  tromino_validation
  PRIVATE
    "${CMAKE_SOURCE_DIR}/src/validation/validation.c"
)
target_include_directories(
  tromino_validation
  PRIVATE
    "${CMAKE_SOURCE_DIR}/include/tromino/validation/"
)
target_include_directories(
  tromino_validation
  PUBLIC
    "${CMAKE_SOURCE_DIR}/include/"
)
get_target_property(
  tromino_validation_headers
  tromino_validation
  HEADER_SET
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/tromino/validation/"
  PREFIX "Header files"
  FILES ${tromino_validation_headers}
)
get_target_property(
  tromino_validation_sources
  tromino_validation
  SOURCES
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/validation/"
  PREFIX "Source files"
  FILES ${tromino_validation_sources}
)

add_library(
  tromino_wrapper
  INTERFACE
)
target_sources(
  tromino_wrapper
  PUBLIC
    FILE_SET HEADERS
    FILES
      "${CMAKE_SOURCE_DIR}/include/tromino/wrapper/callback.hpp"
)
get_target_property(
  tromino_wrapper_headers
  tromino_wrapper
  HEADER_SET
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/tromino/wrapper/"
  PREFIX "Header files"
  FILES ${tromino_wrapper_headers}
)

if(BUILD_TROMINO2D)
find_package(SDL2 CONFIG REQUIRED)
add_library(
  tromino_gfx2d
  SHARED
)
target_include_directories(
  tromino_gfx2d
  PRIVATE
    "${CMAKE_SOURCE_DIR}/include/tromino/gfx2d/"
)
target_include_directories(
  tromino_gfx2d
  PUBLIC
    "${CMAKE_SOURCE_DIR}/include/"
)
target_sources(
  tromino_gfx2d
  PRIVATE
  FILE_SET HEADERS
  FILES
    "${CMAKE_SOURCE_DIR}/include/tromino/gfx2d/board.hpp"
    "${CMAKE_SOURCE_DIR}/include/tromino/gfx2d/gfx2d.hpp"
    "${CMAKE_SOURCE_DIR}/include/tromino/gfx2d/step.hpp"
    "${CMAKE_SOURCE_DIR}/include/tromino/gfx2d/style.hpp"
    "${CMAKE_SOURCE_DIR}/include/tromino/gfx2d/view_model.hpp"
    "${CMAKE_SOURCE_DIR}/include/tromino/gfx2d/window.hpp"
)
target_sources(
  tromino_gfx2d
  PRIVATE
    "${CMAKE_SOURCE_DIR}/src/gfx2d/gfx2d.cpp"
    "${CMAKE_SOURCE_DIR}/src/gfx2d/view_model.cpp"
    "${CMAKE_SOURCE_DIR}/src/gfx2d/window.cpp"
)
get_target_property(tromino_gfx2d_headers tromino_gfx2d HEADER_SET)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/tromino/gfx2d/"
  PREFIX "Header files"
  FILES ${tromino_gfx2d_headers}
)
get_target_property(tromino_gfx2d_sources tromino_gfx2d SOURCES)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/gfx2d/"
  PREFIX "Source files"
  FILES ${tromino_gfx2d_sources}
)
target_link_libraries(
  tromino_gfx2d
  PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
endif()

add_executable(
  tromino
)
target_sources(
  tromino
  PRIVATE
  FILE_SET HEADERS
  FILES
    "${CMAKE_SOURCE_DIR}/src/cli/cli_models.hpp"
    "${CMAKE_SOURCE_DIR}/src/cli/cli_options.hpp"
    "${CMAKE_SOURCE_DIR}/src/cli/init.hpp"
    "${CMAKE_SOURCE_DIR}/src/cli/params.hpp"
    "${CMAKE_SOURCE_DIR}/src/cli/trmn_graph.hpp"
    "${CMAKE_SOURCE_DIR}/src/cli/trmn_graph_vt.hpp"
    "${CMAKE_SOURCE_DIR}/src/cli/wrapper.hpp"
)
target_sources(
  tromino
  PRIVATE
    "${CMAKE_SOURCE_DIR}/src/cli/cli_options.cpp"
    "${CMAKE_SOURCE_DIR}/src/cli/init.cpp"
    "${CMAKE_SOURCE_DIR}/src/cli/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/cli/trmn_graph_vt.cpp"
    "${CMAKE_SOURCE_DIR}/src/cli/wrapper.cpp"
)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_sources(
    tromino
    PRIVATE
    FILE_SET HEADERS
    FILES
      "${CMAKE_SOURCE_DIR}/src/cli/trmn_graph_windows.hpp"
  )
  target_sources(
    tromino
    PRIVATE
      "${CMAKE_SOURCE_DIR}/src/cli/trmn_graph_windows.cpp"
  )
endif()
get_target_property(
  tromino_headers
  tromino
  HEADER_SET
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/cli/"
  PREFIX "Header files"
  FILES ${tromino_headers}
)
get_target_property(
  tromino_sources
  tromino
  SOURCES
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/cli/"
  PREFIX "Source files"
  FILES ${tromino_sources}
)
target_link_libraries(
  tromino
  PRIVATE tromino_core
  PRIVATE tromino_validation
  PRIVATE tromino_wrapper
)

if(BUILD_TROMINO2D)
add_executable(
  tromino2d
)
target_sources(
  tromino2d
  PUBLIC
  FILE_SET HEADERS
  FILES
    "${CMAKE_SOURCE_DIR}/src/gui/callback.hpp"
    "${CMAKE_SOURCE_DIR}/src/gui/cli_models.hpp"
    "${CMAKE_SOURCE_DIR}/src/gui/cli_options.hpp"
    "${CMAKE_SOURCE_DIR}/src/gui/init.hpp"
    "${CMAKE_SOURCE_DIR}/src/gui/params.hpp"
    "${CMAKE_SOURCE_DIR}/src/gui/solver_state.hpp"
)
target_sources(
  tromino2d
  PRIVATE
    "${CMAKE_SOURCE_DIR}/src/gui/callback.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/cli_options.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/init.cpp"
    "${CMAKE_SOURCE_DIR}/src/gui/main.cpp"
)
get_target_property(
  tromino2d_headers
  tromino2d
  HEADER_SET
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/gui/"
  PREFIX "Header files"
  FILES ${tromino2d_headers}
)
get_target_property(
  tromino2d_sources
  tromino2d
  SOURCES
)
source_group(
  TREE "${CMAKE_SOURCE_DIR}/src/gui/"
  PREFIX "Source files"
  FILES ${tromino2d_sources}
)
target_link_libraries(
  tromino2d
  PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    SDL2::SDL2main
)
target_link_libraries(
  tromino2d
  PRIVATE tromino_core
  PRIVATE tromino_validation
  PRIVATE tromino_wrapper
  PRIVATE tromino_gfx2d
)
endif()

if(BUILD_TEST_DRIVER)
enable_testing()
find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework)

add_executable(
  test_driver
)
target_sources(
  test_driver
  PRIVATE
    FILE_SET HEADERS
    FILES
    "${CMAKE_SOURCE_DIR}/test/core/unittest_helper.hpp"
)
target_sources(
  test_driver
  PRIVATE
    "${CMAKE_SOURCE_DIR}/test/core/tromino_2x2_unittest.cpp"
    "${CMAKE_SOURCE_DIR}/test/core/tromino_4x4_unittest.cpp"
    "${CMAKE_SOURCE_DIR}/test/core/tromino_64x64_unittest.cpp"
    "${CMAKE_SOURCE_DIR}/test/core/tromino_stop.cpp"
    "${CMAKE_SOURCE_DIR}/test/core/unittest_helper.cpp"
    "${CMAKE_SOURCE_DIR}/test/main.cpp"
    "${CMAKE_SOURCE_DIR}/test/validation/validation_unittest.cpp"
)
target_link_libraries(
  test_driver
  PRIVATE Boost::unit_test_framework
)
target_link_libraries(
  test_driver
  PRIVATE tromino_core
  PRIVATE tromino_validation
)
endif()

if(BUILD_BENCHMARK_DRIVER)
find_package(nameof CONFIG REQUIRED)
find_package(nanobench CONFIG REQUIRED)
add_executable(
  benchmark_driver
)
target_sources(
  benchmark_driver
  PRIVATE
    "${CMAKE_SOURCE_DIR}/benchmark/core/tromino_benchmark.cpp"
)
target_link_libraries(
  benchmark_driver
  PRIVATE nameof::nameof
  PRIVATE nanobench::nanobench
)
target_link_libraries(
  benchmark_driver
  PRIVATE tromino_core
)
endif()
