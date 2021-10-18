/*******************************************************************************
                Description : MAPI library
*******************************************************************************/
#ifndef INCLUDE_MAPI_INTERNAL_LIB_H__
#define INCLUDE_MAPI_INTERNAL_LIB_H__

#include "smarthome_essentials.h"
#include "logging.h"
#include "utils.h"
#include "mapi_enums.h"

#define MAPI_LIB_NAME "MAPI Library"

#define MAPI_MAX_MIDS           10 /* This is per APP */
#define MAPI_GET_UID(mid)       ((mid & 0xFFFF0000) >> 16)
#define MAPI_GET_SUB_MID(mid)   (mid & 0x0000FFFF)
#define MAPI_SOCK_BACKLOG       32
#define MAPI_DEFAULT_SELECT_TIMEOUT 5 // 5 mins
#define MAPI_DEFAULT_EPOLL_TIMEOUT  5 // 5 mins
#define MAPI_DEFAULT_INTERNAL_PKT_SIZE  32*1024
#define MAPI_DEFAULT_EXTERNAL_PKT_SIZE  32*1024
#define MAPI_MSG_HDR_MAGIC  0xACED
#define MAPI_MSG_HDR_MAJOR_VER  0
#define MAPI_MSG_HDR_MINOR_VER  1


#define MAPI_LOG_ERROR  LOG_ERROR
#define MAPI_LOG_TRACE  LOG_TRACE
#define MAPI_LOG_DEBUG  LOG_DEBUG

#define MAPI_INVALID_ID         0xFFFFFFFF

// Stream status
#define MAPI_STREAM_STATUS_READY      (1 << 0)

// Stream storage type
#define MAPI_STREAM_STORE_TREE          0
#define MAPI_STREAM_STORE_LINKEDLIST    1 // Default type
#define MAPI_STREAM_STORE_HASH          2
#define MAPI_STREAM_STORE_QUEUE         3 // Limited streams per mid

#define MAPI_STREAM_STORE_QUEUE_DEFAULT_MAX_SIZE    10

typedef uint32_t mapiID;
typedef void (*mapi_receive_cb)(char *buffer, uint32_t buflen);

extern boolean mapi_initialized;

typedef struct {
    uint8_t dst_sub_mid;
    uint16_t dst_uid;
    uint16_t dst_port;
    uint32_t dst_ip;
    int stream_fd;
    uint32_t status_flag;
} MAPI_STREAM_INTERNAL_ENTRY;

typedef struct {
    uint8_t stream_storage_type;
    uint8_t stream_storage_initialized;
    uint16_t stream_storage_size; // 0: Infinite, Any other number: Max Size    
    uint16_t num_streams;
    UTILS_DS_ID __DSID;
    void *__optional; // Optional and can be used as anything. (Cache/MRU/LRU/Filtering etc)
} MAPI_STREAM_INTERNAL_INFO;

typedef struct {
    mapiID mapi_id;
    MAPI_LIB_SOCK_TYPE sock_type;
    uint16_t src_port;
    int internal_fd;
    int external_fd;
    uint32_t internal_max_packet_size;
    uint32_t external_max_packet_size;
    boolean use_epoll;
    mapi_receive_cb rcv_cb;
    boolean reuseaddr;
    boolean nonblockingIO;
    fd_set  __working_read_fd;
    int max_fd;
    MAPI_STREAM_INTERNAL_INFO *stream_info;
    int libInactivityTimeOut; // In seconds
    char *buffer; // This is used for Rx/Tx
} MAPI_INTERNAL_INFO;

static inline void __mapi_get_internal_uds_file(uint16_t uid, uint8_t sub_mid, char *path) {
    sprintf(path, "%s%d.%d.socket", MAPI_LIB_GET_DEFAULT_LOC, uid, sub_mid);
}

// This defintion needs to match with MAPI_DEST_INFO
struct __mapi_dest_info {
    uint8_t dst_sub_mid;
    uint16_t dst_uid;
    uint16_t dst_port;
    uint32_t dst_ip;
};

/*******************************************************************************/
/*                      Private functions                                      */
/*******************************************************************************/
int mapi_open_internal_socket(MAPI_INTERNAL_INFO *mapi_internal_info);
int mapi_open_external_socket(MAPI_INTERNAL_INFO *mapi_internal_info);
MAPI_LIB_ERR mapi_set_non_blocking_io(int socket_fd);
MAPI_LIB_ERR mapi_communicator(MAPI_INTERNAL_INFO *mapi_internal_info);
MAPI_LIB_ERR __mapi_communicator_with_epoll(MAPI_INTERNAL_INFO *mapi_internal_info);
MAPI_LIB_ERR __mapi_communicator_with_select(MAPI_INTERNAL_INFO *mapi_internal_info);
MAPI_LIB_ERR __mapi_communicator_with_select_accept(fd_set *master_set, int listen_fd,
                                                    MAPI_INTERNAL_INFO *mapi_internal_info);
MAPI_LIB_ERR mapi_lib_recv(int fd, MAPI_INTERNAL_INFO *mapi_internal_info);
uint32_t mapi_create_msg(MAPI_INTERNAL_INFO *mapi_internal_info,
                         uint32_t dst_ip, uint32_t dst_port, uint16_t dst_uid, 
                         uint32_t messageCode, char *msg, uint32_t len);
int mapi_open_internal_stream(mapiID mid, struct __mapi_dest_info *dst_info);
int mapi_open_external_stream(mapiID mid, struct __mapi_dest_info *dst_info);
int mapi_close_internal_stream(mapiID mid, struct __mapi_dest_info *dst_info);
int mapi_close_external_stream(mapiID mid, struct __mapi_dest_info *dst_info);
int __mapi_get_stream_fd(mapiID mid, struct __mapi_dest_info *dst_info);
int __mapi_get_stream_fd_linkedlist(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry);
int __mapi_get_stream_fd_queue(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry);
int __mapi_add_stream_fd(mapiID mid, struct __mapi_dest_info *dst_info, int fd);
int __mapi_add_stream_fd_linkedlist(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry);
int __mapi_add_stream_fd_queue(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry);
int __mapi_del_stream_fd(mapiID mid, struct __mapi_dest_info *dst_info);
int __mapi_del_stream_fd_linkedlist(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry);
int __mapi_del_stream_fd_queue(MAPI_STREAM_INTERNAL_INFO *stream, MAPI_STREAM_INTERNAL_ENTRY *entry);
int __mapi_set_stream_storage_type(MAPI_INTERNAL_INFO *mapi_internal_info, uint8_t type, uint16_t size);
boolean __mapi_is_stream_entry_match(MAPI_STREAM_INTERNAL_ENTRY *e1, MAPI_STREAM_INTERNAL_ENTRY *e2);
#endif /* INCLUDE_MAPI_INTERNAL_LIB_H__  */
