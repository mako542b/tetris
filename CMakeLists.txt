# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TetrisGame VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the headers in the "include" directory
include_directories(include)

# Use GLOB to find all .cpp files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Add the executable with all source files
add_executable(TetrisGame ${SOURCES})

# Set the directory where the raylib library resides (adjust the path as necessary)
set(RAYLIB_PATH "${CMAKE_SOURCE_DIR}/lib")

# Add raylib as a static library
add_library(raylib STATIC IMPORTED)

# Set the location of the raylib static library
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${RAYLIB_PATH}/libraylib.a")

# Link the required libraries (matching your g++ command)
target_link_libraries(TetrisGame raylib opengl32 gdi32 winmm)