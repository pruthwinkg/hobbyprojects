/*****************************************************************************
    Description : This is the library library for interfacing with various
        componens of this system
******************************************************************************/
#ifndef INCLUDE_INTERFACE_LIB_H__
#define INCLUDE_INTERFACE_LIB_H__

#include "logging.h"
#include "interface_cmn.h"

#define INTERFACE_LOG_ERROR  LOG_ERROR
#define INTERFACE_LOG_TRACE  LOG_TRACE
#define INTERFACE_LOG_DEBUG  LOG_DEBUG

#define INTERFACE_LIB_RES_BUF_SIZE      (8096) // 8KB

// Flags
#define INTERFACE_LIB_RES_IS_PENDING    (1 << 0)
#define INTERFACE_LIB_RES_IS_HEADER     (1 << 1)

#define INTERFACE_LIB_SET_FLAG(x,f)         (x  |= f)
#define INTERFACE_LIB_CLEAR_FLAG(x,f)       (x  &= ~f)
#define INTERFACE_LIB_IS_FLAG_SET(x, f)     (x & f)

typedef enum {
    INTERFACE_LIB_SUCCESS = 0,
    INTERFACE_LIB_FAILURE,
    INTERFACE_LIB_NOT_INTIALIZED,
    INTERFACE_LIB_BAD_QUERY,
    INTERFACE_LIB_BAD_STATE,
    INTERFACE_LIB_UNSUPPORTED_QUERY_TYPE,
    INTERFACE_LIB_APP_RESPONSE_PENDING,
} INTERFACE_LIB_ERR;

typedef enum {
    INTERFACE_LIB_SECURE_LEVEL_CRITICAL = 0,
    INTERFACE_LIB_SECURE_LEVEL_HIGH,
    INTERFACE_LIB_SECURE_LEVEL_NORMAL,
    INTERFACE_LIB_SECURE_LEVEL_UNSECURE
} INTERFACE_LIB_SECURE_LEVEL;

// At any point of time, an app can change the state of its interface
typedef enum {
    INTERFACE_LIB_STATE_ALLOW = 0,
    INTERFACE_LIB_STATE_DENY,
    INTERFACE_LIB_STATE_RETRY
} INTERFACE_LIB_STATE;

typedef struct {
    INTERFACE_LIB_SECURE_LEVEL level;
    INTERFACE_LIB_STATE state;
} INTERFACE;

typedef struct {
    uint16_t magic_num; // 2 byte
    char identifier[INTERFACE_LIB_IDENTIFIER_SIZE]; // 2 byte
    uint8_t query_type; // 1 byte (INTERFACE_LIB_QUERY_TYPE)
    uint8_t query_req; // Query request format (INTERFACE_LIB_QUERY_REQ_TYPE)
    uint8_t response_type; // 1 byte
    char *query; // It can any type
} INTERFACE_QUERY;

// This has to be in same order as INTERFACE_LIB_QUERY_TYPE
static const char* interface_query_type_str[] = {
    "Text",
    "Json",
    "Script"
};

// This has to be in same order as INTERFACE_LIB_QUERY_REQ_TYPE
static const char* interface_query_req_type_str[] = {
    "Token",
    "FullQuery"
};


typedef INTERFACE_LIB_ERR (*interface_req_cb)(INTERFACE_LIB_QUERY_REQ_TYPE, const char *, char *, uint16_t);
typedef INTERFACE_LIB_ERR (*interface_res_cb)(INTERFACE_LIB_QUERY_RES_TYPE, const char *, void *, uint16_t);

typedef struct {
    interface_req_cb text_cb;   // request callback 
    interface_req_cb json_cb;   // request callback 
    interface_req_cb script_cb; // request callback
    interface_res_cb response_cb;   // response callback
} INTERFACE_APP_CB;


/******************************************************************************/
/*                          Public Functions                                  */
/******************************************************************************/
INTERFACE_LIB_ERR interface_lib_init(INTERFACE_LIB_SECURE_LEVEL level, INTERFACE_APP_CB *app_cb);
INTERFACE_LIB_ERR interface_lib_process_query(uint16_t req_uid, uint16_t res_uid, char *buf, uint16_t bufsize, void *arg);
INTERFACE_LIB_ERR interface_lib_change_state(INTERFACE_LIB_STATE state);

/******************************************************************************/
/*                          Private Functions                                  */
/******************************************************************************/
static INTERFACE_LIB_ERR interface_lib_process_text_query(uint16_t req_uid, uint16_t res_uid, INTERFACE_QUERY *query, void *arg);
static INTERFACE_LIB_ERR interface_lib_create_response(INTERFACE_QUERY *query, uint16_t req_uid, uint16_t res_uid, void *arg); 


#endif /* INCLUDE_INTERFACE_LIB_H__ */


