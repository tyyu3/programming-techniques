# CMakeList.txt : CMake project for Sorting Technique, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../thirdparty/SQLiteCpp ${CMAKE_CURRENT_LIST_DIR}/out)

add_executable (CMakeTarget "Sorting Technique.cpp" "Sorting Technique.h")

# TODO: Add tests and install targets if needed.
target_include_directories(CMakeTarget PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../thirdparty/SQLiteCpp/include
)
target_link_libraries(CMakeTarget
  SQLiteCpp
  sqlite3
  )