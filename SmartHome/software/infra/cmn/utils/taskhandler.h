/*******************************************************************************
    Description : Task handler heade file
    
    Note : This also implements some basic event nofitication mechanism, although
           it is not rich as event_managers features.

           It is recommended to use taskhandler libraries event mechanism for
           simple notification between threads

           It uses conditional variables, signals and signalfd()
*******************************************************************************/

#ifndef INCLUDE_UTILS_TASKHANDLER_H__
#define INCLUDE_UTILS_TASKHANDLER_H__

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "smarthome_essentials.h"
#include "logging.h"

#define UTILS_LOG_TRACE             printf

/* These two are used internally for managing multi-events */
// Should never use these for any other purpose
pthread_cond_t  __gEventCV;
pthread_mutex_t __gEventMutex;

#define UTILS_TASK_HANDLER_EVENT_ID     (0xAA000000)

// Function pointer for task handling
typedef void *(*utils_task_handler)(void *);
typedef void (*utils_task_handler_register_events_cb)(uint8_t taskID);

extern pthread_t *utils_task_ids;

// This structure is specific for each task (local)
// Single Reader - Multiple Writers
typedef struct {
    pthread_cond_t  __eventCV;
    pthread_mutex_t __eventMutex;
    uint32_t *__eventQueue; // Local event Queue
    uint8_t __eventQueueSize;
    boolean __eventQueueEmpty;
} UTILS_TASK_HANDLER_EVENTS;

typedef struct {
    uint8_t taskID; // <In> Unique within a module
    utils_task_handler handler; // <In>
    const pthread_attr_t *attr; // <In>
    void *arg;                  // <In>
    boolean eventEnable;        // <In> Even if disabled, a task can send events. But cannot receive (even global)
    utils_task_handler_register_events_cb  reg_event_cb; // <In>
    void *task_ret; // Return value of the task <Out>
    UTILS_TASK_HANDLER_EVENTS *events; // <Out> 
} UTILS_TASK_HANDLER;

typedef struct {
    uint16_t event;
    uint8_t *tasks;// List of taskIDs which are interested in this event
} UTILS_TASK_HANLDER_EVENT_INTEREST_TBL;

// This is a data structure which is specific for each task
typedef struct {
    uint8_t __taskID;
} UTILS_TASK_HANDLER_STATUS;

/*******************************************************************************/
/*              Internal Functions                                               */
/*******************************************************************************/
static void* __utils_task_handlers_startup_routine(void *arg);
static void __utils_task_handler_free_memory(void *arg);
static void __utils_task_handler_create_taskInfoKey(void);
static void __utils_task_handlers_create_event_interest_tbl(uint8_t numEvents, uint8_t numTasks);
static void __utils_task_handlers_destroy_event_interest_tbl(uint8_t numEvents);
static void __utils_task_handlers_update_event_interest_tbl(uint8_t numEvents, uint8_t numTasks);

/*******************************************************************************/
/*              Public Functions                                               */
/*******************************************************************************/
int utils_task_handlers_create(uint8_t num_workers, UTILS_TASK_HANDLER *workers, uint8_t maxLocalEvents, uint8_t maxGlobalEvents);
int utils_task_handlers_wait(int num_workers, UTILS_TASK_HANDLER *workers);
void utils_task_handlers_register_event(uint16_t event, uint8_t taskID);
void utils_task_handlers_unregister_event(uint16_t event, uint8_t taskID);
void utils_task_handlers_send_event(boolean isLocalMode, uint32_t event);
uint16_t utils_task_handlers_get_event(void);
UTILS_TASK_HANDLER_STATUS* utils_task_handler_get_taskInfo(void);


#endif /* INCLUDE_UTILS_TASKHANDLER_H__ */
