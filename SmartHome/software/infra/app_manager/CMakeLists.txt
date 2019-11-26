#Set the name of the executable
set (EXECUTABLE_NAME "app_manager") 

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging"
                 "comm_mgr")

# Generate the executable
add_executable (${EXECUTABLE_NAME} main.c)

# Link any shared or static libraries, if required
target_link_libraries (${EXECUTABLE_NAME} LINK_PUBLIC "${LIBRARY_LIST}")

# Add the sub-directories, if any present
#add_subdirectory ()
