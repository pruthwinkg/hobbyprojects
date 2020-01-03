/*******************************************************************************
    Description : Task handler heade file

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

// Function pointer for task handling
typedef void *(*utils_task_handler)(void *);

extern pthread_t *utils_task_ids;

typedef struct {
    uint8_t taskID; // <In> Unique within a module
    utils_task_handler handler; // <In>
    const pthread_attr_t *attr; // <In>
    void *arg;                  // <In>
    void *task_ret; // Return value of the task <Out>
} UTILS_TASK_HANDLER;


/*******************************************************************************/
/*              Public Functions                                               */
/*******************************************************************************/
int utils_create_task_handlers(uint8_t num_workers, UTILS_TASK_HANDLER *workers);
int utils_wait_task_handlers(int num_workers, UTILS_TASK_HANDLER *workers);


#endif /* INCLUDE_UTILS_TASKHANDLER_H__ */
