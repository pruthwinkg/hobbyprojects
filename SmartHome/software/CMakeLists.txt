cmake_minimum_required(VERSION 3.0)
project(SmartHome)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# include the common header files applicable for entire project
include_directories("${CMAKE_SOURCE_DIR}/smarthome")

#add_subdirectory (apps)
add_subdirectory (infra)
add_subdirectory (smarthome)


