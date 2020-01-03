#include <stdio.h>
#include "taskhandler.h"


void *func1(void *arg) {
    printf("Im in %s\n", __func__);
    return (void*)1;
}

void *func2(void *arg) {
    printf("Im in %s\n", __func__);
    return (void*)2;
}

UTILS_TASK_HANDLER test_handlers[] = 
{
    {
        .handler = func1,
        .attr = NULL,
        .arg = NULL,       
    },
    {
        .handler = func2,
        .attr = NULL,
        .arg = NULL,
    }
};

int main() {
    utils_create_task_handlers(2, test_handlers);
    utils_wait_task_handlers(2, test_handlers);
    return 0;
}



