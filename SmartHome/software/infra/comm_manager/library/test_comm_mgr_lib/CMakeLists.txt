#Set the name of the executable
set (EXECUTABLE_NAME1 "test_lib_comm_mgr_1") 
set (EXECUTABLE_NAME2 "test_lib_comm_mgr_2") 

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging"
                 "comm_mgr")

# Set the source files required
set(SOURCE_FILE_LIST1 "comm_mgr_lib_test_app.c"
                     "comm_mgr_lib_test_app_workers.c")

set(SOURCE_FILE_LIST2 "comm_mgr_lib_test_app2.c"
                     "comm_mgr_lib_test_app_workers.c")

# Generate the executable
add_executable (${EXECUTABLE_NAME1} ${SOURCE_FILE_LIST1})
add_executable (${EXECUTABLE_NAME2} ${SOURCE_FILE_LIST2})

# Link any shared or static libraries, if required
target_link_libraries (${EXECUTABLE_NAME1} LINK_PUBLIC "${LIBRARY_LIST}")
target_link_libraries (${EXECUTABLE_NAME2} LINK_PUBLIC "${LIBRARY_LIST}")

# Add the sub-directories, if any present
#add_subdirectory ()
