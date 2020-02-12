# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")
project ("Search Technique")

# Include sub-projects.
add_subdirectory ("Search Technique")

