#Set the name of the executable
set (EXECUTABLE_NAME "shell") 

# include the cli directory where we can find the auto-generated cli files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/cli")

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging"
                 "utils"
                 "comm_mgr")

# Set the source files required
set (SOURCE_FILE_LIST "shell.c"
                      "shell_workers.c"
                      "shell_cli.c")


# Generate the executable
add_executable (${EXECUTABLE_NAME} ${SOURCE_FILE_LIST})

# Link any shared or static libraries, if required
target_link_libraries (${EXECUTABLE_NAME} LINK_PUBLIC "${LIBRARY_LIST}")

# Add the sub-directories, if any present
#add_subdirectory ()
