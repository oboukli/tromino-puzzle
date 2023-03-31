cmake_minimum_required(VERSION 3.26)

project(
    tromino-puzzle
    VERSION 0.0.1
    DESCRIPTION "A software library, and a collection of apps, to solve and visualize the right tromino puzzle"
    HOMEPAGE_URL "https://github.com/oboukli/tromino-puzzle"
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -Werror")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR- /EHs-c- /EHc- /WX")
endif()

# target_compile_options(tutorial_compiler_flags INTERFACE
#   "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
#   "$<${msvc_cxx}:-W3>"
# )

find_package(SDL2 REQUIRED)

add_library(SDL2_static STATIC IMPORTED)
# set_target_properties(SDL2_static PROPERTIES IMPORTED_LOCATION ${SDL2_LIBRARY})

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/src")

set(LIBTROMINO "libtromino")
set(LIBTROMINO_VALIDATION "libtromino-validation")
set(LIBTROMINO2D "libtromino2d")
set(TROMINO "tromino")
set(TROMINO2D "tromino2d")

file(GLOB LIBTROMINO_SRCS "${SRC_DIR}/libtromino/tromino.c")
file(GLOB LIBTROMINO_VALIDATION_SRCS "${SRC_DIR}/validation/*.c")
file(GLOB LIBTROMINO2D_SRCS "${SRC_DIR}/gfx2d/*.cpp")
file(GLOB TROMINO_SRCS
    "${SRC_DIR}/cli/cli_options.cpp"
    "${SRC_DIR}/cli/init.cpp"
    "${SRC_DIR}/cli/main.cpp"
    "${SRC_DIR}/cli/trmn_graph_vt.cpp"
    $<$<PLATFORM_ID:Windows>:"${SRC_DIR}/trmn_graph_windows.cpp"
)
file(GLOB TROMINO2D_SRCS "${SRC_DIR}/gui/*.cpp")

add_library(${LIBTROMINO}_debug STATIC ${LIBTROMINO_SRCS})
add_library(${LIBTROMINO} STATIC ${LIBTROMINO_SRCS})
add_library(${LIBTROMINO_VALIDATION}_debug STATIC ${LIBTROMINO_VALIDATION_SRCS})
add_library(${LIBTROMINO_VALIDATION} STATIC ${LIBTROMINO_VALIDATION_SRCS})
add_library(${LIBTROMINO2D}_debug STATIC ${LIBTROMINO2D_SRCS})
add_library(${LIBTROMINO2D} STATIC ${LIBTROMINO2D_SRCS})

add_executable(${TROMINO}_debug ${TROMINO_SRCS})
add_executable(${TROMINO} ${TROMINO_SRCS})
add_executable(${TROMINO2D}_debug ${TROMINO2D_SRCS})
add_executable(${TROMINO2D} ${TROMINO2D_SRCS})

# target_include_directories(${LIBTROMINO}_debug PUBLIC ${INC_DIR})
# target_include_directories(${LIBTROMINO} PUBLIC ${INC_DIR})
# target_include_directories(${LIBTROMINO_VALIDATION}_debug PUBLIC ${INC_DIR})
# target_include_directories(${LIBTROMINO_VALIDATION} PUBLIC ${INC_DIR})
# target_include_directories(${LIBTROMINO2D}_debug PUBLIC ${INC_DIR})
# target_include_directories(${LIBTROMINO2D} PUBLIC ${INC_DIR})
target_include_directories(${TROMINO}_debug PUBLIC "${INC_DIR}/libtromino" "${INC_DIR}/validation")
target_include_directories(${TROMINO} PUBLIC "${INC_DIR}/libtromino" "${INC_DIR}/validation")
target_include_directories(${TROMINO2D}_debug PUBLIC "${INC_DIR}/libtromino" "${INC_DIR}/validation" "${INC_DIR}/gfx2d")
target_include_directories(${TROMINO2D} PUBLIC "${INC_DIR}/libtromino" "${INC_DIR}/validation" "${INC_DIR}/gfx2d")

# TODO: MSVC
set(DEBUG_FLAGS "-g -O0")
set(RELEASE_FLAGS "-O2")

set_target_properties(${LIBTROMINO}_debug PROPERTIES OUTPUT ${LIBTROMINO}_debug)
set_target_properties(${LIBTROMINO_VALIDATION}_debug PROPERTIES OUTPUT ${LIBTROMINO_VALIDATION}_debug)
set_target_properties(${LIBTROMINO2D}_debug PROPERTIES OUTPUT ${LIBTROMINO2D}_debug)
set_target_properties(${TROMINO}_debug PROPERTIES OUTPUT ${TROMINO}_debug)
set_target_properties(${TROMINO2D}_debug PROPERTIES OUTPUT ${TROMINO2D}_debug)

set_target_properties(${TROMINO}_debug PROPERTIES LINK_FLAGS ${DEBUG_FLAGS})
set_target_properties(${TROMINO2D}_debug PROPERTIES LINK_FLAGS ${DEBUG_FLAGS})

target_link_libraries(${TROMINO}_debug ${LIBTROMINO}_debug ${LIBTROMINO_VALIDATION}_debug)
target_link_libraries(${TROMINO2D}_debug ${LIBTROMINO}_debug ${LIBTROMINO_VALIDATION}_debug ${LIBTROMINO2D}_debug)

set_target_properties(${LIBTROMINO} PROPERTIES OUTPUT ${LIBTROMINO})
set_target_properties(${LIBTROMINO_VALIDATION} PROPERTIES OUTPUT ${LIBTROMINO_VALIDATION})
set_target_properties(${LIBTROMINO2D} PROPERTIES OUTPUT ${LIBTROMINO2D})
set_target_properties(${TROMINO} PROPERTIES OUTPUT ${TROMINO})
set_target_properties(${TROMINO2D} PROPERTIES OUTPUT ${TROMINO2D})

set_target_properties(${TROMINO} PROPERTIES LINK_FLAGS ${RELEASE_FLAGS})
set_target_properties(${TROMINO2D} PROPERTIES LINK_FLAGS ${RELEASE_FLAGS})

target_link_libraries(${TROMINO} ${LIBTROMINO} ${LIBTROMINO_VALIDATION})
target_link_libraries(${TROMINO2D} ${LIBTROMINO} ${LIBTROMINO_VALIDATION} ${LIBTROMINO2D})

target_link_libraries(${LIBTROMINO2D} SDL2-static)
target_link_libraries(${TROMINO2D} SDL2-static)

# find_package(Vcpkg REQUIRED)
# if(VCPKG_TARGET_TRIPLET)
#     vcpkg_install_package(SDL2:x64-windows)
#     set(SDL2_LIB_DIR "${VCPKG_LIBRARY_DIR}/SDL2")
#     set(SDL2_INCLUDE_DIR "${VCPKG_INCLUDE_DIR}/SDL2")
# endif()
# target_include_directories(${TROMINO} PUBLIC ${SDL2_INCLUDE_DIR})
# target_link_libraries(${TROMINO} ${SDL2_LIB_DIR}/SDL2.lib)
