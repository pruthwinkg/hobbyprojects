/*****************************************************************************
    Descritpion : The functionality of this file is to support task handling
                  for any process
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taskhandler.h"

boolean utils_task_handler_initialized = FALSE;

static pthread_t *utils_task_ids;

// These are global event Queues
// Multiple Readers - Multiple Writers
static pthread_mutex_t __gEventMutex = PTHREAD_MUTEX_INITIALIZER;
static uint32_t *__gEventQueue;
static uint8_t __gEventQueueReadersReference;
static uint8_t *__gEventQueueReaders;
static uint16_t __gEventQueueSize = 0;
static boolean __gEventQueueEmpty = TRUE;

static UTILS_TASK_HANLDER_EVENT_INTEREST_TBL *eventInterestTbl;
static boolean eventInterestTableInitialized = FALSE;

static uint8_t __utilsMaxTasks = 0;
static uint16_t __utilsMaxLocalEvents = 0;
static uint16_t __utilsMaxGlobalEvents = 0;
static UTILS_TASK_HANDLER* __utilsWorkerList = NULL;

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
                              uint16_t maxLocalEvents,
                              uint16_t maxGlobalEvents) {

    if(utils_task_handler_initialized == TRUE) {
        UTILS_LOG_ERROR("Task handlers are already created. Cannot be called twice\n");
        return -1;
    }

    UTILS_LOG_TRACE("Creating %d task handlers\n", num_workers);
    int pthread_ret = 0;

    utils_task_ids = (pthread_t *)malloc(num_workers * sizeof(pthread_t));

    // Create a Global event queue
    __gEventQueue = (UTILS_EVENT_ID *)malloc(sizeof(UTILS_EVENT_ID) * maxGlobalEvents);
    for (uint16_t i = 0; i < maxGlobalEvents; i++) {
        __gEventQueue[i] = UTILS_TASK_HANDLER_NO_EVENT;
    }
    __gEventQueueReaders = (uint8_t *)malloc(sizeof(uint8_t) * maxGlobalEvents);
    __gEventQueueReadersReference = 0;
    memset(__gEventQueueReaders, 0, sizeof(uint8_t) * maxGlobalEvents);
    __gEventQueueSize = maxGlobalEvents;
    __gEventQueueEmpty = TRUE;

    // Update the local Read-Only global variables
    __utilsMaxLocalEvents = maxLocalEvents;
    __utilsMaxGlobalEvents = maxGlobalEvents;
    __utilsMaxTasks = num_workers;
    __utilsWorkerList = workers;

    // Thread-specific key for storing the taskInfo
    (void) pthread_once(&__taskInfoKey_once, __utils_task_handler_create_taskInfoKey);

    // Create the local event interest table
    __utils_task_handlers_create_event_interest_tbl(maxLocalEvents, num_workers);
 
    utils_task_handler_initialized = TRUE;

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
void utils_task_handlers_register_event(uint16_t event, uint32_t taskID) {
    if(utils_task_handler_initialized == FALSE) {
        return;
    }

    if (eventInterestTableInitialized == FALSE) {
        return;
    }

    uint32_t *taskList = eventInterestTbl[event].tasks;
    uint8_t first_free_slot = __utilsMaxTasks;
    boolean slot_allocated = FALSE;
    boolean already_exists = FALSE;
    // Find a free slot for the task ID in the task list
    // Also check if the task ID already exists in the task list. In case
    // an event is added twice by user for the same task ID
    for (uint8_t i = 0; i < __utilsMaxTasks; i++) {
        if((taskList[i] == UTILS_TASK_HANDLER_EVENT_UNINTERESTED_TASK) &&
                (slot_allocated == FALSE)) {
            first_free_slot = i;
            slot_allocated = TRUE;
        }
        if(taskList[i] == taskID) {
            already_exists = TRUE;
        }
    }
    if((already_exists == FALSE) && (slot_allocated)) {
        taskList[first_free_slot] = taskID;
    }
}

void utils_task_handlers_unregister_event(uint16_t event, uint32_t taskID) {
    if(utils_task_handler_initialized == FALSE) {
        return;
    }

    if (eventInterestTableInitialized == FALSE) {
        return;
    }
    uint32_t *taskList = eventInterestTbl[event].tasks;

    for (uint8_t i = 0; i < __utilsMaxTasks; i++) {
        if (taskList[i] == taskID) {
            taskList[i] = UTILS_TASK_HANDLER_EVENT_UNINTERESTED_TASK;
            break;
        }
    }
}

/*
    @brief This function waits for all the workers in the UTILS_TASK_HANDLER list
*/
int utils_task_handlers_wait(int num_workers, UTILS_TASK_HANDLER *workers) {
    if(utils_task_handler_initialized == FALSE) {
        UTILS_LOG_ERROR("Utils task handler not created yet\n");
        return -1;
    }

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

        There will be only global mutex. No global cv. Every local Queue will have an 
        additional entry for notifying the task to go and read from Global Event Queue
        at the earliest.

        The event writer in global mode, will use the indivisual local cv for notification if
        required

    Local Event Queue Format :
                g L L L L L L ...
           g -> Read the Global event queue
           L -> Local events

    Global event Queue format:
            G G G G G G
         G > Global events
*/
int utils_task_handlers_send_event(boolean isLocalMode, 
                                    uint16_t event, boolean isHighPrio) {
    if(utils_task_handler_initialized == FALSE) {
        UTILS_LOG_ERROR("Utils task handler not created yet\n");
        return -1;
    }

    // Current event sending task info
    UTILS_TASK_HANDLER_STATUS *taskInfo = utils_task_handler_get_taskInfo();
    if ((taskInfo == NULL) || (taskInfo->__task == NULL)) {
        return -1;
    }

    UTILS_LOG_DEBUG("Event %d is sent by task ID %d\n", 
                                event, taskInfo->__task->taskID);
    // Handle Global event
    if (isLocalMode == FALSE) {
        // First grab the global event lock
        pthread_mutex_lock(&__gEventMutex);

        uint16_t free_slot = UTILS_TASK_HANDLER_EVENT_MASK;

        // Add the event to global event Queue.
        for (uint16_t j = 0; j < __utilsMaxGlobalEvents; j++) {
            // In case a previous event is not yet processed, ignore the current event
            if ((__gEventQueue[j] & UTILS_TASK_HANDLER_EVENT_MASK) == event) {
                pthread_mutex_unlock(&__gEventMutex);
                return 0;
            }

            if((free_slot == UTILS_TASK_HANDLER_EVENT_MASK) && 
               (__gEventQueue[j] == UTILS_TASK_HANDLER_NO_EVENT)) {
                free_slot = j; // Get the first available free slot     
            }
        }

        if (__gEventQueue[free_slot] == UTILS_TASK_HANDLER_NO_EVENT) { // Double check
            __gEventQueue[free_slot] = UTILS_TASK_HANDLER_EVENT_ID | UTILS_TASK_HANDLER_EVENT_MODE | event;
            // Reset the number of global event readers to the reference value
            __gEventQueueReaders[free_slot] = __gEventQueueReadersReference;
        }

        // Unlock the global event lock
        pthread_mutex_unlock(&__gEventMutex);

        // Now notify all the event enabled tasks using local queues
        return __utils_task_handlers_update_local_event_queue(isLocalMode, event, isHighPrio);
    } else {
        // Local events
        return __utils_task_handlers_update_local_event_queue(isLocalMode, event, isHighPrio);        
    }
    return 0;
}

// Note : App should keep calling this to get events
// This is a blocking API
// A single call to this API either returns a list of pending
// global OR local events. Local events will be returned in the
// order of priority. It is upto the app to process in this events
// according to its wish, call this API again for next set of events
/* 
    @param : eventList Pass a non-null memory to get the list of events
    @param : eventListSize Size of the eventList passed
    @return : Number of events in the event List

    @note : Its recommneded to pass the evenList size as max(Global events, local events)
           so that all the events are returned in the same call.
*/
uint16_t utils_task_handlers_get_events(uint32_t *eventList, uint16_t eventListSize) {
    UTILS_EVENT_ID event = UTILS_TASK_HANDLER_NO_EVENT;
    UTILS_EVENT_ID gEvent = UTILS_TASK_HANDLER_NO_EVENT;
    uint16_t eventCount = 0;
    boolean still_pending_events = FALSE;
    uint16_t num_of_entries_read = 0;

    if(utils_task_handler_initialized == FALSE) {
        UTILS_LOG_ERROR("Utils task handler not created yet\n");
        return 0;
    }

    if((eventList == NULL) || (eventListSize == 0)) {
        return 0;
    }

    // Current event reading task info
    UTILS_TASK_HANDLER_STATUS *taskInfo = utils_task_handler_get_taskInfo();
    if ((taskInfo == NULL) || (taskInfo->__task == NULL)) {
        return 0;
    }

    UTILS_LOG_DEBUG("Events are read by task ID %d\n", taskInfo->__task->taskID);

    UTILS_TASK_HANDLER_EVENTS *eventHandle = taskInfo->__task->events;

    // First check if the event notifications are enabled for this task
    if(taskInfo->__task->eventEnable == FALSE) {
        return 0;
    }

    // First grab the local event lock of self
    pthread_mutex_lock(&(eventHandle->__eventMutex));

    // Wait if the local queue is empty
    while (eventHandle->__eventQueueEmpty == TRUE) {
        UTILS_LOG_DEBUG("Task ID [%d] : Local event queue empty. Waiting in CV\n", 
                                                            taskInfo->__task->taskID);
        pthread_cond_wait(&(eventHandle->__eventCV), &(eventHandle->__eventMutex));
    }
    UTILS_LOG_DEBUG("Task ID [%d] : Local event queue not empty. Woke up from CV\n", 
                                                        taskInfo->__task->taskID);
    /* Reset the user eventList */
    for (uint16_t i = 0; i < eventListSize; i++) {
        eventList[i] = UTILS_TASK_HANDLER_NO_EVENT;
    }
    // Now read the local queue for any pending events. Once read, clear them
    // Always read from left of Queue, since the events are sorted according to
    // priorities (Global > High > Low)
    for (uint16_t i = 0; i < eventHandle->__eventQueueSize; i++) {
        if(eventHandle->__eventQueue[i] == UTILS_TASK_HANDLER_NO_EVENT) {
            continue;
        }
        // There is a pending event, read it and clear it
        event = eventHandle->__eventQueue[i];
        eventHandle->__eventQueue[i] = UTILS_TASK_HANDLER_NO_EVENT; // Clear it

        if (event & UTILS_TASK_HANDLER_EVENT_MODE) { // Check if global event
            // Unlock the local event lock, so that new events can be added ASAP
            pthread_mutex_unlock(&(eventHandle->__eventMutex));
            
            // Read the global event queue            
            // First grab the global event lock
            pthread_mutex_lock(&__gEventMutex);
            
            for (uint16_t j = 0; j < __utilsMaxGlobalEvents; j++) {
                gEvent = __gEventQueue[j];

                // Decrement the number of event readers for the global event
                if (gEvent != UTILS_TASK_HANDLER_NO_EVENT) {
                    eventList[eventCount] = gEvent; // Add the event to the user passed list
                    eventCount++;
                    if (eventCount >= eventListSize) {
                        break;
                    }
                    __gEventQueueReaders[gEvent & UTILS_TASK_HANDLER_EVENT_MASK]--;
                    
                    // If all readers have read this global event, clear the global event
                    if(__gEventQueueReaders[gEvent & UTILS_TASK_HANDLER_EVENT_MASK] == 0) {
                        __gEventQueue[j] = UTILS_TASK_HANDLER_NO_EVENT;
                    }
                }
            }
            // Unlock the global event lock
            pthread_mutex_unlock(&__gEventMutex);    
            return eventCount;
        }

        // Local event
        // Every call delivers list of events. Call the api again to get the next set of events
        // <TODO>
        eventList[eventCount] = event; // Add the event to the user passed list
        eventCount++;

        // Special case
        if (eventCount >= eventListSize) { // If the event queue passed by user is smaller than the queue size
            for (uint16_t j = i; j < eventHandle->__eventQueueSize; j++) {
                // even if one event is found, mark the queue as still not empty
                if (eventHandle->__eventQueue[i] != UTILS_TASK_HANDLER_NO_EVENT) { 
                    still_pending_events = TRUE;
                    break;
                }
            }
            break; // Need to break from main loop, since the eventList size is small
        }
        num_of_entries_read++;
    }

    // Mark the local queue as empty if all the events have been read
    // In case, the eventList passed by the user is small, then we cannot
    // read all the events in that case. If there are no events pending to be read even if user passed
    // list size is small, mark the queue is empty
    if ((still_pending_events == FALSE) || (num_of_entries_read >= eventHandle->__eventQueueSize)) { // Full queue is read
        eventHandle->__eventQueueEmpty = TRUE;
    }
    // Unlock the local event lock
    pthread_mutex_unlock(&(eventHandle->__eventMutex));

    return eventCount;
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

    uint16_t high_priority_queue_size = 0;
    UTILS_TASK_HANDLER *worker = (UTILS_TASK_HANDLER *)arg;
    UTILS_TASK_HANDLER_STATUS *taskInfo = 
                (UTILS_TASK_HANDLER_STATUS*)pthread_getspecific(__taskInfoKey);

    if (taskInfo == NULL) {
        taskInfo = (UTILS_TASK_HANDLER_STATUS*)malloc(sizeof(UTILS_TASK_HANDLER_STATUS));
        taskInfo->__task = worker;
        pthread_setspecific(__taskInfoKey, taskInfo); // Save the data

        // Create a local event queue for the task (1 entry for Global + __utilsMaxLocalEvents)
        worker->events = (UTILS_TASK_HANDLER_EVENTS *)malloc(sizeof(UTILS_TASK_HANDLER_EVENTS));             
        worker->events->__eventQueueSize = (1 + __utilsMaxLocalEvents);
        worker->events->__eventQueue = (UTILS_EVENT_ID *)malloc(sizeof(UTILS_EVENT_ID) * (1+__utilsMaxLocalEvents));
        for (uint16_t i = 0 ; i < worker->events->__eventQueueSize; i++) {
            worker->events->__eventQueue[i] = UTILS_TASK_HANDLER_NO_EVENT;
        }
        worker->events->__eventQueueEmpty = TRUE; 
        pthread_cond_init(&worker->events->__eventCV, NULL);
        pthread_mutex_init(&worker->events->__eventMutex, NULL);

        // This is to count how many readers are there for each global event
        if(worker->eventEnable == TRUE) {
            __gEventQueueReadersReference++;
        }
        
        /* For best effort priority event delivery */
        // Calculate the % size of local queue allocated for high prio local events
        if (worker->taskattr == NULL) {
            high_priority_queue_size = (__utilsMaxLocalEvents * \
                                UTILS_TASK_HANDLER_EVENT_PRIO_HIGH_PERCENT) / 100;
            worker->events->__eventQueueHighPrioSize = high_priority_queue_size; 
        } else {
            if (worker->taskattr->eventHighPrioPercent > 100) {
                worker->taskattr->eventHighPrioPercent = 100;
            }
            high_priority_queue_size = (__utilsMaxLocalEvents * \
                                        worker->taskattr->eventHighPrioPercent) / 100;
            worker->events->__eventQueueHighPrioSize = high_priority_queue_size; 
        }
        // Call the task
        // TODO : See if we have to handle the return code of workers
        worker->handler(worker->arg);
    }

    pthread_exit(0);
}

// This function makes sure that index of the woker list and task ID are different
// It means in a app, the task IDs need NOT start from '0' and also, the tasks
// can be in any order in the woker list defined by the app
static UTILS_TASK_HANDLER* __utils_task_handlers_get_task(uint32_t taskID) {

    for (uint8_t i = 0; i < __utilsMaxTasks; i++) {
       if(taskID == __utilsWorkerList[i].taskID) {
            return &__utilsWorkerList[i];
       }
    }
    return NULL;
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
static void __utils_task_handlers_create_event_interest_tbl(uint16_t numEvents, uint8_t numTasks) {
    if (eventInterestTableInitialized == TRUE) {
        return;
    }
    if ((numEvents == 0) || (numTasks == 0)) {
        return;
    }

    eventInterestTbl = (UTILS_TASK_HANLDER_EVENT_INTEREST_TBL *)malloc(numEvents *
                             sizeof(UTILS_TASK_HANLDER_EVENT_INTEREST_TBL)); 
    for (uint16_t e = 0; e < numEvents; e++) {
        eventInterestTbl[e].event = e;
        eventInterestTbl[e].tasks = (uint32_t *)malloc(sizeof(uint32_t) * numTasks);
        for (uint8_t t = 0; t < numTasks; t++) {
            eventInterestTbl[e].tasks[t] = UTILS_TASK_HANDLER_EVENT_UNINTERESTED_TASK;
        }                                                      
    }
    eventInterestTableInitialized = TRUE;
}

static void __utils_task_handlers_destroy_event_interest_tbl(uint16_t numEvents) {
    if (eventInterestTableInitialized == FALSE) {
        return;
    }
    for (uint16_t e = 0; e < numEvents; e++) {
        eventInterestTbl[e].event = numEvents; // Max Value
        free(eventInterestTbl[e].tasks);
    }
    free(eventInterestTbl);
    eventInterestTbl = NULL;
    eventInterestTableInitialized = FALSE;
}

static uint32_t* __utils_task_handlers_get_tasks_from_event_interest_tbl(uint16_t event) {
    if (eventInterestTableInitialized == FALSE) {
        return NULL;
    }

    if(event >= __utilsMaxLocalEvents) {
        return NULL;
    }

    UTILS_TASK_HANLDER_EVENT_INTEREST_TBL evIT = eventInterestTbl[event];

    if (evIT.tasks != NULL) {
        return evIT.tasks;
    }
    return NULL;
}

static int __utils_task_handlers_update_local_event_queue(boolean isLocalMode, uint16_t event, boolean isHighPrio) {
    uint32_t *taskList = NULL;

    if (isLocalMode == TRUE) { // Only for local mode. In global everyone will be notified
        // Check the event Interest table for notifiying the tasks
        taskList = __utils_task_handlers_get_tasks_from_event_interest_tbl(event);
        if(taskList == NULL) {
            return -1;
        }
    }

    // Iterate the task list for this event
    for(uint8_t i = 0; i < __utilsMaxTasks; i++) {
        if (isLocalMode == TRUE) { // Only for local mode. In global everyone will be notified
            if (taskList[i] == UTILS_TASK_HANDLER_EVENT_UNINTERESTED_TASK) {                
                continue; // Uninterested tasks
            }
        }

        UTILS_TASK_HANDLER *task = NULL;
        if (isLocalMode == TRUE) {
            task = __utils_task_handlers_get_task(taskList[i]);
        } else { // For global event
            task = &__utilsWorkerList[i];  
        }
        UTILS_TASK_HANDLER_EVENTS *eventHandle = task->events;
      
        // Skip if the event mechanism is disabled for the task
        if(task->eventEnable == FALSE) {
            continue;
        }

        // First grab the event lock for the task
        pthread_mutex_lock(&(eventHandle->__eventMutex));
        
        uint16_t free_slot = 0;
        uint32_t eventStatus = __utils_task_handlers_get_event_index(isLocalMode, event, isHighPrio, 
                                                                eventHandle, &free_slot);

        // In case a previous event is not yet processed, ignore the current event
        if(eventStatus != UTILS_TASK_HANDLER_NO_EVENT) {
            pthread_mutex_unlock(&(eventHandle->__eventMutex));
            continue;
        }
        
        if (isLocalMode == TRUE) {
            if (isHighPrio == TRUE) { // Priority is only for local events
                eventHandle->__eventQueue[free_slot] = UTILS_TASK_HANDLER_EVENT_ID | \
                                                      UTILS_TASK_HANDLER_EVENT_PRIO | event;
            } else {
                eventHandle->__eventQueue[free_slot] = UTILS_TASK_HANDLER_EVENT_ID | event;
            }
        } else {
            // Mark the event as Global event
            // Bit 17 = 1 is global
            uint16_t gSlot = UTILS_TASK_HANDLER_EVENT_QUEUE_GLOBAL_BEGIN;
            eventHandle->__eventQueue[gSlot] = UTILS_TASK_HANDLER_EVENT_ID | UTILS_TASK_HANDLER_EVENT_MODE; 
        }

        // If the event Queue is empty, notify the tasks interested in this event
        // This is the case when event is added for the first time OR all the events
        // in the queue has been processed and reader is sleeping.
        if(eventHandle->__eventQueueEmpty == TRUE) {
            pthread_cond_signal(&(eventHandle->__eventCV));
        }
        eventHandle->__eventQueueEmpty = FALSE;

        // Unlock the event lock for the task
        pthread_mutex_unlock(&(eventHandle->__eventMutex));
    }
    return 0;
}

// This function searches the event queue for the given event
// This function also returns a free slot according to priority, in case the event is not found
static uint32_t __utils_task_handlers_get_event_index(boolean isLocalMode, uint16_t event, 
                                            boolean isHighPrio, 
                                            UTILS_TASK_HANDLER_EVENTS *eventHandle,
                                            uint16_t *free_slot) {
    uint16_t first_free_slot = 0;

    // Global event
    if (isLocalMode == FALSE) {
        // Pending global event
        if(eventHandle->__eventQueue[0] != UTILS_TASK_HANDLER_NO_EVENT) {
            return eventHandle->__eventQueue[0];
        }
        return UTILS_TASK_HANDLER_NO_EVENT; // No pending global event
    }
    // Free slot is applicable only for local events
    // For local events, 0 can never be the slot, since it is reserved for global
    *free_slot = 0; 
    uint16_t start = UTILS_TASK_HANDLER_EVENT_QUEUE_LOCAL_BEGIN;

    // Note : If an event is sent as High Prio by Task A, and the same event is sent as
    //   low prio by task B, then we should not add twice for the same event.
    // Rules : 1) If a High Prio already exists, ignore the current low prio
    //         2) If a low prio already exists, then replace it with high prio in the correct slot
    //         3) In all other cases, add the event with prio passed by the task or ignore it
   
    if (isHighPrio == FALSE) { // Low priority event
        start += eventHandle->__eventQueueHighPrioSize;
        // In case if the full queue is allocated for highPrio events, then there wont
        // be any option but to use the highPrio slots for even low priority events
        if (start > eventHandle->__eventQueueSize) {
            start = UTILS_TASK_HANDLER_EVENT_QUEUE_LOCAL_BEGIN;
        }
    }

    for (uint16_t i = UTILS_TASK_HANDLER_EVENT_QUEUE_LOCAL_BEGIN; i < eventHandle->__eventQueueSize; i++) {
        // Find correct free slots while iterating the entire queue
        if((*free_slot == 0) && (eventHandle->__eventQueue[i] == UTILS_TASK_HANDLER_NO_EVENT)) {
            if (isHighPrio == TRUE) { // Current event is high prio
                *free_slot = i; // Get the first available free slot
            } else { // current event is low prio
                if (i >= start) { // Use the low prio slots
                    *free_slot = i; // Get the first available free slot
                }
            }
        }

        //Refer the rules mentioned above for this logic. 
        // We have to worry, only when an event already exists. Then, act according to the above rules
        if((eventHandle->__eventQueue[i] & UTILS_TASK_HANDLER_EVENT_MASK) == event) {
            if ((eventHandle->__eventQueue[i] & UTILS_TASK_HANDLER_EVENT_PRIO)) { // If a High prio already exists (Rule 1)
                return i; // Ignore the current event (both high or low)
            } else { // low prio exists
                 if (isHighPrio == FALSE) { // Current event is also low prio, ignore current
                    return i;
                 } else { // Current event is high and a low prio exists, replace it (Rule 2)
                     if (*free_slot == 0) { // If a free_slot is not yet found, just replace it
                         eventHandle->__eventQueue[i] = UTILS_TASK_HANDLER_EVENT_ID | \
                                                        UTILS_TASK_HANDLER_EVENT_PRIO | event;
                         return i;                                                        
                     } else { // If a better free_slot id found for the high prio event, delete currrent and create new
                         eventHandle->__eventQueue[i] = UTILS_TASK_HANDLER_NO_EVENT;
                         eventHandle->__eventQueue[*free_slot] = UTILS_TASK_HANDLER_EVENT_ID | \
                                                         UTILS_TASK_HANDLER_EVENT_PRIO | event;
                        return *free_slot;                                                         
                     }
                 }
            }
        }
    }

    return UTILS_TASK_HANDLER_NO_EVENT;
}

