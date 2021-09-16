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
    The write/read fd functions can be used by the apps to write/read
    responses/requests which is coming from various interfacing apps like shell/UI etc.

    The fd can be a simple file or even a direct socket
*/
static inline interface_lib_write_fd(int fd, const char *buf) {
	
}

static inline interface_lib_read_fd(int fd, char *buf) {

}

typedef enum {
    INTERFACE_LIB_QUERY_TYPE_TEXT = 0, // used for cli type apps
    INTERFACE_LIB_QUERY_TYPE_JSON,
    INTERFACE_LIB_QUERY_TYPE_SCRIPT,
} INTERFACE_LIB_QUERY_TYPE;

/* Various supported query request types */
typedef enum {
    INTERFACE_LIB_QUERY_REQ_TYPE_TOKEN = 0, // easy and faster
    INTERFACE_LIB_QUERY_REQ_TYPE_SPLIT_QUERY, // Full query is split into many words
    INTERFACE_LIB_QUERY_REQ_TYPE_FULL_QUERY
} INTERFACE_LIB_QUERY_REQ_TYPE;

typedef enum {
    INTERFACE_LIB_QUERY_RES_FD = 0, // Response is via files
    INTERFACE_LIB_QUERY_RES_ANC_MSG, // Response via Ancillary messages
} INTERFACE_LIB_QUERY_RES_TYPE;

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
                               uint8_t res_type, void *query, uint8_t query_len, char *buf)  {
    uint16_t interface_lib_magic = INTERFACE_LIB_MAGIC_NUM;
    uint16_t bufsize = 0;
    memcpy(&buf[0], &interface_lib_magic, sizeof(uint16_t));
    memcpy(&buf[2], &id, sizeof(uint16_t));
    buf[INTERFACE_LIB_IDENTIFIER_SIZE+2] = type;
    buf[INTERFACE_LIB_IDENTIFIER_SIZE+3] = req_type;
    buf[INTERFACE_LIB_IDENTIFIER_SIZE+4] = res_type;
    if(req_type == 0) {
       memcpy(&buf[INTERFACE_LIB_IDENTIFIER_SIZE+5], query, sizeof(uint16_t));
       bufsize = sizeof(char) * (INTERFACE_LIB_IDENTIFIER_SIZE+8);
    } else if(req_type == 1) {
        
    } else if(req_type == 2) {
        memcpy(&buf[INTERFACE_LIB_IDENTIFIER_SIZE+5], query, query_len);
        bufsize = strlen(query) + (sizeof(char) * (INTERFACE_LIB_IDENTIFIER_SIZE+5));
    }
    return bufsize;    
}


#endif /* INCLUDE_INTERFACE_CMN_H__ */
