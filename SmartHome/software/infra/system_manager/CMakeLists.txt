#Set the name of the executable
set (EXECUTABLE_NAME "system_manager") 

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging")

# Set the source files required
set (SOURCE_FILE_LIST "main.c"
                      "system_mgr.c"
                      "system_mgr_client_tbl.c")

# Generate the executable
add_executable (${EXECUTABLE_NAME} ${SOURCE_FILE_LIST})

# Link any shared or static libraries, if required
target_link_libraries (${EXECUTABLE_NAME} LINK_PUBLIC "${LIBRARY_LIST}")

# Add the sub-directories, if any present
#add_subdirectory ()
