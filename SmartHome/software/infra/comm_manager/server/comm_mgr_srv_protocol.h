/*******************************************************************************
    Description : Communication manager prototypes and structures

 *******************************************************************************/
#ifndef INCLUDE_COMM_MGR_PROTOCOL_H__
#define INCLUDE_COMM_MGR_PROTOCOL_H__

#include "comm_mgr_srv.h"
#include "comm_mgr_cmn.h"

// There is no valid bit. So the list must always contain
// valid registered apps
typedef struct {
    uint32_t UID;
    uint32_t clientID;
    uint32_t priority; // TODO : Change it to enum later    
} COMM_MGR_SRV_REG_APPS;

typedef struct {
    uint32_t reserved; // TODO : Update this later 
} COMM_MGR_SRV_PROTO_TBL_PROPERTY;

// Map of <UID, Server FD>
typedef struct {        
    uint32_t UID;
    int server_fd;
    COMM_MGR_SRV_PROTO_TBL_PROPERTY *property; // If null, use default
} COMM_MGR_SRV_PROTO_TBL;



extern COMM_MGR_SRV_REG_APPS *comm_mgr_reg_apps_list;

/************************************************************************/
/*                   Internal helper functions                          */
/************************************************************************/



/************************************************************************/
/*                   Public  functions                                  */
/************************************************************************/
//COMM_MGR_SRV_ERR comm_mgr_srv_protocol_


#endif /* INCLUDE_COMM_MGR_PROTOCOL_H__ */
