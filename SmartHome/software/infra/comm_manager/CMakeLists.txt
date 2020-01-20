# Set common object name (Used to generate a common obj file for two exe)
set(COMMON_OBJ  "comm_mgr_cmn")

# Set the source files required
set(SOURCE_FILE_LIST "comm_mgr_cmn.c"
                     "comm_mgr_cmn_enums_defs.c")

# Create a Common object file                     
add_library(${COMMON_OBJ} OBJECT ${SOURCE_FILE_LIST})

# Add the sub-directories, if any present
add_subdirectory (library)
add_subdirectory (server)

