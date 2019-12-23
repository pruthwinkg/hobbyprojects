#include "utils.h"
#include <unistd.h>

int main() {
    UTILS_SHM_OBJ *shm_obj;
    char data[10] = "Process A";
    printf("Im process A\n");


    shm_obj = utils_create_shared_obj(0xA, 100, 
  UTILS_SHM_FLAGS_CREATE | UTILS_SHM_FLAGS_RDWR | UTILS_SHM_FLAGS_SHARED);

    memcpy(shm_obj->addr, data, sizeof(data));

    while(1) {
        sleep(2);
        UTILS_SHM_OBJ_HDR *hdr = &shm_obj->hdr;
        utils_update_shared_obj_refcount(shm_obj);
        printf("Refcount in A = %d\n", hdr->refcount);
    }

    return 0;
}
