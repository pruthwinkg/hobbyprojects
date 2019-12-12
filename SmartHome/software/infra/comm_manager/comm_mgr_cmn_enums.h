/*******************************************************************************
    Description : Communication manager common header files for server and lib

*******************************************************************************/
#ifndef INCLUDE_COMM_MGR_CMN_ENUMS_H__
#define INCLUDE_COMM_MGR_CMN_ENUMS_H__

#include "smarthome_essentials.h"


BEGIN_ENUM(COMM_MGR_PROTO_STATES) {
    ADD_ENUM_VAL_STR(COMM_MGR_PROTO_DISOVERY_START, 0, "")
    ADD_ENUM_STR(COMM_MGR_PROTO_DISOVERY_DONE, "")
} END_ENUM(COMM_MGR_PROTO_STATES);

BEGIN_ENUM(COMM_MGR_MSG_TYPE) {
    ADD_ENUM_VAL_STR(COMM_MGR_MSG_PROTOCOL, 0, "Used for discovery/learning")
    ADD_ENUM_STR(COMM_MGR_MSG_ACK, "Ack messages for protocol and data as well")
    ADD_ENUM_STR(COMM_MGR_MSG_DATA, "Used for data transfer after discovery")
    ADD_ENUM(COMM_MGR_MSG_MAX)
} END_ENUM(COMM_MGR_MSG_TYPE);



#endif /* INCLUDE_COMM_MGR_CMN_ENUMS_H__ */ 
