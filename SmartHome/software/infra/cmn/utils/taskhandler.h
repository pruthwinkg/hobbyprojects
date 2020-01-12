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

#define UTILS_LOG_DEBUG             printf
#define UTILS_LOG_TRACE             printf
#define UTILS_LOG_ERROR             printf

/*
    Event format : 32 bits
      16 bits    (Special flags)  |  16 bit (event)

    Special flags :
        Bit 16 : Priority (1 : High, 0 : Normal) [Best effort and dynamic]
        Bit 17 : Mode (0 : Local, 1 : Global)
        Bit 18 - 23 : Reserved (Future use)
        Bit 31-24 : Valid event marker (0xAA)

    Note :
        The priority bit is only best effort. According to the percent
        set, the tasks event queue will be divided logically as high and
        low priority. The high priority events are always to the left side 
        of the event queue and low priority events to the right side. The
        tasks can change the priority of any event dynamically when sending 
        an event. A best effort will be made to put the events according to their
        priority when adding to the event queue. Global events have the highest
        priority. It cannot be changed

        The event reading api, always reads from the left most part of the queue to
        the right most part.

        The queue division to high and low are set to 25% and 75% by default. But can
        override this setting using UTILS_TASK_HANDLER_ATTR when creating the task
*/
#define UTILS_TASK_HANDLER_EVENT_PRIO   (1 << 16)
#define UTILS_TASK_HANDLER_EVENT_MODE   (1 << 17)

#define UTILS_TASK_HANDLER_EVENT_PRIO_HIGH_PERCENT      (25)
#define UTILS_TASK_HANDLER_EVENT_PRIO_LOW_PERCENT       (75)

#define UTILS_TASK_HANDLER_EVENT_ID     (0xAA000000) // Valid event prefix
#define UTILS_TASK_HANDLER_NO_EVENT     (0xFFFFFFFF) // Marker for no event
#define UTILS_TASK_HANDLER_EVENT_MASK   (0x0000FFFF) // To get actual event

#define UTILS_TASK_HANDLER_EVENT_QUEUE_LOCAL_BEGIN      (1)
#define UTILS_TASK_HANDLER_EVENT_QUEUE_GLOBAL_BEGIN     (0)

#define UTILS_TASK_HANDLER_EVENT_UNINTERESTED_TASK      (0xFFFFFFFF)

// Function pointer for task handling
typedef void *(*utils_task_handler)(void *);
typedef void (*utils_task_handler_register_events_cb)(uint8_t taskID);

// This structure is specific for each task (local)
// Single Reader - Multiple Writers
typedef struct {
    pthread_cond_t  __eventCV;
    pthread_mutex_t __eventMutex;
    uint32_t *__eventQueue; // Local event Queue
    uint16_t __eventQueueSize;
    boolean __eventQueueEmpty;
    uint16_t __eventQueueHighPrioSize; // Num of entries (Not in %)
} UTILS_TASK_HANDLER_EVENTS;

// Can use this to override some default settings of the task
typedef struct {
    uint8_t eventHighPrioPercent; // Low will be calculated from 100-high 
} UTILS_TASK_HANDLER_ATTR;

typedef struct {
    uint32_t taskID; // <In> Unique within a module
    utils_task_handler handler; // <In>
    const pthread_attr_t *attr; // <In>
    void *arg;                  // <In>
    boolean eventEnable;        // <In> Even if disabled, a task can send events. But cannot receive (even global)
    utils_task_handler_register_events_cb  reg_event_cb; // <In>
    void *task_ret; // Return value of the task <Out>
    UTILS_TASK_HANDLER_ATTR *taskattr; // <In> Usually NULL. But can use to override some defaults
    UTILS_TASK_HANDLER_EVENTS *events; // <Out> 
} UTILS_TASK_HANDLER;

typedef struct {
    uint16_t event;
    uint32_t *tasks;// List of taskIDs which are interested in this event
} UTILS_TASK_HANLDER_EVENT_INTEREST_TBL;

// This is a data structure which is specific for each task
typedef struct {
    UTILS_TASK_HANDLER *__task;
} UTILS_TASK_HANDLER_STATUS;

/*******************************************************************************/
/*              Internal Functions                                               */
/*******************************************************************************/
static void* __utils_task_handlers_startup_routine(void *arg);
static UTILS_TASK_HANDLER* __utils_task_handlers_get_task(uint32_t taskID);
static void __utils_task_handler_free_memory(void *arg);
static void __utils_task_handler_create_taskInfoKey(void);
static void __utils_task_handlers_create_event_interest_tbl(uint16_t numEvents, uint8_t numTasks);
static void __utils_task_handlers_destroy_event_interest_tbl(uint16_t numEvents);
static uint32_t* __utils_task_handlers_get_tasks_from_event_interest_tbl(uint16_t event);
static int __utils_task_handlers_update_local_event_queue(boolean isLocalMode, uint16_t event, boolean isHighPrio);
static uint32_t __utils_task_handlers_get_event_index(boolean isLocalMode, uint16_t event, 
                                                      boolean isHighPrio, 
                                                      UTILS_TASK_HANDLER_EVENTS *eventHandle, 
                                                      uint16_t *free_slot);
/*******************************************************************************/
/*              Public Functions                                               */
/*******************************************************************************/
int utils_task_handlers_create(uint8_t num_workers, UTILS_TASK_HANDLER *workers, uint16_t maxLocalEvents, uint16_t maxGlobalEvents);
int utils_task_handlers_wait(int num_workers, UTILS_TASK_HANDLER *workers);
void utils_task_handlers_register_event(uint16_t event, uint32_t taskID);
void utils_task_handlers_unregister_event(uint16_t event, uint32_t taskID);
int utils_task_handlers_send_event(boolean isLocalMode, uint16_t event, boolean isHighPrio);
uint16_t utils_task_handlers_get_events(uint32_t *eventList, uint16_t eventListSize);
UTILS_TASK_HANDLER_STATUS* utils_task_handler_get_taskInfo(void);


#endif /* INCLUDE_UTILS_TASKHANDLER_H__ */
