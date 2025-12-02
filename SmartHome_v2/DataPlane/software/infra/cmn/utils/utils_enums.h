/*******************************************************************************
    Description: Contains all the enums required for the utilties library
   
*******************************************************************************/

#include "smarthome_essentials.h"

BEGIN_ENUM(UTILS_DS_LIB_MODE) {
    ADD_ENUM_STR(UTILS_DS_LIB_MODE_CPP, "Use STL C++ libraries only")
    ADD_ENUM_STR(UTILS_DS_LIB_MODE_STD, "Use standard mode")
    ADD_ENUM_STR(UTILS_DS_LIB_MODE_MIXED, "Use both CPP and STD. (Recommended)")
} END_ENUM(UTILS_DS_LIB_MODE);
