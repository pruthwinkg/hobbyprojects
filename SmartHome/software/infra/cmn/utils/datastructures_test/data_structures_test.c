#include "data_structures.h"

void test_queue_static() {
    UTILS_QUEUE queue; 
    queue.type = UTILS_QUEUE_STATIC;
    queue.size = 10;
    queue.isPriority = 0;

    printf("\n\nTesting queue of STATIC type, %s\n", __func__);
    
    int data[10] = {1,2,3,4,5,6,7,8,9,10};
    int out_data;

    UTILS_DS_ID id = utils_ds_queue_create(&queue);
   
    printf("Queue id : 0x%0x\n", id);

    utils_ds_queue_enqueue(id, (void *)&data[0]);
    utils_ds_queue_enqueue(id, (void *)&data[2]);
    utils_ds_queue_enqueue(id, (void *)&data[4]);
    utils_ds_queue_enqueue(id, (void *)&data[6]);

    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);
    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);
    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);
    
    utils_ds_queue_enqueue(id, (void *)&data[6]);
    
    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);

    utils_ds_queue_destroy(id, 0);
}

void test_queue_circular() {
    UTILS_QUEUE queue; 
    queue.type = UTILS_QUEUE_CIRCULAR;
    queue.size = 5;
    queue.isPriority = 0;

    printf("\n\nTesting queue of CIRCULAR type, %s\n", __func__);
    
    int data[10] = {11,12,13,14,15,16,17,18,19,20};
    int out_data;

    UTILS_DS_ID id = utils_ds_queue_create(&queue);
    
    printf("Queue id : 0x%0x\n", id);

    utils_ds_queue_enqueue(id, (void *)&data[1]);
    utils_ds_queue_enqueue(id, (void *)&data[2]);
    utils_ds_queue_enqueue(id, (void *)&data[3]);
    utils_ds_queue_enqueue(id, (void *)&data[4]);
    utils_ds_queue_enqueue(id, (void *)&data[5]);

    if(utils_ds_queue_enqueue(id, (void *)&data[6]) < 0) {
        printf("Queue Full Test case passed\n");
    }

    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);
    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);
    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);
    
    utils_ds_queue_enqueue(id, (void *)&data[6]);
    
    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);
    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);
    out_data = *(int *)utils_ds_queue_dequeue(id);
    printf("out_data = %d\n", out_data);

    if(utils_ds_queue_dequeue(id) == NULL) {
        printf("Queue empty Test case passed\n");
    }
    
    utils_ds_queue_destroy(id, 0);
}


int main() {
    utils_ds_init();

    test_queue_static();        
    test_queue_circular();        

    return 0;
}
