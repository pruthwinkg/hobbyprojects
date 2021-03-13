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
    uint16_t response_loc; // 2 byte
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


typedef INTERFACE_LIB_ERR (*interface_cb)(INTERFACE_LIB_QUERY_REQ_TYPE, const char *, char *, uint16_t);

typedef struct {
    interface_cb text_cb;
    interface_cb json_cb;
    interface_cb script_cb;
} INTERFACE_APP_CB;


/******************************************************************************/
/*                          Public Functions                                  */
/******************************************************************************/
INTERFACE_LIB_ERR interface_lib_init(INTERFACE_LIB_SECURE_LEVEL level, INTERFACE_APP_CB *app_cb);
INTERFACE_LIB_ERR interface_lib_process_query(uint16_t req_uid, uint16_t res_uid, char *buf, uint16_t bufsize);
INTERFACE_LIB_ERR interface_lib_change_state(INTERFACE_LIB_STATE state);

/******************************************************************************/
/*                          Private Functions                                  */
/******************************************************************************/
static INTERFACE_LIB_ERR interface_lib_process_text_query(uint16_t req_uid, uint16_t res_uid, INTERFACE_QUERY *query);
static INTERFACE_LIB_ERR interface_lib_create_response(uint16_t fd, uint16_t req_uid, uint16_t res_uid,
                                                       const char *query_type, const char *query_req_type,
                                                       const char *query);
static INTERFACE_LIB_ERR interface_lib_write_response(uint16_t fd, const char *buf, boolean isResPending);
                                                       


#endif /* INCLUDE_INTERFACE_LIB_H__ */


