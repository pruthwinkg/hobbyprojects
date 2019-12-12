#include "../utils.h"

int main() {
    UTILS_SHM_OBJ *shm_obj;
    char data[100] = {0};
    printf("Im process B\n");

    shm_obj = utils_create_shared_obj(0xA, 100, 
            UTILS_SHM_FLAGS_RDWR | UTILS_SHM_FLAGS_SHARED);

    memcpy(data, shm_obj->addr, 10);

    printf("Data read from shm obj : %s\n", data);

    UTILS_SHM_OBJ_HDR* shm_obj_hdr = utils_get_shared_obj_hdr(shm_obj->addr);
    printf("shm obj header : magic = 0x%x, refcount = %d, obj_id = %d\n",
                shm_obj_hdr->magic, shm_obj_hdr->refcount, shm_obj_hdr->obj_id);

    sleep(8);

    utils_destroy_shared_obj(shm_obj, FALSE);

    return 0;
}
