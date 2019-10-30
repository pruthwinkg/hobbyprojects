/*******************************************************************************
    Description: Contains all the protypes for the system manager
    

*******************************************************************************/
#include <stdint.h>
#include <stdio.h>

#define SYS_MGR_LOG     printf


#define SYS_MGR_ERR_BASE        (0xFFFFFF00)

typedef enum {
    SYS_MGR_SUCCESS = 0,
    SYS_MGR_INIT_FAILURE = SYS_MGR_ERR_BASE,
    SYS_MGR_CLIENT_INIT_FAILURE,
} SYS_MGR_ERR;


typedef struct {
    uint32_t clientID;
    char clientName[128];
    char clientLocation[128];
} SYS_MGR_CLIENT_TBL;
