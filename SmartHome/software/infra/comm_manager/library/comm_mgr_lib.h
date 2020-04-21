/*******************************************************************************
    Description : Communication Manager client library header file

*******************************************************************************/
#ifndef INCLUDE_COMM_MGR_LIB_H__
#define INCLUDE_COMM_MGR_LIB_H__

#include <netdb.h>
#include "smarthome_essentials.h"
#include "logging.h"
#include "utils.h"
#include "comm_mgr_lib_enums.h"
#include "comm_mgr_cmn.h"
#include "system_mgr.h"

#define COMM_MGR_LIB_NAME        "Communication Manager Library"

#define COMM_MGR_LIB_DEFAULT_SELECT_TIMEOUT     (5) // 5 seconds
#define COMM_MGR_LIB_DEFAULT_EPOLL_TIMEOUT     (5) // 5 seconds

#define COMM_MGR_LIB_ERROR  LOG_ERROR
#define COMM_MGR_LIB_TRACE  LOG_TRACE
#define COMM_MGR_LIB_DEBUG  LOG_DEBUG

#define COMM_MGR_LIB_PRINT  printf

#define COMM_MGR_LIB_MAX_CLIENTS        (4) // Even though 15 can be supported, limiting at 4
#define COMM_MGR_LIB_INVALID_CLIENT     (0xFFFF)
#define COMM_MGR_LIB_GET_CLIENT_ID(id)  (id & 0x0F)
#define COMM_MGR_LIB_GET_CLIENT_AF(id)  ((id & 0xF0) >> 4)

#define COMM_MGR_LIB_PROTO_QUEUE_SIZE       (10)  // This is set by lib

// Default. But can be changed by app during client creation
#define COMM_MGR_LIB_RECV_QUEUE_SIZE        (1024) 
#define COMM_MGR_LIB_SEND_QUEUE_SIZE        (1024)


// The last argument (void *) can be used to send complex datastrcuture
// If void *arg is used, then the corresponding dsid_cb should be able to
// tyoecast to apprioate type for that DSID and use it.
typedef COMM_MGR_LIB_ERR (*comm_mgr_lib_dsid_cb)(UTILS_DS_ID, char *, uint32_t, void *);


/*
    This is a application callback by the comm mgr library whenever there are some library
    events
*/
typedef void (*comm_mgr_lib_app_cb)(COMM_MGR_LIB_EVENT);

/*
    Use the COMM_MGR_LIB_CLIENT_ID to send/receive user data
    Format :               
        <8 bits> (Reserved) | <4 bits> (AF) | <4 bits (client id)>
*/
typedef uint16_t    COMM_MGR_LIB_CLIENT_ID;

/*
    This is a internal data structure used by lib client
    for maintaing meta info about the client.
*/
typedef struct {
    int __fd; 
    uint16_t __src_uid;             
    uint8_t __clientReady;          
    COMM_MGR_PROTO_STATES __proto_state;
    UTILS_DS_ID *__DSID;            /* In */ // Array of DSIDs
    comm_mgr_lib_dsid_cb *__dsid_cb;/* In */ // Array of Call back functions
    fd_set  __working_read_fd;
    fd_set  __working_write_fd;
} COMM_MGR_LIB_CLIENT_INTERNAL;

typedef struct {
    comm_mgr_lib_app_cb app_cb;
    uint16_t comm_mgr_lib_recv_queue_size;
    uint16_t comm_mgr_lib_send_queue_size;
    int libInactivityTimeOut; // In seconds
} COMM_MGR_LIB_CLIENT_PROPERTY;

// Data structure to hold client properties
typedef struct {
    COMM_MGR_LIB_IPC_AF clientAf;   /* In */
    struct hostent server;          /* In */
    int portNum;                    /* In */
    COMM_MGR_LIB_CLIENT_PROPERTY *property; /* In (Optional) If NULL, uses default */
    COMM_MGR_LIB_CLIENT_ID __clientID; /* Out */
    COMM_MGR_LIB_CLIENT_INTERNAL *client_ptr; /* For internal usage */
} COMM_MGR_LIB_CLIENT;

/*                      HOW TO USE THE LIBRARY TO GET DATA

    Notes: There are various ways for an app using this library to get useful information
    out of it.
        - The app can optionally register for a callback from the library for events.
        - The app can directly use some of the API provided by the library to get data/events
        - The app can also poll for COMM_MGR_LIB_STATUS

    The application has the liberty to mix & match above options available and build an custom
    and efficient solution according to its own needs

    Example : An app can register for a callback for events. This happens in the context of
    library thread. In the callback it can additionally consult COMM_MGR_LIB_EVENT_FLAGS for richer
    events. Then it can use the utils library event mechanism to send app-specific events to other
    threads OR set some app-specific flags/data. Also the other task handlers upon receving the 
    app-specific events, use some of the library APIs to extract information

*/

/*
    This struture can be used by the Apps which is using the Communication Library
    for getting various events. It is read-only by apps. The library does all the job
    of settting/clearing the flags

    The apps can build a Custom sophesticated event mechasims around this structure
    as well or simply it can even keep polling these flags periodically

    Note: This strcuture is referenced by using "cid" (Client ID)

    Also note that, there can be race conditions due to which the flags below might
    not be correct at the time of read if read by a different thread.
*/
#define COMM_MGR_LIB_RECV_STATUS_PENDING        (1 << 0)
#define COMM_MGR_LIB_RECV_STATUS_FULL           (1 << 1)

typedef struct {
    uint8_t comm_mgr_lib_data_recv_status;     // Various status regarding RECV DSID
    uint8_t comm_mgr_lib_generic_status;       // Library generic status
    uint8_t comm_mgr_lib_error_status;         // Library error status
} COMM_MGR_LIB_STATUS;

// Read-only copy used the by apps
const COMM_MGR_LIB_STATUS comm_mgr_lib_status_ro[COMM_MGR_LIB_MAX_CLIENTS];

/******************************************************************************/
/*          Public Functions                                                  */
/******************************************************************************/
COMM_MGR_LIB_ERR comm_mgr_lib_init(LOG_LEVEL level, uint16_t src_uid, boolean epoll_en);
COMM_MGR_LIB_ERR comm_mgr_lib_destroy(void);
COMM_MGR_LIB_CLIENT_ID comm_mgr_lib_create_client(COMM_MGR_LIB_CLIENT *client);
COMM_MGR_LIB_ERR comm_mgr_lib_delete_client(COMM_MGR_LIB_CLIENT_ID id);
COMM_MGR_LIB_ERR comm_mgr_lib_server_communicator(COMM_MGR_LIB_CLIENT_ID id);
COMM_MGR_MSG* comm_mgr_lib_recv_data(COMM_MGR_LIB_CLIENT_ID id);
COMM_MGR_LIB_ERR comm_mgr_lib_send_data(COMM_MGR_LIB_CLIENT_ID id, uint16_t dst_uid, 
                                        char *msg, int len);
COMM_MGR_LIB_ERR comm_mgr_lib_send_ack(COMM_MGR_LIB_CLIENT_ID id, uint16_t dst_uid, COMM_MGR_SUBMSG_TYPE submsg);                                        

/******************************************************************************/
/*          Internal Functions                                                */
/******************************************************************************/
static uint16_t __comm_mgr_lib_get_free_client(void);
static void __comm_mgr_lib_delete_client(COMM_MGR_LIB_CLIENT_ID id);
static COMM_MGR_LIB_ERR comm_mgr_set_non_blocking_io(int socket_fd);
static COMM_MGR_LIB_ERR  __comm_mgr_lib_receive_packets(COMM_MGR_LIB_CLIENT_ID id, 
                                                char *buffer, uint16_t bufsize);
static COMM_MGR_LIB_ERR __comm_mgr_lib_send_msg(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG_HDR *hdr,
                                        char *msg, int len);
static COMM_MGR_LIB_ERR __comm_mgr_lib_send_protocol(COMM_MGR_LIB_CLIENT *client, 
                                            COMM_MGR_SUBMSG_TYPE submsg_type,
                                            char *payload, uint16_t payloadsize);
static COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_handler(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg);
static COMM_MGR_LIB_ERR __comm_mgr_lib_ack_handler(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg);
static COMM_MGR_LIB_ERR __comm_mgr_lib_data_handler(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg);
static COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_statemachine(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg);
static COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_discovery_start(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg);
static COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_discovery_done(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg);
static COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_learning(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg);
static COMM_MGR_LIB_ERR __comm_mgr_lib_protocol_datatransfer_ready(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG *msg);
static COMM_MGR_LIB_ERR __comm_mgr_lib_update_local_uid_map(COMM_MGR_MSG *msg);
static boolean __comm_mgr_lib_is_uid_valid(uint16_t uid);
static boolean __comm_mgr_lib_is_uid_static(uint16_t uid);
static COMM_MGR_LIB_ERR __comm_mgr_lib_server_communicator_with_epoll(COMM_MGR_LIB_CLIENT_ID id);
static COMM_MGR_LIB_ERR __comm_mgr_lib_server_communicator_with_select(COMM_MGR_LIB_CLIENT_ID id);
#endif /* INCLUDE_COMM_MGR_LIB_H__ */
