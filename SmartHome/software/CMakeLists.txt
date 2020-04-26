cmake_minimum_required(VERSION 3.0)
project(SmartHome)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# include the common header files applicable for entire project
include_directories("${CMAKE_SOURCE_DIR}/smarthome")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/infra/system_manager")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/infra/comm_manager")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/infra/cmn")


if(EnableTestCode)
    message(STATUS "Note: EnableTestCode is set. Generating Test Codes...")
endif()

add_subdirectory (apps)
add_subdirectory (infra)
add_subdirectory (smarthome)


