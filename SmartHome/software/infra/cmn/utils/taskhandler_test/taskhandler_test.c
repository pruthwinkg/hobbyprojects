#include <stdio.h>
#include <unistd.h>
#include "taskhandler.h"

typedef enum {
    TEST_LOCAL_EVENT_0 = 0,
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
    printf("Im in %s, task ID %d\n", __func__, taskInfo->__task->taskID);

    sleep(2);
    printf("Sending event %d\n", TEST_LOCAL_EVENT_0);
    utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_0, FALSE);    
    sleep(2);
    printf("Sending event %d\n", TEST_LOCAL_EVENT_2);
    utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_2, TRUE); // High priority event
    sleep(2);
   printf("Sending event %d\n", TEST_LOCAL_EVENT_3);
    utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_3, FALSE); 
  
    // Every task should receive this, even if not registered for this event
    sleep(2);
    printf("Sending Global event %d\n", TEST_GLOBAL_EVENT_0);
    utils_task_handlers_send_event(FALSE, TEST_GLOBAL_EVENT_0, FALSE); 
   

    return (void*)1;
}

void *func2(void *arg) {
    UTILS_TASK_HANDLER_STATUS* taskInfo = utils_task_handler_get_taskInfo();
    printf("Im in %s, task ID %d\n", __func__, taskInfo->__task->taskID);

    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;
    while(1) {
        printf("%s : Waiting for events\n", __func__);
        eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
        printf("%s : Num of events read = %d\n", __func__, eventsRead);
        for (uint16_t i = 0; i < eventsRead; i++) {
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                printf("%s : Received a Global event = 0x%0x\n", __func__, eventList[i]);
            } else {                
                printf("%s : Received a local event = 0x%x with priority = %s\n", 
               __func__, eventList[i], UTILS_TASK_HANDLER_EVENT_IS_HIGH_PRIO(eventList[i]) ? "HIGH":"LOW");
            }
        }
        sleep(2);
        printf("Sending event %d\n", TEST_LOCAL_EVENT_0);
        utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_0, FALSE);       
    }

    return (void*)2;
}

void *func3(void *arg) {
    UTILS_TASK_HANDLER_STATUS* taskInfo = utils_task_handler_get_taskInfo();
    printf("Im in %s, task ID %d\n", __func__, taskInfo->__task->taskID);

    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;
    while(1) {
        printf("%s : Waiting for events\n", __func__);
        eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
        printf("%s : Num of events read = %d\n", __func__, eventsRead);
        for (uint16_t i = 0; i < eventsRead; i++) {           
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                printf("%s : Received a Global event = 0x%0x\n", __func__, eventList[i]);
            } else { 
                printf("%s : Received a local event = 0x%x\n", __func__, eventList[i]);
            }           
        }
        sleep(2);
        printf("Sending event %d\n", TEST_LOCAL_EVENT_2);
        utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_2, FALSE);  
    }

    return (void*)3;
}

void *func4(void *arg) {
    UTILS_TASK_HANDLER_STATUS* taskInfo = utils_task_handler_get_taskInfo();
    printf("Im in %s, task ID %d\n", __func__, taskInfo->__task->taskID);
  
    uint16_t eventListSize = 5;
    uint32_t eventList[eventListSize];
    uint16_t eventsRead = 0;
    while(1) {
        printf("%s : Waiting for events\n", __func__);
        eventsRead = utils_task_handlers_get_events(eventList, eventListSize);
        printf("%s : Num of events read = %d\n", __func__, eventsRead);
        for (uint16_t i = 0; i < eventsRead; i++) {
            if(UTILS_TASK_HANDLER_EVENT_IS_GLOBAL(eventList[i])) {
                printf("%s : Received a Global event = 0x%0x\n", __func__, eventList[i]);
            } else { 
                printf("%s : Received a local event = 0x%x\n", __func__, eventList[i]);
            }          
        }
        sleep(2);
        printf("Sending event %d\n", TEST_LOCAL_EVENT_0);
        utils_task_handlers_send_event(TRUE, TEST_LOCAL_EVENT_3, FALSE); 
       
    }

    return (void*)4;
}


void func2_reg_events(uint32_t taskID) {
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_2, taskID); 
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_3, taskID); 
}

void func3_reg_events(uint32_t taskID) {
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_0, taskID); 
   utils_task_handlers_register_event(TEST_LOCAL_EVENT_3, taskID); 
}

void func4_reg_events(uint32_t taskID) {
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
        .eventEnable = TRUE,
        .reg_event_cb = func2_reg_events,
    },
    {
        .taskID = 3,
        .handler = func3,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = TRUE,
        .reg_event_cb = func3_reg_events,
    },
    {
        .taskID = 4,
        .handler = func4,
        .attr = NULL,
        .arg = NULL,
        .eventEnable = TRUE,
        .reg_event_cb = func4_reg_events,
    }
};



int main() {
    utils_task_handlers_create(4, test_handlers, TEST_LOCAL_EVENT_MAX, TEST_GLOBAL_EVENT_MAX);
    utils_task_handlers_wait(4, test_handlers);
    return 0;
}



