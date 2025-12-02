/*****************************************************************************
    Description : The purpose of this file is to define various common
                datastructures qhich might be required by various modules.

                All these data strcutures will be very genereic. i.e they will
                agnostic of what kind of data they hold
*****************************************************************************/

#include "data_structures.h"
#include "data_structures_cmn.h"

// Maintained per type. Helps to allocate huge number of DSIDs
UTILS_DS_ID *utils_ds_bitmap[UTILS_DS_TYPE_MAX];
void **utils_ds_metadata[UTILS_DS_TYPE_MAX];

uint16_t utils_ds_max_dsid = UTILS_DS_MAX_ID; // Default soft limit

boolean utils_ds_initialized = FALSE;
UTILS_DS_LIB_MODE utils_ds_lib_mode = UTILS_DS_LIB_MODE_CPP; // Default mode


/****************************************************************************/
/*                      Internal functions declaration                      */
/****************************************************************************/
static UTILS_DS_ID __utils_get_free_id(UTILS_DS_TYPE type, int subtype);
static void __utils_delete_id(UTILS_DS_ID id);

void utils_ds_init(UTILS_DS_LIB_MODE mode, uint16_t max_dsid) {
    if(utils_ds_initialized == TRUE) {
        UTILS_LOG_TRACE("utils_ds library is already initialized\n");
        return;
    }

    if(max_dsid != 0) {
        utils_ds_max_dsid = max_dsid;
        UTILS_LOG_TRACE("Changing the max supported dsid to %d", max_dsid);
    }

    // Dynamic allocation to control per-app specific DSID allocation
    for(int i = 0; i < UTILS_DS_TYPE_MAX; i++) {
        utils_ds_bitmap[i] = (UTILS_DS_ID *)malloc(sizeof(UTILS_DS_ID) * utils_ds_max_dsid);
        // 0 will be treated as a unused ID
        memset(utils_ds_bitmap[i], 0, sizeof(UTILS_DS_ID) * utils_ds_max_dsid);

        // Create an array of pointers to hold the metadata of the ds.
        // Even this array will be generic (void *). Its upto the DS
        // to typecast and malloc properly
        utils_ds_metadata[i] = (void **)malloc(sizeof(void *) * utils_ds_max_dsid);
        memset(utils_ds_metadata[i], NULL, sizeof(void *) * utils_ds_max_dsid); 
    }        

    utils_ds_lib_mode = mode;
    UTILS_LOG_TRACE("Setting the utils ds library mode to %d", mode);

    utils_ds_initialized = TRUE;    
}

UTILS_DS_ID utils_ds_get_id(UTILS_DS_TYPE type, int subtype) {
    return __utils_get_free_id(type, subtype);
}

void utils_ds_delete_id(UTILS_DS_ID id) {
    __utils_delete_id(id);
}

void* utils_ds_get_meta(UTILS_DS_ID id) {
    UTILS_DS_TYPE type = UTILS_DS_GET_TYPE(id);
    return utils_ds_metadata[type][UTILS_DS_GET_ID(id)];
}

void utils_ds_set_meta(UTILS_DS_ID id, void *qmeta) {
    UTILS_DS_TYPE type = UTILS_DS_GET_TYPE(id);
    utils_ds_metadata[type][UTILS_DS_GET_ID(id)] = qmeta; 
}

/*****************************************************************************
                    Generic external utility Functions
*****************************************************************************/
boolean utils_is_int_in_array(int value, const int *array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return TRUE; // Found the integer
        }
    }
    return FALSE; // Integer not found
}

int utils_get_max_int_in_array(const int *array, int size) {
    if (size <= 0) {
        return -1; // Handle empty array case
    }

    int max_value = array[0]; // Assume the first element is the maximum initially
    for (int i = 1; i < size; i++) {
        if (array[i] > max_value) {
            max_value = array[i];
        }
    }
    return max_value;
}

// In utils.c
int utils_compare_structs(void *struct1, void *struct2, size_t size) {
    return memcmp(struct1, struct2, size);
}

/*****************************************************************************
                    Internal Functions
*****************************************************************************/
static UTILS_DS_ID __utils_get_free_id(UTILS_DS_TYPE type, int subtype) {
    for (UTILS_DS_ID i = 0; i < utils_ds_max_dsid; i++) {
        if (utils_ds_bitmap[type][i] == 0) {
            utils_ds_bitmap[type][i] = (((type << UTILS_DS_TYPE_SHIFT) & UTILS_DS_TYPE_MASK) |
                   ((subtype << UTILS_DS_SUB_TYPE_SHIFT) & UTILS_DS_SUB_TYPE_MASK) |
                   (i & UTILS_DS_ID_MASK));
            return utils_ds_bitmap[type][i];                   
        }
    }
    return 0;
}

static void __utils_delete_id(UTILS_DS_ID id) {
    if (id == 0) {
        return;        
    }
    UTILS_DS_TYPE type = UTILS_DS_GET_TYPE(id);
    utils_ds_bitmap[type][UTILS_DS_GET_ID(id)] = 0;
}

