#include <stdio.h>
#include "taskhandler.h"

typedef enum {
    TEST_LOCAL_EVENT_0,
    TEST_LOCAL_EVENT_1,
    TEST_LOCAL_EVENT_2,
    TEST_LOCAL_EVENT_3,
    TEST_LOCAL_EVENT_MAX
} TEST_LOCAL_EVENT;

typedef enum {
    TEST_GLOBAL_EVENT_0,
    TEST_GLOBAL_EVENT_1,
    TEST_GLOBAL_EVENT_MAX
} TEST_GLOBAL_EVENT;

void *func1(void *arg) {
    UTILS_TASK_HANDLER_STATUS* taskInfo = utils_task_handler_get_taskInfo();
    printf("Im in %s, task ID %d\n", __func__, taskInfo->__taskID);
#if 0
    sleep(2);
    printf("Sending event %d\n", TEST_LOCAL_EVENT_0);
    utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_0);
    sleep(2);
    printf("Sending event %d\n", TEST_LOCAL_EVENT_2);
    utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_2);
    sleep(2);
    printf("Sending event %d\n", TEST_LOCAL_EVENT_3);
    utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_3); 
#endif

    return (void*)1;
}

void *func2(void *arg) {
    UTILS_TASK_HANDLER_STATUS* taskInfo = utils_task_handler_get_taskInfo();
    printf("Im in %s, task ID %d\n", __func__, taskInfo->__taskID);
   
    return (void*)2;
}

void *func3(void *arg) {
    UTILS_TASK_HANDLER_STATUS* taskInfo = utils_task_handler_get_taskInfo();
    printf("Im in %s, task ID %d\n", __func__, taskInfo->__taskID);
   
    return (void*)3;
}

void *func4(void *arg) {
    UTILS_TASK_HANDLER_STATUS* taskInfo = utils_task_handler_get_taskInfo();
    printf("Im in %s, task ID %d\n", __func__, taskInfo->__taskID);
   
    return (void*)4;
}


void func2_reg_events(uint8_t taskID) {
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_1, taskID); 
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_3, taskID); 
}

void func3_reg_events(uint8_t taskID) {
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_0, taskID); 
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_3, taskID); 
}

void func4_reg_events(uint8_t taskID) {
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_2, taskID); 
}



UTILS_TASK_HANDLER test_handlers[] = 
{
    {
        .taskID = 1,
        .handler = func1,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
    },
    {
        .taskID = 2,
        .handler = func2,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
        .reg_event_cb = func2_reg_events,
    },
    {
        .taskID = 3,
        .handler = func3,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
        .reg_event_cb = func3_reg_events,
    },
    {
        .taskID = 4,
        .handler = func4,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = FALSE,
        .reg_event_cb = func4_reg_events,
    }
};



int main() {
    utils_task_handlers_create(4, test_handlers, 0, 0);
    utils_task_handlers_wait(4, test_handlers);
    return 0;
}



