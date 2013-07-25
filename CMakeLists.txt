cmake_minimum_required (VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
project (BigInteger)
#The version number
set (BigInteger_VERSION_MAJOR 0)
set (BigInteger_VERSION_MINOR 9)

add_library(BigIntegerOps BigIntegerOps.c)
add_subdirectory(test)
add_executable(BigInteger main.c)
target_link_libraries(BigInteger BigIntegerOps)



