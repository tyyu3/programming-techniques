cmake_minimum_required (VERSION 3.8)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../thirdparty/SQLiteCpp ${CMAKE_CURRENT_LIST_DIR}/out)
add_executable (CMakeTarget "Search Technique.cpp" "Search Technique.h")

target_include_directories(CMakeTarget PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../../thirdparty/SQLiteCpp/include
)


target_link_libraries(CMakeTarget
  SQLiteCpp
  sqlite3
  )