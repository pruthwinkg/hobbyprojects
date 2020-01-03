/*****************************************************************************
    Descritpion : The functionality of this file is to support task handling
                  for any process
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taskhandler.h"

pthread_t *utils_task_ids;

/*
    @brief This function creates task handlers for handling jobs

    @param workers : Array of UTILS_TASK_HANDLER
*/
int utils_create_task_handlers(uint8_t num_workers, UTILS_TASK_HANDLER *workers) {
    UTILS_LOG_TRACE("Creating %d task handlers\n", num_workers);
    int pthread_ret = 0;

    utils_task_ids = (pthread_t *)malloc(num_workers * sizeof(pthread_t));

    for (uint8_t i = 0; i < num_workers; i++) {
        if (workers[i].handler == NULL) {
            UTILS_LOG_TRACE("Handler is NULL for Task ID %d\n", workers[i].taskID);
            continue;
        }
        pthread_ret = pthread_create(&utils_task_ids[i],
                                    workers[i].attr,
                                    workers[i].handler,
                                    workers[i].arg);

        if (pthread_ret != 0) {
            UTILS_LOG_TRACE("Failed to create worker for %d\n", i);
        }
    }

    return 0;
}

/*
    @brief This function waits for all the workers in the UTILS_TASK_HANDLER list
*/
int utils_wait_task_handlers(int num_workers, UTILS_TASK_HANDLER *workers) {
    UTILS_LOG_TRACE("Waiting for %d task handlers\n", num_workers);
    int pthread_ret = 0;
    for(uint8_t i = 0; i < num_workers; i++) {
       pthread_ret = pthread_join(utils_task_ids[i], &workers[i].task_ret);
    }
    return 0;
}
