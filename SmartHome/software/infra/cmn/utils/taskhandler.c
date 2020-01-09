/*****************************************************************************
    Descritpion : The functionality of this file is to support task handling
                  for any process
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taskhandler.h"

pthread_t *utils_task_ids;
pthread_cond_t  __gEventCV = PTHREAD_COND_INITIALIZER;
pthread_mutex_t __gEventMutex = PTHREAD_MUTEX_INITIALIZER;

// These are global event Queues
// Multiple Readers - Multiple Writers
uint32_t *gEventQueue;
uint8_t gEventQueueSize = 0;
boolean gEventQueueEmpty = TRUE;

UTILS_TASK_HANLDER_EVENT_INTEREST_TBL *eventInterestTbl;
static boolean eventInterestTableInitialized = FALSE;

static uint8_t __utilsMaxLocalEvents = 0;
static uint8_t __utilsMaxGlobalEvents = 0;

/* Internal to this lib */
static pthread_key_t __taskInfoKey;
static pthread_once_t __taskInfoKey_once = PTHREAD_ONCE_INIT;
/*
    @brief This function creates task handlers for handling jobs

    @param workers : Array of UTILS_TASK_HANDLER
    @param numEvents : Total number of events.

*/
int utils_task_handlers_create(uint8_t num_workers, 
                              UTILS_TASK_HANDLER *workers,
                              uint8_t maxLocalEvents,
                              uint8_t maxGlobalEvents) {
    UTILS_LOG_TRACE("Creating %d task handlers\n", num_workers);
    int pthread_ret = 0;

    utils_task_ids = (pthread_t *)malloc(num_workers * sizeof(pthread_t));

    // Create the local event interest table
    __utils_task_handlers_create_event_interest_tbl(maxLocalEvents, num_workers);

    /* Update the event interest table */
    for (uint8_t i = 0; i < num_workers; i++) {
        if (workers[i].handler == NULL) {
            UTILS_LOG_TRACE("Handler is NULL for Task ID %d\n", workers[i].taskID);
            continue;
        }
        
        // Only if event option is enabled for that task
        if (workers[i].eventEnable == TRUE) {
            workers[i].reg_event_cb(workers[i].taskID);
        }
    }

    // Create a Global event queue
    gEventQueue = (uint32_t *)malloc(sizeof(uint32_t) * maxGlobalEvents);
    memset(&gEventQueue, 0xFFFFFFFF, sizeof(uint32_t) * maxGlobalEvents);
    gEventQueueSize = maxGlobalEvents;
    gEventQueueEmpty = TRUE;

    // Update the local Read-Only global variables
    __utilsMaxLocalEvents = maxLocalEvents;
    __utilsMaxGlobalEvents = maxGlobalEvents;

    // Thread-specific key for storing the taskInfo
    (void) pthread_once(&__taskInfoKey_once, __utils_task_handler_create_taskInfoKey);

    /* Start all the tasks */
    for (uint8_t i = 0; i < num_workers; i++) {
        if (workers[i].handler == NULL) {
            UTILS_LOG_TRACE("Handler is NULL for Task ID %d\n", workers[i].taskID);
            continue;
        }

        pthread_ret = pthread_create(&utils_task_ids[i],
                                    workers[i].attr,
                                    __utils_task_handlers_startup_routine,                                    
                                   (void *)&workers[i]);

        if (pthread_ret != 0) {
            UTILS_LOG_TRACE("Failed to create worker for %d\n", i);
        }
    }

    return 0;
}

// Can add a new event even during runtime
void utils_task_handlers_register_event(uint16_t event, uint8_t taskID) {
    uint8_t *taskList = eventInterestTbl[event].tasks;
    taskList[taskID] = 0x01;
}

void utils_task_handlers_unregister_event(uint16_t event, uint8_t taskID) {
    uint8_t *taskList = eventInterestTbl[event].tasks;
    taskList[taskID] = 0xFF;   
}

/*
    @brief This function waits for all the workers in the UTILS_TASK_HANDLER list
*/
int utils_task_handlers_wait(int num_workers, UTILS_TASK_HANDLER *workers) {
    UTILS_LOG_TRACE("Waiting for %d task handlers\n", num_workers);
    int pthread_ret = 0;
    for(uint8_t i = 0; i < num_workers; i++) {
       pthread_ret = pthread_join(utils_task_ids[i], &workers[i].task_ret);
    }
    return 0;
}

/*
    Two modes - Local event Mode and Global Event Mode
    
    Local Event Mode : Applicable for Local Events
        Every task will have a local event queue and its own cv and mutex
        There will be multiple event writer and one event reader.

        Reader :
        The event reader will read its own event queue for any pending events.
        The event reader will process the pending event. It will process all
        the pending events in the local event queue. If there are no pending events,
        it will sleep and wait for event notification.

        Writer :
        The event writer writes an event to the event queues in case of any registered event.
        The event will be written to local event queues of tasks which are interested in this event.
        The event writer will notify the event reader only if 'eventQueueEmpty' is set to TRUE.
        Else it will just write the event and continue with its own task. If an pending event
        already exists, the current event will be ignored.


    Global Event Mode : Applicable for Gloabl events
        There is only one global event queue and global and mutex.
        There will be mutiple event writers and mutiple event readers

        If an event needs to be sent to ALL tasks, then this mode have to be used.

        NOTE : A thread CANNOT WAIT ON MULTIPLE COND VAR . So think about Global mode notification
            mechanism

        Option : There will only global mutex. No global cv. Every local Queue will have an 
            additional entry for notifying the task to go and read from Global Event Queue
            at the earliest.

            The event writer in global mode, will use the indivisual local cv for notification if
            required
*/
// <TODO> How to obtain the task ID when a task calls this api ???
void utils_task_handlers_send_event(boolean isLocalMode, 
                                    uint32_t event) {
    UTILS_TASK_HANDLER_STATUS* taskInfo = utils_task_handler_get_taskInfo();                                    

#if 0
    // First grab the event lock    
    pthread_mutex_lock(&__eventMutex);
    // Add the event to event Queue and signal others
    eventQueue[event] = UTILS_TASK_HANDLER_EVENT_ID | event;
    eventQueueEmpty = FALSE;
    pthread_cond_signal(&__eventCV);
    // Unlock the event lock
    pthread_mutex_unlock(&__eventMutex);
#endif
}

uint16_t utils_task_handlers_get_event(void) {
#if 0
    // First grab the event lock    
    pthread_mutex_lock(&__eventMutex);
    while (eventQueueEmpty) {
        pthread_cond_wait(&__eventCV, &__eventMutex);
    }
    for (uint8_t i = 0; i < eventQueueSize; i++) {

    }
    // Unlock the event lock
    pthread_mutex_unlock(&__eventMutex);
#endif
}

UTILS_TASK_HANDLER_STATUS* utils_task_handler_get_taskInfo(void) {
   UTILS_TASK_HANDLER_STATUS *taskInfo = pthread_getspecific(__taskInfoKey);
   return taskInfo;
}
/**********************************************************************************/
/*                       Internal Functions                                       */
/**********************************************************************************/
/*
    This function will be the startup routing for every task generated by this 
    library. This function will in turn call the user defined task functions
*/
static void* __utils_task_handlers_startup_routine(void *arg) {
    if (arg == NULL) {
        pthread_exit(0);
    }

    UTILS_TASK_HANDLER *worker = (UTILS_TASK_HANDLER *)arg;
    UTILS_TASK_HANDLER_STATUS *taskInfo = 
                (UTILS_TASK_HANDLER_STATUS*)pthread_getspecific(__taskInfoKey);

    if (taskInfo == NULL) {
        taskInfo = (UTILS_TASK_HANDLER_STATUS*)malloc(sizeof(UTILS_TASK_HANDLER_STATUS));
        taskInfo->__taskID = worker->taskID;
        pthread_setspecific(__taskInfoKey, taskInfo); // Save the data

        // Create a local event queue for the task (1 entry for Global + __utilsMaxLocalEvents)
        worker->events = (UTILS_TASK_HANDLER_EVENTS *)malloc(sizeof(UTILS_TASK_HANDLER_EVENTS));             
        worker->events->__eventQueue = (uint32_t *)malloc(sizeof(uint32_t) * (1 + __utilsMaxLocalEvents));
        worker->events->__eventQueueSize = (1 + __utilsMaxLocalEvents);
        worker->events->__eventQueueEmpty = TRUE; 
        pthread_cond_init(&worker->events->__eventCV, NULL);
        pthread_mutex_init(&worker->events->__eventMutex, NULL);

        // Call the task
        // TODO : See if we have to handle the return code of workers
        worker->handler(worker->arg);
    }

    pthread_exit(0);
}

static void __utils_task_handler_free_memory(void *arg) {
    if (arg != NULL) {
        free(arg);
    }
}

static void __utils_task_handler_create_taskInfoKey(void) {
    pthread_key_create(&__taskInfoKey, __utils_task_handler_free_memory);
}

/*
    Format :
      [events]  [List of Tasks]
        [ev0] : T0 T1  X T3 
        [ev1] : X  T1 T2 X
        [ev3] : X  X  X  T3

    We could have created an array of linked lists to achieve runtime add/del.
    But for faster memory access, we will create a 2D array. Each event will point
    to an array of max tasks. We will mark the tasks not interested using a special
    marker.
*/
static void __utils_task_handlers_create_event_interest_tbl(uint8_t numEvents, uint8_t numTasks) {
    if (eventInterestTableInitialized == TRUE) {
        return;
    }
    eventInterestTbl = (UTILS_TASK_HANLDER_EVENT_INTEREST_TBL *)malloc(numEvents *
                             sizeof(UTILS_TASK_HANLDER_EVENT_INTEREST_TBL)); 
    for (uint8_t e = 0; e < numEvents; e++) {
        eventInterestTbl[e].event = e;
        eventInterestTbl[e].tasks = (uint8_t *)malloc(sizeof(uint8_t) * numTasks);
        memset(eventInterestTbl[e].tasks, 0xFF, sizeof(uint8_t) * numTasks);
    }
    eventInterestTableInitialized = TRUE;
}

static void __utils_task_handlers_destroy_event_interest_tbl(uint8_t numEvents) {
    if (eventInterestTableInitialized == FALSE) {
        return;
    }
    for (uint8_t e = 0; e < numEvents; e++) {
        eventInterestTbl[e].event = numEvents; // Max Value
        free(eventInterestTbl[e].tasks);
    }
    free(eventInterestTbl);
    eventInterestTbl = NULL;
    eventInterestTableInitialized = FALSE;
}
 
