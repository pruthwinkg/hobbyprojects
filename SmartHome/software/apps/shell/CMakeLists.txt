#Set the name of the executable
set (EXECUTABLE_NAME "shell") 

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging"
                 "utils"
                 "comm_mgr")

# Set the source files required
set (SOURCE_FILE_LIST "shell.c"
                      "shell_workers.c")

# Generate the executable
add_executable (${EXECUTABLE_NAME} ${SOURCE_FILE_LIST})

# Link any shared or static libraries, if required
target_link_libraries (${EXECUTABLE_NAME} LINK_PUBLIC "${LIBRARY_LIST}")

# Add the sub-directories, if any present
#add_subdirectory ()
