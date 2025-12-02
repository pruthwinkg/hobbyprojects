/*******************************************************************************
                Description : MAPI library
*******************************************************************************/
#ifndef INCLUDE_MAPI_LIB_H__
#define INCLUDE_MAPI_LIB_H__

#include "mapi_internal.h"
#include "mapi_adv.h"

#define MAPI_MSG_SIZE(msg)          (sizeof(msg->hdr) + (msg->hdr.payloadSize))
#define MAPI_GET_MSG_HDR(msg)       (((MAPI_MSG *)msg)->hdr)
#define MAPI_GET_MSG_PAYLOAD(msg)   (((MAPI_MSG *)msg)->payload)

#define MAPI_LOCALHOST              (0x7F000001) // 127.0.0.1

/*
Each MAPI ID is bit resource intensive. It creates both internal and external sockets for each MAPI ID.
If we want to create multiple communication channels betweens two applications, we need to create multiple MAPI IDs.

So we need a light weight mechanism to create multiple communication channels between two applications. Hence we need to repurpose
the sub_mid field in the MAPI ID to create multiple communication channels for a single MAPI ID. Ofcourse, the apps still will be able to create 
multiple MAPI IDs if needed. But each mapi ID can now host multiple communication channels using the sub_mid field. It creates a logical sub-division
for a single MAPI ID. All the sub-mids of an MAPI ID will share  all the resources of the MAPI ID. By default each MAPI ID will have 1 sub-mid.
This will be applicable for both DGRAM and STREAM modes to keep the interface consistent.

The sub-mids are resolved at the destination in the MAPI library receive callback. The sub-mids are sent as part of the message header.

The sub-mids must be created along with MID. Cannot create sub-mids for a MID after the MID is started. They are sequentially numbered starting from 0 to max sub-mids.

Max sub-mids per MAPI ID = 16


Purpose of dst_sub_mid (think of it like channel)

Use Cases of dst_sub_mid:
    Multiple Services Within an Application:
    Multiple Instances of a Service:
    Different Communication Channels:


    UID-A
    MID-A-0 (sub-mid = 0, sub-mid = 1, sub-mid = 2, sub-mid = 3)
    MID-A-1 (sub-mid = 0, sub-mid = 1, sub-mid = 2)


    UID-B
    MID-B-0 (sub-mid = 0, sub-mid = 1, sub-mid = 2)
    MID-B-1 (sub-mid = 0, sub-mid = 1, sub-mid = 2, sub-mid = 3)

    In DGRAM mode, MID-A-0-0 can send message to any MID-B-x-y
    In STREAM mode, MID-A-0-0 need to create channel with MID-B-0-2 using mapi_start_stream()
            Now MID-A-0-0 ========== MID-B-0-2 (Allowed)
            Now MID-A-0-0 ========== MID-B-0-1 (Not Allowed)

*/
typedef struct {    
    uint8_t num_sub_mids;
    MAPI_LIB_SOCK_TYPE sock_type;
    uint8_t num_ports;
    uint16_t *port_nums;
    boolean reuseaddr;              /* In */
    boolean nonblockingIO;          /* In */
    boolean use_epoll;              /* In */
    mapi_receive_cb rcv_cb;
    MAPI_USER_ADVANCED_CONFIG *adv_config; // Set to NULL if not needed
} MAPI_USER_INFO;

typedef struct {
    uint32_t magic; // MAGIC number for MAPI
    uint8_t major_ver; // Version number of Header
    uint8_t minor_ver; // Version number of Header
    uint32_t dst_ip; // User provided
    uint32_t src_ip; // MAPI provided
    uint32_t dst_port; // User provided
    uint32_t src_port; // MAPI provided
    mapiID   dst_mid; // UID | MID
    mapiID   src_mid; // UID | MID
    uint8_t  dst_sub_mid;  // User provided
    uint8_t  src_sub_mid; // MAPI provided
    uint32_t messageCode; // User provided
    uint32_t payloadSize; // User provided
} MAPI_MSG_HDR;

typedef struct {
    MAPI_MSG_HDR hdr;
    char *payload;
} MAPI_MSG;

typedef struct {
    uint32_t dst_ip;
    uint16_t dst_port;
    mapiID  dst_mid; // UID | MID
    uint8_t dst_sub_mid;
} MAPI_DEST_INFO;

typedef struct {
    uint16_t src_port;        /**< If non-zero, overrides the default source port selection. */
    uint32_t messageCode;      /**< If non-zero, the new msg code will be used.*/
    mapiID   dst_mid;          /**< If non-zero, the new MID will be used.*/
    uint8_t  dst_sub_mid;      /**< If non-zero, the new submid will be used.*/
    uint8_t  src_sub_mid;      /**< If non-zero, the new submid will be used.*/
    uint8_t  reserved_1;       /**< Reserved for future use. */
    uint8_t  reserved_2;       /**< Reserved for future use. */    
    uint32_t reserved_3;       /**< Reserved for future use. */
} MAPI_SEND_OPTIONS;


/*******************************************************************************/
/*                      Public functions                                       */
/*******************************************************************************/
/**
 * @file mapi.h
 * @brief This file contains the function declarations for the MAPI (Messaging API) library.
 */

/**
 * @brief Initializes the MAPI library.
 *
 * @param level The logging level to be used by the library.
 * @param max_mids The maximum number of MAPI IDs that can be created.
 * @param src_uid The source user ID.
 * @param src_ip The source IP address.
 */
void mapi_init(LOG_LEVEL level, uint8_t max_mids, uint16_t src_uid, uint32_t src_ip) ;

/**
 * @brief Creates a new MAPI ID for a user.
 *
 * @param user_info Pointer to the user information structure.
 * @return The created MAPI ID.
 */
mapiID mapi_create_mid(MAPI_USER_INFO *user_info);

/**
 * @brief Starts the MAPI session for the given MAPI ID.
 *         Recommended to call this function in a separate thread.
 *
 * @param mid The MAPI ID.
 * @return The result of the operation.
 */
MAPI_LIB_ERR mapi_start_mid(mapiID mid);

/**
 * @brief Sends a message using the MAPI library.
 *
 * @param mid The MAPI ID.
 * @param dst_info Pointer to the destination information structure.
 * @param messageCode The message code.
 * @param msg Pointer to the message to be sent.
 * @param len The length of the message.
 * @param options Pointer to a MAPI_SEND_OPTIONS struct, or NULL for default behavior.
 * @return The result of the operation.
 */
MAPI_LIB_ERR mapi_send(mapiID mid, MAPI_DEST_INFO *dst_info, uint32_t messageCode, char *msg, uint32_t len, MAPI_SEND_OPTIONS *options);

/**
 * @brief Destroys the MAPI session for the given MAPI ID.
 *
 * @param mid The MAPI ID.
 */
void mapi_destroy(mapiID mid);

// Functions to start/stop streams with a destination - Only in STREAM mode
MAPI_LIB_ERR mapi_start_stream(mapiID mid, MAPI_DEST_INFO *dst_info);
MAPI_LIB_ERR mapi_stop_stream(mapiID mid, MAPI_DEST_INFO *dst_info);
MAPI_LIB_ERR mapi_set_stream_store_type(mapiID mid, uint8_t type, uint16_t size); // Use only if needed

// Functions to tweak default set values, if needed
MAPI_LIB_ERR mapi_set_internal_packet_size(mapiID mid, uint16_t size);
MAPI_LIB_ERR mapi_set_external_packet_size(mapiID mid, uint16_t size);


#endif /* INCLUDE_MAPI_LIB_H__  */
