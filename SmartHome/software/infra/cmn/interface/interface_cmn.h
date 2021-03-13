/*****************************************************************************
    Description : This is the library library for interfacing with various
        componens of this system

    This file is used by various interfacing apps like shell to talk to the 
    interface library
******************************************************************************/
#ifndef INCLUDE_INTERFACE_CMN_H__
#define INCLUDE_INTERFACE_CMN_H__

#define INTERFACE_LIB_MAGIC_NUM         (0xFACE)

/* 
    There can be multiple versions of the interface library. This is used to identify the
    interface library version the requesting app is using
*/
#define INTERFACE_LIB_IDENTIFIER_SIZE   2
#define INTERFACE_LIB_IDENTIFIER_V1     0x0001

#define INTERFACE_LIB_IDENTIFIER        INTERFACE_LIB_IDENTIFIER_V1
#define INTERFACE_QUERY_HEADER_SIZE     (8) // In bytes
#define INTERFACE_LIB_MAX_QUERY_SIZE    (50) // In bytes

/*
    i  : INTERFACE_LIB_IDENTIFIER
    t  : INTERFACE_LIB_QUERY_TYPE
    rt : INTERFACE_LIB_QUERY_REQ_TYPE
    rl : Response location (For example file descriptor)
    q  : Query (Can be a simple token, split query, full query etc)
    buf: Buffer where the formatted query is stored

    This inline function returns the size of the buf 
*/
inline uint16_t interface_lib_get_query(uint16_t id, uint8_t type, uint8_t req_type, 
                               uint16_t res_loc, void *query, uint8_t query_len, char *buf)  {
    uint16_t interface_lib_magic = INTERFACE_LIB_MAGIC_NUM;
    uint16_t bufsize = 0;
    memcpy(&buf[0], &interface_lib_magic, sizeof(uint16_t));
    memcpy(&buf[2], &id, sizeof(uint16_t));
    buf[INTERFACE_LIB_IDENTIFIER_SIZE+2] = type;
    buf[INTERFACE_LIB_IDENTIFIER_SIZE+3] = req_type;
    memcpy(&buf[INTERFACE_LIB_IDENTIFIER_SIZE+4], &res_loc, sizeof(uint16_t));
    if(req_type == 0) {
       memcpy(&buf[INTERFACE_LIB_IDENTIFIER_SIZE+6], query, sizeof(uint16_t));
       bufsize = sizeof(char) * (INTERFACE_LIB_IDENTIFIER_SIZE+8);
    } else if(req_type == 1) {
        
    } else if(req_type == 2) {
        memcpy(&buf[INTERFACE_LIB_IDENTIFIER_SIZE+6], query, query_len);
        bufsize = strlen(query) + (sizeof(char) * (INTERFACE_LIB_IDENTIFIER_SIZE+6));
    }
    return bufsize;    
}


#endif /* INCLUDE_INTERFACE_CMN_H__ */
