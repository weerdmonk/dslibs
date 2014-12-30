
cmake_minimum_required(VERSION 2.6)

# set project name
project(dslibs)

MESSAGE("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
MESSAGE("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")

# set build tree root for out of source build
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")

# set library and runtime output directorries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# set include directory
include_directories("${PROJECT_SOURCE_DIR}/inc")

# add directories to recurse into
add_subdirectory(src)
