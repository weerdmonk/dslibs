
cmake_minimum_required(VERSION 2.6)

# set project name
project(dslibs)

MESSAGE("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
MESSAGE("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")

# set library and runtime output directorries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# set include directory
include_directories("${PROJECT_SOURCE_DIR}/inc")

# add subdirectories
add_subdirectory(src)
add_subdirectory(examples)

# add dslibs library
add_library(dslibs SHARED src/list.c src/stack.c src/queue.c src/btree.c src/graph.c src/sort.c src/maxheap.c)

# install dslibs library
