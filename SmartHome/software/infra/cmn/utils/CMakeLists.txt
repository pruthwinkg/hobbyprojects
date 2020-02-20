#Set the name of the executable
set (LIB_NAME "utils") 

# Select whether to generate shared or static library @params: ON OFF
set (GENERATE_SHARED_LIB ON)

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging"
                 "rt"   # -lrt is required for shm
                 "pthread") # -lpthread is required for task handler                 

# Set the source files required
set (SOURCE_FILE_LIST "shared_mem.c"
                      "taskhandler.c"
                      "data_structures.c")

# Generate the library
if(GENERATE_SHARED_LIB)
    add_library (${LIB_NAME} SHARED ${SOURCE_FILE_LIST})
else(GENERATE_SHARED_LIB)
    add_library (${LIB_NAME} STATIC ${SOURCE_FILE_LIST})
endif(GENERATE_SHARED_LIB)

# Link any shared or static libraries, if required
target_link_libraries (${LIB_NAME} LINK_PUBLIC "${LIBRARY_LIST}")

# Make sure the compiler can find include files for our library
target_include_directories (${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add the sub-directories, if any present
if(EnableTestCode)
    add_subdirectory (shared_mem_test)
    add_subdirectory (taskhandler_test)
    add_subdirectory (datastructures_test)
endif()    

