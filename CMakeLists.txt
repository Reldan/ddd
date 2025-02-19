cmake_minimum_required(VERSION 3.31)
project(ddd C)

set(CMAKE_C_STANDARD 11)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ddd main.c)

# Link SDL2
target_link_libraries(ddd PRIVATE ${SDL2_LIBRARIES})

# Set architecture-specific flags
set(CMAKE_OSX_ARCHITECTURES "arm64")