/*******************************************************************************
    Description : Communication manager common header files for server and lib

*******************************************************************************/
#ifndef INCLUDE_COMM_MGR_CMN_H__
#define INCLUDE_COMM_MGR_CMN_H__

#include "smarthome_essentials.h"
#include "comm_mgr_cmn_enums.h"

#define SOCKET_FILE_PATH  "/tmp/smarthome_server.socket"

#define COMM_MGR_PACKET_MAX_SIZE    (4096)
#define COMM_MGR_HDR_SIZE           (256)
#define COMM_MGR_MSG_MAX_SIZE       (COMM_MGR_PACKET_MAX_SIZE-COMM_MGR_HDR_SIZE)

// Below are the list of port numbers used by this system (Use above 5000)
#define COMM_MGR_LOCAL_COM_PORT                 (5001) // Used for UDS based IPC

// Below structure defines the header for the comm mgr header
typedef struct {
    uint8_t magic_number; // Unique number to safeguard/delimit pkts
    COMM_MGR_MSG_TYPE msg_type;
    uint16_t src_uid;
    uint16_t dst_uid;
    boolean ack_required;
    int msg_backing_time;
    // Rest are reserved fields for now
} COMM_MGR_HDR;




#endif /* INCLUDE_COMM_MGR_CMN_H__ */ 
