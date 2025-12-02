#Set the name of the executable
set (LIB_NAME "interface") 

# Select whether to generate shared or static library @params: ON OFF
set (GENERATE_SHARED_LIB OFF)

# Set the static and shared libraries on which the executable is dependent
set(LIBRARY_LIST "logging")

# Set the source files required
set (SOURCE_FILE_LIST "interface.c")

# Generate the library
if(GENERATE_SHARED_LIB)
    add_library (${LIB_NAME} SHARED ${SOURCE_FILE_LIST})
else(GENERATE_SHARED_LIB)
    add_library (${LIB_NAME} STATIC ${SOURCE_FILE_LIST})
endif(GENERATE_SHARED_LIB)

# Link any shared or static libraries, if required
target_link_libraries (${LIB_NAME} LINK_PUBLIC "${LIBRARY_LIST}")

# Add the sub-directories, if any present
#add_subdirectory ()

# Make sure the compiler can find include files for our library
target_include_directories (${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
