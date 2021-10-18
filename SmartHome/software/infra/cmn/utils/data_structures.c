/*****************************************************************************
    Description : The purpose of this file is to define various common
                datastructures qhich might be required by various modules.

                All these data strcutures will be very genereic. i.e they will
                agnostic of what kind of data they hold
*****************************************************************************/

#include "data_structures.h"
#include "data_structures_cmn.h"

UTILS_DS_ID utils_ds_bitmap[UTILS_DS_MAX_ID];
void *utils_ds_metadata[UTILS_DS_MAX_ID];

boolean utils_ds_initialized = FALSE;

/****************************************************************************/
/*                      Internal functions declaration                      */
/****************************************************************************/
static UTILS_DS_ID __utils_get_free_id(UTILS_DS_TYPE type, int subtype);
static void __utils_delete_id(UTILS_DS_ID id);

void utils_ds_init() {
    if(utils_ds_initialized == TRUE) {
        UTILS_LOG_TRACE("utils_ds library is already initialized\n");
        return;
    }

    // 0 will be treated as a unused ID
    memset(utils_ds_bitmap, 0, sizeof(utils_ds_bitmap));

    // Create an array of pointers to hold the metadata of the ds.
    // Even this array will be generic (void *). Its upto the DS
    // to typecast and malloc properly
    memset(utils_ds_metadata, 0, sizeof(utils_ds_metadata));

    utils_ds_initialized = TRUE;    
}

UTILS_DS_ID utils_ds_get_id(UTILS_DS_TYPE type, int subtype) {
    return __utils_get_free_id(type, subtype);
}

void utils_ds_delete_id(UTILS_DS_ID id) {
    __utils_delete_id(id);
}

void* utils_ds_get_meta(UTILS_DS_ID id) {
    return utils_ds_metadata[UTILS_DS_GET_ID(id)];
}

void utils_ds_set_meta(UTILS_DS_ID id, void *qmeta) {
    utils_ds_metadata[UTILS_DS_GET_ID(id)] = qmeta; 
}

/*****************************************************************************
                    Internal Functions
*****************************************************************************/
static UTILS_DS_ID __utils_get_free_id(UTILS_DS_TYPE type, int subtype) {
    for (UTILS_DS_ID i = 0; i < UTILS_DS_MAX_ID; i++) {
        if (utils_ds_bitmap[i] == 0) {
            utils_ds_bitmap[i] = (((type << UTILS_DS_TYPE_SHIFT) & UTILS_DS_TYPE_MASK) |
                   ((subtype << UTILS_DS_SUB_TYPE_SHIFT) & UTILS_DS_SUB_TYPE_MASK) |
                   (i & UTILS_DS_ID_MASK));
            return utils_ds_bitmap[i];                   
        }
    }
    return 0;
}

static void __utils_delete_id(UTILS_DS_ID id) {
    if (id == 0) {
        return;        
    }
    utils_ds_bitmap[UTILS_DS_GET_ID(id)] = 0;
}

