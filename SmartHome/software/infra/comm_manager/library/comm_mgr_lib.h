/*******************************************************************************
    Description : Communication Manager client library header file

*******************************************************************************/
#ifndef INCLUDE_COMM_MGR_LIB_H__
#define INCLUDE_COMM_MGR_LIB_H__

#include <netdb.h>
#include "smarthome_essentials.h"
#include "logging.h"
#include "comm_mgr_lib_enums.h"
#include "comm_mgr_cmn.h"

#define COMM_MGR_LIB_NAME        "Communication Manager Library"

#define COMM_MGR_LIB_ERROR  LOG_ERROR
#define COMM_MGR_LIB_TRACE  LOG_TRACE
#define COMM_MGR_LIB_DEBUG  LOG_DEBUG


// Data structure to hold client properties
typedef struct {
    COMM_MGR_LIB_IPC_AF clientAf;   /* In */
    struct hostent server;          /* In */
    int portNum;                    /* In */
    int __fd;                       /* Out */
    uint16_t __src_uid;             /* Out */
    uint8_t __clientReady;          /* Out */
} COMM_MGR_LIB_CLIENT;


/******************************************************************************/
/*          Public Functions                                                  */
/******************************************************************************/
COMM_MGR_LIB_ERR comm_mgr_lib_init(LOG_LEVEL level);
COMM_MGR_LIB_ERR comm_mgr_lib_destroy(void);
COMM_MGR_LIB_ERR comm_mgr_lib_create_client(COMM_MGR_LIB_CLIENT *client);
COMM_MGR_LIB_ERR comm_mgr_lib_send_msg(COMM_MGR_LIB_CLIENT *client, COMM_MGR_MSG_HDR *hdr,
                                        char *msg, int len);
COMM_MGR_LIB_ERR comm_mgr_lib_send_data(COMM_MGR_LIB_CLIENT *client, uint16_t dst_uid, 
                                        char *msg, int len);
COMM_MGR_LIB_ERR comm_mgr_lib_send_ack(COMM_MGR_LIB_CLIENT *client, uint16_t dst_uid);                                        
COMM_MGR_LIB_ERR comm_mgr_lib_send_protocol(COMM_MGR_LIB_CLIENT *client, 
                                            COMM_MGR_SUBMSG_TYPE submsg_type);

COMM_MGR_LIB_ERR comm_mgr_lib_recv_data(COMM_MGR_LIB_CLIENT *client, char *msg, int len);

#endif /* INCLUDE_COMM_MGR_LIB_H__ */
