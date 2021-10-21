/*******************************************************************************
    Description : Data structures heade file
                  Futute Request : TODO See if this file can be made as a 
                  wrapper for C++ STL. SO no need to change any other module,
                  if the interfaces are well defined

    TODO: USe BSD libraries and WRAP Utils library around it

    http://bxr.su/OpenBSD/sys/dev/pci/drm/include/linux/
                  
*******************************************************************************/

#ifndef INCLUDE_UTILS_DATASTRUCTURES_CMN_H__
#define INCLUDE_UTILS_DATASTRUCTURES_CMN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "smarthome_essentials.h"
#include "logging.h"
#include "utils_enums.h"

#define UTILS_LOG_ERROR  LOG_ERROR
#define UTILS_LOG_TRACE  LOG_TRACE
#define UTILS_LOG_DEBUG  LOG_DEBUG
#define UTILS_NOT_YET_IMPLEMENTED   printf("Not yet implemented\n")
#define UTILS_NOT_SUPPORTED printf("Not supported\n")

#define UTILS_DS_MAX_ID             (100) // Max IDs support (soft limit)

// Type (8 bit), sub-type (4 bit), ID (20 bit)
typedef uint32_t UTILS_DS_ID;

#define UTILS_DS_TYPE_SHIFT          (24)
#define UTILS_DS_SUB_TYPE_SHIFT      (20)
#define UTILS_DS_ID_SHIFT            (0)

#define UTILS_DS_TYPE_MASK          (0x00FF << UTILS_DS_TYPE_SHIFT)
#define UTILS_DS_SUB_TYPE_MASK      (0x0F << UTILS_DS_SUB_TYPE_SHIFT)
#define UTILS_DS_ID_MASK            (0x0FFFFF << UTILS_DS_ID_SHIFT)

#define UTILS_DS_GET_TYPE(id)       ((id & UTILS_DS_TYPE_MASK) >> UTILS_DS_TYPE_SHIFT)
#define UTILS_DS_GET_SUBTYPE(id)    ((id & UTILS_DS_SUB_TYPE_MASK) >> UTILS_DS_SUB_TYPE_SHIFT)
#define UTILS_DS_GET_ID(id)         ((id & UTILS_DS_ID_MASK) >> UTILS_DS_ID_SHIFT)

#define UTILS_DS_LOCK_CREATE(qmeta)  do {\
                                        qmeta->lock.isProtected = TRUE;\
                                        pthread_mutex_init(&(qmeta->lock.__lock), NULL);\
                                     } while(0)

#define UTILS_DS_CHECK_LOCK(qmeta)  do {\
                                        if(qmeta->lock.isProtected) {\
                                            pthread_mutex_lock(&(qmeta->lock.__lock));\
                                        }\
                                    } while(0)                                        

#define UTILS_DS_CHECK_UNLOCK(qmeta)  do {\
                                            if(qmeta->lock.isProtected) {\
                                                pthread_mutex_unlock(&(qmeta->lock.__lock));\
                                            }\
                                        } while(0)                                        
#define UTILS_DS_LOCK_DESTROY(qmeta)  do {\
                                            if(qmeta->lock.isProtected) {\
                                                pthread_mutex_destroy(&qmeta->lock.__lock);\
                                            }\
                                        } while(0)
typedef enum {
    UTILS_DS_QUEUE = 0x1,
    UTILS_DS_LIST = 0x2,
    UTILS_DS_STACK = 0x3,
    UTILS_DS_TREE = 0x4,
    UTILS_DS_HASH = 0x5,
} UTILS_DS_TYPE;

/*******************************************************************************/
/*                  Internal Data structures                                   */
/*******************************************************************************/
extern boolean utils_ds_initialized;
extern UTILS_DS_LIB_MODE utils_ds_lib_mode;

typedef struct {
    boolean isProtected;
    pthread_mutex_t __lock;
} __UTILS_DS_LOCK;

// Common Functions
UTILS_DS_ID utils_ds_get_id(UTILS_DS_TYPE type, int subtype);
void utils_ds_delete_id(UTILS_DS_ID id);
void* utils_ds_get_meta(UTILS_DS_ID id);
void utils_ds_set_meta(UTILS_DS_ID id, void *qmeta);

#endif /* INCLUDE_UTILS_DATASTRUCTURES_CMN_H__ */
