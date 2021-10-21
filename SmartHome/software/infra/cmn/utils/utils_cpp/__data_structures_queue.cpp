/****************************************************************************
    Description: This uses the C++ dequeue library
*****************************************************************************/
#include <iostream>
#include <deque>

using namespace std;

/****************************************************************************/
/*                      Functions Definitions                               */
/****************************************************************************/
extern "C" { /* Define all functions as C compatible */

void* utils_ds_cpp_queue_create_container(int size) {
    deque<void*> *utils_ds_queue = new deque<void *>(size);
    return utils_ds_queue;
}

int utils_ds_cpp_queue_enqueue_container(void *container, void *data, bool isFront) {
    if(container == NULL) return -1;

    deque<void*> *utils_ds_queue = (deque<void*>*)container;
    if(isFront == true) {
        utils_ds_queue->push_front(data);
    } else {
        utils_ds_queue->push_back(data);
    }
    return 0;
}

void* utils_ds_cpp_queue_dequeue_container(void *container, bool isFront) {
    if(container == NULL) return NULL;

    deque<void*> *utils_ds_queue = (deque<void*>*)container;
    void *data = NULL;
    if(isFront == true) {
        data = utils_ds_queue->front();
        utils_ds_queue->pop_front();
    } else {
        data = utils_ds_queue->back();
        utils_ds_queue->pop_back();
    }
    return data;
}

// Caller needs to make sure that pos is valid
int utils_ds_cpp_queue_insert_at_pos_container(void *container, int pos, void *data) {
    if(container == NULL) return -1;

    deque<void*> *utils_ds_queue = (deque<void*>*)container;
    utils_ds_queue->at(pos) = data;
    return pos;
}

// Caller needs to make sure that pos is valid
void* utils_ds_cpp_queue_lookup_at_pos_container(void *container, int pos) {
    if(container == NULL) return NULL;

    deque<void*> *utils_ds_queue = (deque<void*>*)container;
    void *data = utils_ds_queue->at(pos);
    return data;
}

void utils_ds_cpp_queue_destroy_container(void *container) {
    if(container == NULL) return;
    deque<void*> *utils_ds_queue = (deque<void*>*)container;
    delete utils_ds_queue;
    return;
}

} /* end of extern "C" */
