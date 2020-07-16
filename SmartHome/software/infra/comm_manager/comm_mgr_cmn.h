/*******************************************************************************
    Description : Communication manager common header files for server and lib

*******************************************************************************/
#ifndef INCLUDE_COMM_MGR_CMN_H__
#define INCLUDE_COMM_MGR_CMN_H__

#include "smarthome_essentials.h"
#include "comm_mgr_cmn_enums.h"

// Various socket types supported
#define SOCKET_FILE_PATH  		"/tmp/smarthome_server.socket"
#define ANC_SOCKET_FILE_PATH  	"/tmp/smarthome_server.anc_socket"

#define COMM_MGR_PACKET_MAX_SIZE    (64 * 1024 * 1024) // 64 Kbytes
#define COMM_MGR_HDR_SIZE           (128)  // bytes
#define COMM_MGR_MSG_MAX_SIZE       (COMM_MGR_PACKET_MAX_SIZE-COMM_MGR_HDR_SIZE)

// Below are the list of port numbers used by this system (Use above 5000)
#define COMM_MGR_LOCAL_COM_PORT     (5001) // Used for UDS based IPC

#define COMM_MGR_MSG_HDR_MAGIC      (0x1357)
#define COMM_MGR_MSG_PROTOCOL_MAGIC (0xCAFE)
#define COMM_MGR_MSG_ANC_HDR_MAGIC  (0x2468)
// Communication Manager msg versions (For portability purpose)
#define COMM_MGR_MSG_HDR_MAJOR_VER      (0)
#define COMM_MGR_MSG_HDR_MINOR_VER      (1)

#define COMM_MGR_MSG_ANC_HDR_MAJOR_VER      (0)
#define COMM_MGR_MSG_ANC_HDR_MINOR_VER      (1)


// Standard Protocol Payload sizes (In bytes)
#define COMM_MGR_MSG_PROTOCOL_SRV_DISCOVERY_SIZE     (12) // Sent by Server to Client
#define COMM_MGR_MSG_PROTOCOL_LIB_DISCOVERY_SIZE     (4)  // Sent by client to Server
#define COMM_MGR_MSG_PROTOCOL_SRV_LEARNING_SIZE      (6)  // Always sent by Server to client

/*
    Ancillary send is a new feature added to the communication manager
    to support some advacned send mechanism.

    By default it is enabled. If disabled, normal send with NO ancillary support will be enabled
*/
#define COMM_MGR_USE_ANCILLARY_SEND      	(TRUE)    // By default enabled
#define COMM_MGR_MAX_ANCILLARY_FD        	(2)    // Max number of file descriptors currently supported
#define COMM_MGR_MAX_ANCILLARY_INTERNAL_IOV (3)	   // Number of internal IOVs used by Communication Manager
#define COMM_MGR_MAX_ANCILLARY_USER_IOV     (1)    // Max number of non-contagious buffers which needs to sent
#define COMM_MGR_MAX_ANCILLARY_RECV_BUFFER	(16 * 1024) // 16KB

#define COMM_MGR_MAX_ANCILLARY_IOV_SIZE     (256) // 256 bytes
#define COMM_MGR_MAX_NORMAL_MODE_RECV_BUFFER	(8 * 1024)

typedef uint8_t COMM_MGR_FLAG;

// These flags define the behaviour of comm_mgr_send/comm_mgr_recv functions
#define COMM_MGR_FLAG_MODE_DEFAULT			(0)		 // Use a default behaviour. The function decides how to send
#define COMM_MGR_FLAG_MODE_NORMAL			(1 << 0) // Use regular mode. In this vectors/fds are not supported
#define COMM_MGR_FLAG_MODE_FD				(1 << 1) // Send/Recv FDs
#define COMM_MGR_FLAG_MODE_VECTOR			(1 << 2) // Send/Recv vectors
#define COMM_MGR_FLAG_MODE_BLOCKING			(1 << 3) // Make the send/recv a blocking call
#define COMM_MGR_FLAG_MODE_STRICT			(1 << 4) // Checks for each and every condition (Not applicable for Normal mode)

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

// This defines the header for the comm mgr ancillary packets
typedef struct {
	uint32_t magic; // Unique number to safeguard/delimit pkts
	uint8_t major_ver;
	uint8_t minor_ver;
	COMM_MGR_ANC_MSG_TYPE anc_msg_type;
	uint8_t num_fd;
	uint8_t num_vec;
} COMM_MGR_ANC_MSG_HDR;

typedef struct {
	COMM_MGR_ANC_MSG_HDR hdr;
	uint32_t *fds;
	uint8_t *nPayloadSize;
	char **payloads;
} COMM_MGR_ANC_MSG;


#define COMM_MGR_MSG_SIZE(msg)  (sizeof(COMM_MGR_MSG_HDR) + (msg->hdr.payloadSize * sizeof(char)))
#define COMM_MGR_GET_ANC_MSG(msg)	((COMM_MGR_ANC_MSG *)msg->payload) // Payload is overrided

/*********************************************************************************
                                Public Functions
**********************************************************************************/
COMM_MGR_MSG* comm_mgr_create_msg(uint16_t src_uid, uint16_t dst_uid, 
                                 COMM_MGR_MSG_TYPE msg_type, char *payload, 
                                 uint16_t payloadSize);
COMM_MGR_MSG comm_mgr_create_msg_hdr(uint16_t src_uid, uint16_t dst_uid, 
                                    COMM_MGR_MSG_TYPE msg_type, 
                                    uint16_t payloadSize);
COMM_MGR_MSG* comm_mgr_get_msg(char *msg, uint16_t len);
COMM_MGR_MSG* comm_mgr_get_next_msg(char *msg);
void comm_mgr_print_msg_hdr(COMM_MGR_MSG *msg, char *buf, uint16_t len);

void comm_mgr_destroy_msg(COMM_MGR_MSG *msg);
void comm_mgr_destroy_anc_msg(COMM_MGR_MSG *msg);
COMM_MGR_CMN_ERR comm_mgr_send(int sock, COMM_MGR_FLAG flag, COMM_MGR_MSG *comm_msg);
COMM_MGR_CMN_ERR comm_mgr_recv(int sock, COMM_MGR_FLAG flag, COMM_MGR_MSG **msg[], uint8_t *num_msgs);

static COMM_MGR_CMN_ERR __comm_mgr_send_with_ancillary_msg(int fd,
                                                           COMM_MGR_MSG_HDR *comm_hdr,
                                                           COMM_MGR_ANC_MSG *anc_msg);
static COMM_MGR_CMN_ERR __comm_mgr_recv_with_ancillary_msg(int fd,
                                                           COMM_MGR_MSG_HDR *comm_hdr,
                                                           COMM_MGR_ANC_MSG *anc_msg);
static void comm_mgr_datastream_thread_init(void);

#endif /* INCLUDE_COMM_MGR_CMN_H__ */ 
