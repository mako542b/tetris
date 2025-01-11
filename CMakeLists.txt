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

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

# Link the required libraries (matching your g++ command)
target_link_libraries(TetrisGame raylib opengl32 gdi32 winmm)
