#Set the name of the executable
set (EXECUTABLE_NAME_1 "test_utils_shared_obj_write") 
set (EXECUTABLE_NAME_2 "test_utils_shared_obj_read") 

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging"
                 "utils")

# Set the source files required
set(SOURCE_FILE_LIST_1 "write.c")
set(SOURCE_FILE_LIST_2 "read.c")

# Generate the executable
add_executable (${EXECUTABLE_NAME_1} ${SOURCE_FILE_LIST_1})
add_executable (${EXECUTABLE_NAME_2} ${SOURCE_FILE_LIST_2})

# Link any shared or static libraries, if required
target_link_libraries (${EXECUTABLE_NAME_1} LINK_PUBLIC "${LIBRARY_LIST}")
target_link_libraries (${EXECUTABLE_NAME_2} LINK_PUBLIC "${LIBRARY_LIST}")

# Add the sub-directories, if any present
#add_subdirectory ()
