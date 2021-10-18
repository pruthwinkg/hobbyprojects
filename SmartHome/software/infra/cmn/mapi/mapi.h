/*******************************************************************************
                Description : MAPI library
*******************************************************************************/
#ifndef INCLUDE_MAPI_LIB_H__
#define INCLUDE_MAPI_LIB_H__

#include "mapi_internal.h"

#define MAPI_MSG_SIZE(msg)          (sizeof(msg->hdr) + (msg->hdr.payloadSize))
#define MAPI_GET_MSG_HDR(msg)       (((MAPI_MSG *)msg)->hdr)
#define MAPI_GET_MSG_PAYLOAD(msg)   (((MAPI_MSG *)msg)->payload)

#define MAPI_LOCALHOST              (0x7F000001) // 127.0.0.1

typedef struct {    
    uint8_t sub_mid; // Needed for multiple MAPI ID support
    MAPI_LIB_SOCK_TYPE sock_type;
    uint16_t port_num;
    boolean reuseaddr;              /* In */
    boolean nonblockingIO;          /* In */
    mapi_receive_cb rcv_cb;
} MAPI_USER_INFO;

typedef struct {
    uint32_t magic; // MAGIC number for MAPI
    uint8_t major_ver; // Version number of Header
    uint8_t minor_ver; // Version number of Header
    uint32_t dst_ip; // User provided
    uint32_t src_ip; // MAPI provided
    uint32_t dst_port; // User provided
    uint32_t src_port; // MAPI provided
    uint16_t dst_uid; // User provided
    uint16_t src_uid; // MAPI provided
    uint32_t messageCode; // User provided
    uint32_t payloadSize; // User provided
} MAPI_MSG_HDR;

typedef struct {
    MAPI_MSG_HDR hdr;
    char *payload;
} MAPI_MSG;

typedef struct {
    uint8_t dst_sub_mid;
    uint16_t dst_uid;
    uint16_t dst_port;
    uint32_t dst_ip;
} MAPI_DEST_INFO;

/*******************************************************************************/
/*                      Public functions                                       */
/*******************************************************************************/
void mapi_init(LOG_LEVEL level, uint16_t src_uid, uint32_t src_ip);
mapiID mapi_create_mid(MAPI_USER_INFO *user_info);
MAPI_LIB_ERR mapi_start_mid(mapiID mid);
MAPI_LIB_ERR mapi_send(mapiID mid, MAPI_DEST_INFO *dst_info, uint32_t messageCode, char *msg, uint32_t len);
void mapi_destroy(mapiID mid);

// Functions to start/stop streams with a destination - Only in STREAM mode
MAPI_LIB_ERR mapi_start_stream(mapiID mid, MAPI_DEST_INFO *dst_info);
MAPI_LIB_ERR mapi_stop_stream(mapiID mid, MAPI_DEST_INFO *dst_info);
MAPI_LIB_ERR mapi_set_stream_store_type(mapiID mid, uint8_t type, uint16_t size); // Use only if needed

// Functions to tweak default set values, if needed
MAPI_LIB_ERR mapi_set_internal_packet_size(mapiID mid, uint16_t size);
MAPI_LIB_ERR mapi_set_external_packet_size(mapiID mid, uint16_t size);


#endif /* INCLUDE_MAPI_LIB_H__  */
