#Set the name of the executable
set (EXECUTABLE_NAME1 "test_mapi_1") 
set (EXECUTABLE_NAME2 "test_mapi_2") 

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging"
                 "mapi"
                 "pthread")

# Set the source files required
set(SOURCE_FILE_LIST1 "mapi_test_app.c")

set(SOURCE_FILE_LIST2 "mapi_test_app.c")

# Generate the executable
add_executable (${EXECUTABLE_NAME1} ${SOURCE_FILE_LIST1})
add_executable (${EXECUTABLE_NAME2} ${SOURCE_FILE_LIST2})

# Set the Module specific Compile flags
target_compile_definitions(${EXECUTABLE_NAME1} PRIVATE TEST_APP_1=1)
target_compile_definitions(${EXECUTABLE_NAME2} PRIVATE TEST_APP_2=1)

# Link any shared or static libraries, if required
target_link_libraries (${EXECUTABLE_NAME1} LINK_PUBLIC "${LIBRARY_LIST}")
target_link_libraries (${EXECUTABLE_NAME2} LINK_PUBLIC "${LIBRARY_LIST}")

# Add the sub-directories, if any present
#add_subdirectory ()
