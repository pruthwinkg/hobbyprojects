/*******************************************************************************
    Description : SmartHome essential header. It is sufficient to include only
            this header in software.

*******************************************************************************/

#ifndef INCLUDE_SMARTHOME_ESSENTIALS_H__
#define INCLUDE_SMARTHOME_ESSENTIALS_H__


#include "smarthome_error.h"
#include "smarthome_types.h"
#include "smarthome_subsystems.h"

// Use the Below Macro to display any enum in string format
#define DECODE_ENUM(Enum, Elem)   GetString##Enum((Enum)Elem)


#endif /* INCLUDE_SMARTHOME_ESSENTIALS_H__ */
