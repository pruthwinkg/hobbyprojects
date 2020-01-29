/*******************************************************************************
    Description : Communication manager common header files for server and lib

*******************************************************************************/
#ifndef INCLUDE_COMM_MGR_CMN_H__
#define INCLUDE_COMM_MGR_CMN_H__

#include "smarthome_essentials.h"
#include "comm_mgr_cmn_enums.h"

#define SOCKET_FILE_PATH  "/tmp/smarthome_server.socket"

#define COMM_MGR_PACKET_MAX_SIZE    (4096) // bytes
#define COMM_MGR_HDR_SIZE           (128)  // bytes
#define COMM_MGR_MSG_MAX_SIZE       (COMM_MGR_PACKET_MAX_SIZE-COMM_MGR_HDR_SIZE)

// Below are the list of port numbers used by this system (Use above 5000)
#define COMM_MGR_LOCAL_COM_PORT     (5001) // Used for UDS based IPC

#define COMM_MGR_MSG_HDR_MAGIC      (0x1357)
#define COMM_MGR_MSG_PROTOCOL_MAGIC (0xCAFE)
// Communication Manager msg versions (For portability purpose)
#define COMM_MGR_MSG_HDR_MAJOR_VER      (0)
#define COMM_MGR_MSG_HDR_MINOR_VER      (1)

// Below structure defines the header for the comm mgr header
typedef struct {
    uint32_t magic; // Unique number to safeguard/delimit pkts
    uint8_t major_ver; // Version number of Header
    uint8_t minor_ver;
    COMM_MGR_MSG_TYPE msg_type;
    COMM_MGR_SUBMSG_TYPE submsg_type;
    uint16_t src_uid;
    uint16_t dst_uid;
    COMM_MGR_MSG_PRIORITY priority;
    boolean ack_required;
    uint8_t msg_backing_time; // in minutes (max of 120 mins=2hrs) 
    uint16_t payloadSize;
    // Rest are reserved fields for now
} COMM_MGR_MSG_HDR;

typedef struct {
    COMM_MGR_MSG_HDR hdr;
    char *payload;
} COMM_MGR_MSG;


/*********************************************************************************
                                Public Functions
**********************************************************************************/
COMM_MGR_MSG* comm_mgr_create_msg(uint16_t src_uid, uint16_t dst_uid, 
                                 COMM_MGR_MSG_TYPE msg_type, char *payload, 
                                 uint16_t payloadSize);
COMM_MGR_MSG* comm_mgr_get_msg(char *msg, uint16_t len);
void comm_mgr_print_msg_hdr(COMM_MGR_MSG *msg, char *buf, uint16_t len);
#endif /* INCLUDE_COMM_MGR_CMN_H__ */ 
