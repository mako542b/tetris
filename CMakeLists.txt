# Minimum required version of CMake
cmake_minimum_required(VERSION 3.14)

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

# Enable FetchContent module
include(FetchContent)

# Declare raylib as a dependency
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master  # Use the latest commit or specify a tag/branch
)

# Make sure the dependency is downloaded and built if necessary
FetchContent_MakeAvailable(raylib)

# Link the required libraries (matching your g++ command)
target_link_libraries(TetrisGame raylib opengl32 gdi32 winmm)
