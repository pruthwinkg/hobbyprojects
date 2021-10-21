#include "data_structures.h"
#include "utils_cpp.h"

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

void test_hash_string() {
    UTILS_HASH hash;
    hash.type = UTILS_DS_HASH_KEY_STRING;

    printf("\n\nTesting Hash for string key type\n");

    UTILS_DS_ID id = utils_ds_hash_create(&hash);
    printf("Hash id : 0x%0x\n", id);

    char hash_key[10];
    int data[10] = {11,12,13,14,15,16,17,18,19,20};
    int out_data;
    int curr_size;

    strcpy(hash_key, "key0");    
    utils_ds_hash_insert(id, (void *)hash_key, strlen(hash_key), (void *)&data[0]);
    strcpy(hash_key, "key1");
    utils_ds_hash_insert(id, (void *)hash_key, strlen(hash_key), (void *)&data[1]);
    strcpy(hash_key, "key2");
    utils_ds_hash_insert(id, (void *)hash_key, strlen(hash_key), (void *)&data[2]);
    strcpy(hash_key, "key3");
    utils_ds_hash_insert(id, (void *)hash_key, strlen(hash_key), (void *)&data[3]);

    strcpy(hash_key, "key1");
    out_data = *(int *)utils_ds_hash_lookup(id, (void *)hash_key, strlen(hash_key));
    printf("out_data = %d, Expecting = %d\n", out_data, data[1]);
    strcpy(hash_key, "key3");
    out_data = *(int *)utils_ds_hash_lookup(id, (void *)hash_key, strlen(hash_key));
    printf("out_data = %d, Expecting = %d\n", out_data, data[3]);

    curr_size = utils_ds_hash_get_size(id);
    printf("Current size = %d\n", curr_size);

    strcpy(hash_key, "key2");
    utils_ds_hash_erase(id, (void *)hash_key, strlen(hash_key));
   
    curr_size = utils_ds_hash_get_size(id);
    printf("Current size = %d\n", curr_size);

}

void test_hash_integer() {
    UTILS_HASH hash;
    hash.type = UTILS_DS_HASH_KEY_INTEGER;

    printf("\n\nTesting Hash for integer key type\n");

    UTILS_DS_ID id = utils_ds_hash_create(&hash);
    printf("Hash id : 0x%0x\n", id);

    int hash_key;
    int data[10] = {11,12,13,14,15,16,17,18,19,20};
    int out_data;
    int curr_size;

    hash_key = 0xA1;
    utils_ds_hash_insert(id, (void *)&hash_key, 0, (void *)&data[0]);
    hash_key = 0xA2;
    utils_ds_hash_insert(id, (void *)&hash_key, 0, (void *)&data[1]);
    hash_key = 0xA3;
    utils_ds_hash_insert(id, (void *)&hash_key, 0, (void *)&data[2]);
    hash_key = 0xA4;
    utils_ds_hash_insert(id, (void *)&hash_key, 0, (void *)&data[3]);

    hash_key = 0xA2;
    out_data = *(int *)utils_ds_hash_lookup(id, (void *)&hash_key, 0);
    printf("out_data = %d, Expecting = %d\n", out_data, data[1]);
    hash_key = 0xA4;
    out_data = *(int *)utils_ds_hash_lookup(id, (void *)&hash_key, 0);
    printf("out_data = %d, Expecting = %d\n", out_data, data[3]);

    curr_size = utils_ds_hash_get_size(id);
    printf("Current size = %d\n", curr_size);

    hash_key = 0xA3;
    utils_ds_hash_erase(id, (void *)&hash_key, 0);
   
    curr_size = utils_ds_hash_get_size(id);
    printf("Current size = %d\n", curr_size);

}

int main() {
    log_lib_init(NULL, LOG_LVL_DEBUG);
    utils_ds_init(UTILS_DS_LIB_MODE_CPP);

    test_queue_static();        
    test_queue_circular();        

    test_hash_string();
    test_hash_integer();

    return 0;
}
