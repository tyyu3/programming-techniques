# CMakeList.txt : CMake project for Hashing Technique, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../thirdparty/SQLiteCpp ${CMAKE_CURRENT_LIST_DIR}/out)
add_executable (CMakeTarget "RNG Technique.cpp" "RandomFunctions.cpp")

target_include_directories(CMakeTarget PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../thirdparty/SQLiteCpp/include
)


target_link_libraries(CMakeTarget
  SQLiteCpp
  sqlite3
  )


