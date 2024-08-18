cmake_minimum_required(VERSION 3.10)

# Project name and version
project(JPEGConverter VERSION 1.0)

# Set the C standard (C99 for compatibility)
set(CMAKE_C_STANDARD 99)

# Add the executable
file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(jpeg_converter ${SOURCES})
