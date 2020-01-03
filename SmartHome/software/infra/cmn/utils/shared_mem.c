/*******************************************************************************
    Description : Common functions to create shared memories
    Reference : https://gist.github.com/garcia556/8231e844a90457c99cc72e5add8388e4
*******************************************************************************/

#include "utils.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void __utils_get_shm_obj_id(uint8_t id, char *buf, uint8_t bufsize);

uint8_t __utils_shm_obj_count = 0;

// Format of the shm obj
/*---------------------------------*/
/*  shm obj header (20 bytes)      */
/*---------------------------------*/
/*                                 */
/*     shm obj data (addr)         */
/*                                 */
/*---------------------------------*/

// Note : Shared objects have a over head of around 20 bytes as header.
// So its recommended to use it when the actual data is much bigger.


/*!
*   @brief Creates a shared memory object  
*   @param shm_id : Pass a unique ID for each shm obj
*   @return NULL : Error
            Shm Obj : Success
*/
UTILS_SHM_OBJ* utils_create_shared_obj(uint16_t shm_id, uint16_t size, int flags) {
    int fd;
    int oflag = 0;
    UTILS_SHM_OBJ *shm_obj;
	int final_shm_obj_size = 0;
	int res;
	void *addr;
	int mmap_flags = 0;
	int prot = 0;
    char buf[20];
    memset(buf, 0, sizeof(buf));

    if (__utils_shm_obj_count >= UTILS_MAX_SHM_OBJS) {
        UTILS_LOG_TRACE("Reached the max supported shm objs by the system\n");
        return NULL;
    }

	// This check is very important for data consistency. Else everything
	// will go for a toss
	if (sizeof(UTILS_SHM_OBJ_HDR) != UTILS_SHM_OBJ_HDR_SIZE) {
		UTILS_LOG_TRACE("Shm obj header size is not equal to %d. Aborting\n", UTILS_SHM_OBJ_HDR_SIZE);
		return NULL;
	}


    if (flags & UTILS_SHM_FLAGS_CREATE) {
        oflag |= O_CREAT;
    }
    if (flags & UTILS_SHM_FLAGS_RDWR) {
        oflag |= O_RDWR;
		prot |= PROT_WRITE;
    } else if (flags & UTILS_SHM_FLAGS_RDONLY) {
        oflag |= O_RDONLY;
		prot |= PROT_READ;
    } else {
        oflag |= O_RDONLY; // Default
		prot |= PROT_READ;
    }

    __utils_get_shm_obj_id(shm_id, buf, sizeof(buf));
    fd = shm_open(buf, oflag, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        
        return NULL;
    }
	
	final_shm_obj_size = UTILS_SHM_OBJ_HDR_SIZE + size;

    if (flags & UTILS_SHM_FLAGS_CREATE) {
        // extend shared memory object as by default it's initialized with size 0
        res = ftruncate(fd, final_shm_obj_size);
        if (res == -1) {
            return NULL;
        }
    }

	if (flags | UTILS_SHM_FLAGS_SHARED) {
		mmap_flags	|= MAP_SHARED;
	}

	// map shared memory to process address space
	addr = mmap(NULL, final_shm_obj_size, prot, mmap_flags, fd, 0);
	if (addr == MAP_FAILED)
	{
		return NULL;
	}

    shm_obj = (UTILS_SHM_OBJ *)malloc(sizeof(UTILS_SHM_OBJ));
    memset(shm_obj, 0, sizeof(UTILS_SHM_OBJ));

    // Read the physical shm mem header
    UTILS_SHM_OBJ_HDR *phy_shm_hdr = (UTILS_SHM_OBJ_HDR *)addr;

    // There will be only one owner of the physical shm mem.
    // But every user of this shm mem, will have a private copy of shm_obj
    if (flags & UTILS_SHM_FLAGS_CREATE) {
        shm_obj->hdr.magic = UTILS_SHM_OBJ_MAGIC_NUM;
        shm_obj->hdr.obj_id = shm_id;
        shm_obj->hdr.flags = flags;
        shm_obj->hdr.refcount = 1;
        shm_obj->hdr.size = size;
        shm_obj->hdr.reserved1 = 0; // For future use
        shm_obj->hdr.reserved2 = 0; // For future use
        shm_obj->hdr.reserved3 = 0; // For future use
        memset(&(shm_obj->hdr.userdefined), 0, sizeof(UTILS_SHM_OBJ_USER_HDR)); // Upto apps to use
        shm_obj->addr = addr + UTILS_SHM_OBJ_HDR_SIZE; // Correct the offset
        // On success increase the count
        __utils_shm_obj_count++;
        
        // Copy the header to the physical shm memory header
        memcpy(phy_shm_hdr, &(shm_obj->hdr), sizeof(UTILS_SHM_OBJ_HDR));

    } else { // Read from physical shm mem and fill the shm_obj
        if (flags & UTILS_SHM_FLAGS_RDWR) { // In RDONLY cannot write to phy shm mem. Results segfault 
            phy_shm_hdr->refcount++; // Increase the ref count in physical, so that everyone is aware of it
        }
        memcpy(&(shm_obj->hdr), phy_shm_hdr, sizeof(UTILS_SHM_OBJ_HDR));
        if (shm_obj->hdr.magic != UTILS_SHM_OBJ_MAGIC_NUM) {
            UTILS_LOG_TRACE("Something is wrong with the shm obj. Unusuable\n");
            return NULL;
        }
        shm_obj->addr = addr + UTILS_SHM_OBJ_HDR_SIZE; // Correct the offset
        shm_obj->hdr.flags = flags; // Private copy of flags for the caller
    }
   
   return shm_obj;
}

/*!
* @Breif This function should only be called by process
*        who is the owner of this shm_obj
*       In normal cases, if the shm obj is still being in use by other processes, 
*       this function wont delete it, unless explicitly specified by
*       force_delete
*/
int utils_destroy_shared_obj(UTILS_SHM_OBJ *shm_obj, boolean force_delete) {
    int res;
    int fd;
    int final_shm_obj_size = 0;
    char buf[20];
    memset(buf, 0, sizeof(buf));

    if(shm_obj == NULL) {
        return -1;
    }

    // For a user of a shm_obj just delete the private shm_obj
    // and decrement the refcount in physical shm mem if allowed
    if (!(shm_obj->hdr.flags & UTILS_SHM_FLAGS_CREATE)) {
        if (shm_obj->hdr.flags & UTILS_SHM_FLAGS_RDWR) {
            UTILS_SHM_OBJ_HDR* phy_shm_obj_hdr;
            phy_shm_obj_hdr = utils_get_shared_obj_hdr(shm_obj->addr);
            if (phy_shm_obj_hdr) {
                phy_shm_obj_hdr->refcount--;
            }
        }
        memset(shm_obj, 0, sizeof(UTILS_SHM_OBJ));
        free(shm_obj);
        return 0;
    }
    
    // ONLY a owner/creater is allowed to destroy all the references of
    // the shm_obj

    final_shm_obj_size = UTILS_SHM_OBJ_HDR_SIZE + shm_obj->hdr.size; 

    // Update the refcount before delete
    if (force_delete == FALSE) {
        utils_update_shared_obj_refcount(shm_obj);
        if (shm_obj->hdr.refcount > 1) {
            return -2;
        }
    }

    res = munmap(shm_obj->addr, final_shm_obj_size);
    if (res == -1) {
        return -3;
    }

    __utils_get_shm_obj_id(shm_obj->hdr.obj_id, buf, sizeof(buf));
    fd = shm_unlink(buf);
    if (fd == -1) {
        return -4;
    }

    memset(shm_obj, 0, sizeof(UTILS_SHM_OBJ)); // Free usually doesnt set to 0
    free(shm_obj);

    return 0;
}

UTILS_SHM_OBJ_HDR* utils_get_shared_obj_hdr(void *addr) {
    UTILS_SHM_OBJ_HDR *phy_shm_obj_hdr = NULL;

    if(addr == NULL) {
        UTILS_LOG_TRACE("Invalid address passed to %s\n", __func__);
		return NULL;
	}

    phy_shm_obj_hdr = addr - sizeof(UTILS_SHM_OBJ_HDR);

    // Do some sanity checks on this pointer
    if (phy_shm_obj_hdr == NULL) {
        return NULL;
    }
    if (phy_shm_obj_hdr->magic != UTILS_SHM_OBJ_MAGIC_NUM) {
        return NULL;
    }

    return phy_shm_obj_hdr;
}

void utils_update_shared_obj_refcount(UTILS_SHM_OBJ *shm_obj) {
    UTILS_SHM_OBJ_HDR *phy_shm_obj_hdr = NULL;
    
    phy_shm_obj_hdr = utils_get_shared_obj_hdr(shm_obj->addr); 
    if (phy_shm_obj_hdr == NULL) {
        UTILS_LOG_TRACE("Unable to get the phy shm obj hdr\n");
        return;
    }

    shm_obj->hdr.refcount = phy_shm_obj_hdr->refcount;
}


static void __utils_get_shm_obj_id(uint8_t id, char *buf, uint8_t bufsize) {
    snprintf(buf, bufsize, "%s%d", UTILS_SHM_ID_PREFIX, id);
}
