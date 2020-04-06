# CMakeList.txt : CMake project for Hashing Technique, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.8)

set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../thirdparty/boost")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/boost")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)
find_package(Boost COMPONENTS COMPONENTS)
include_directories(${BOOST_INCLUDE_DIRS})


add_executable (CMakeTarget "RNG Technique.cpp" "RandomFunctions.cpp")
target_link_libraries(CMakeTarget PRIVATE Boost::boost)




