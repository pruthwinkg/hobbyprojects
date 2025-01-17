/*******************************************************************************
    Description : Utilities library

*******************************************************************************/

#ifndef INCLUDE_UTILS_SHAREDMEM_H__
#define INCLUDE_UTILS_SHAREDMEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "smarthome_essentials.h"
#include "logging.h"

#define UTILS_MAX_SHM_OBJS          (50)
#define UTILS_SHM_ID_PREFIX         "/UTILS_SHM_ID_"

#define UTILS_LOG_ERROR  LOG_ERROR
#define UTILS_LOG_TRACE  LOG_TRACE
#define UTILS_LOG_DEBUG  LOG_DEBUG

#define UTILS_SHM_OBJ_HDR_SIZE      (sizeof(UTILS_SHM_OBJ_HDR)) // According to spec 40 bytes
#define UTILS_SHM_OBJ_MAGIC_NUM     (0xABCD)

// Shared memory flags
#define UTILS_SHM_FLAGS_CREATE		 (1 << 0) // "Create new shm obj"
#define UTILS_SHM_FLAGS_RDWR		 (1 << 1) // "Set the shm obj for read and write"
#define UTILS_SHM_FLAGS_RDONLY		 (1 << 2) // "Set the shm obj for read only"
#define UTILS_SHM_FLAGS_PRIVATE		 (1 << 3) // "Private shm obj (No other process can access it"
#define UTILS_SHM_FLAGS_SHARED		 (1 << 4) // "Shared shm obj"

uint8_t __utils_shm_obj_count;

// Reserving 4 * 4 = 16 bytes as userdefined (These fields should be used carefully. Dont expand
// the total size of this structure)
typedef struct {
    uint32_t    field1; //This can be used by anyone how they want
    uint32_t    field2; //This can be used by anyone how they want
    uint32_t    field3; //This can be used by anyone how they want
    uint32_t    field4; //This can be used by anyone how they want
} UTILS_SHM_OBJ_USER_HDR;

// Shared memory object header (This should be 40 bytes according to spec)
// Special field : userdefined -> Can be used by any applications
// according to its needs. One example is, to detect "in use" of shm obj 
// to avoid race cases, in multiple write scernios
typedef struct __attribute__((__packed__)) {
    uint32_t    magic;
    uint32_t    size; // Size of the shm obj addr
    uint16_t    flags; // Properties of the shm obj
    uint8_t     obj_id; // Unique ID to identify the shm obj
    uint8_t     refcount; // Refcount of processes using this shm obj (Not applicable in RDONLY)
    uint32_t    reserved1; // Reserved for internal future use
    uint32_t    reserved2; // Reserved for internal future use
    uint32_t    reserved3; // Reserved for internal future use
    UTILS_SHM_OBJ_USER_HDR userdefined; // This field is reserved for user apps (16 bytes)
} UTILS_SHM_OBJ_HDR;


typedef struct {
    UTILS_SHM_OBJ_HDR hdr;
    void        *addr;  // Pointer to the actual data mem
} UTILS_SHM_OBJ;


/******************************************************/
/*          Public functions                          */
/******************************************************/
UTILS_SHM_OBJ* utils_create_shared_obj(uint16_t shm_id, uint16_t size, int flags);
int utils_destroy_shared_obj(UTILS_SHM_OBJ *shm_obj, boolean force_delete);
void utils_update_shared_obj_refcount(UTILS_SHM_OBJ *shm_obj);
UTILS_SHM_OBJ_HDR* utils_get_shared_obj_hdr(void *addr);


#endif /* INCLUDE_UTILS_SHAREDMEM_H__ */
