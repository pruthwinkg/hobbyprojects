/*******************************************************************************
    Description : SmartHome Enum to String
    
    Usage : This header has to be included exclusively wherever the enum has to
            be defined. 

            It is recommended to define all the enums for a module in a sepearte
            header file. The header file should not contain anything other than
            enums. This will keep the code clean

*******************************************************************************/

//#ifndef INCLUDE_SMARTHOME_ENUM_TO_STR_H__ // DO NOT enable these lines !!!!!
//#define INCLUDE_SMARTHOME_ENUM_TO_STR_H__

#undef ADD_ENUM
#undef ADD_ENUM_VAL
#undef ADD_ENUM_STR
#undef ADD_ENUM_VAL_STR
#undef BEGIN_ENUM
#undef END_ENUM

#ifndef GENERATE_ENUM_STRINGS
    #define ADD_ENUM( element ) element,
    #define ADD_ENUM_VAL( element, value ) element = value,
    #define ADD_ENUM_STR( element, descr ) ADD_ENUM( element )
    #define ADD_ENUM_VAL_STR( element, value, descr ) ADD_ENUM_VAL( element, value )
    #define BEGIN_ENUM( ENUM_NAME ) typedef enum tag##ENUM_NAME
    #define END_ENUM( ENUM_NAME ) ENUM_NAME; \
            const char* GetString##ENUM_NAME(enum tag##ENUM_NAME index);
#else
    #define BEGIN_ENUM( ENUM_NAME) const char * GetString##ENUM_NAME( enum tag##ENUM_NAME index ) {\
        switch( index ) { 
    #define ADD_ENUM( element ) case element: return #element; break;
    #define ADD_ENUM_VAL( element, value ) ADD_ENUM( element )
    #define ADD_ENUM_STR( element, descr ) case element: return descr; break;
    #define ADD_ENUM_VAL_STR( element, value, descr ) ADD_ENUM_STR( element, descr )

    #define END_ENUM( ENUM_NAME ) default: return "Unknown value"; } } ;

#endif

//#endif /* INCLUDE_SMARTHOME_ENUM_TO_STR_H__ */
