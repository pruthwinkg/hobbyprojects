# include the common header files applicable for entire /infra
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/system_manager")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/comm_manager")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/cmn")

add_subdirectory (cmn)
add_subdirectory (app_manager)
#add_subdirectory (database_manager)
add_subdirectory (system_manager)
add_subdirectory (comm_manager)
#add_subdirectory (users_manager)

