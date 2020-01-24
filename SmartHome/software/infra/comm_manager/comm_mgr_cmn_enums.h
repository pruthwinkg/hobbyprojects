/*******************************************************************************
    Description : Communication manager common header files for server and lib

*******************************************************************************/
#ifndef INCLUDE_COMM_MGR_CMN_ENUMS_H__
#define INCLUDE_COMM_MGR_CMN_ENUMS_H__

#include "smarthome_essentials.h"


BEGIN_ENUM(COMM_MGR_PROTO_STATES) {
    ADD_ENUM(COMM_MGR_PROTO_DISCOVERY_START)
    ADD_ENUM(COMM_MGR_PROTO_DISCOVERY_DONE)
    ADD_ENUM(COMM_MGR_PROTO_LEARNING_START)
    ADD_ENUM(COMM_MGR_PROTO_LEARNING_DONE)
    ADD_ENUM(COMM_MGR_PROTO_DATATRANSFER_READY)
} END_ENUM(COMM_MGR_PROTO_STATES);

// Below are the main msg types
BEGIN_ENUM(COMM_MGR_MSG_TYPE) {
    ADD_ENUM_STR(COMM_MGR_MSG_PROTOCOL, "Used for discovery/learning")
    ADD_ENUM_STR(COMM_MGR_MSG_ACK, "Ack messages for protocol and data")
    ADD_ENUM_STR(COMM_MGR_MSG_DATA, "Used for data txfer after discovery")
    ADD_ENUM_STR(COMM_MGR_MSG_SYSTEM, "Used for sending system info")
    ADD_ENUM(COMM_MGR_MSG_MAX)
} END_ENUM(COMM_MGR_MSG_TYPE);

// Sub messages for each main msg types if required
BEGIN_ENUM(COMM_MGR_SUBMSG_TYPE) {
    ADD_ENUM(COMM_MGR_SUBMSG_DISCOVERY)
    ADD_ENUM(COMM_MGR_SUBMSG_LEARNING)
    ADD_ENUM(COMM_MGR_SUBMSG_DATATXREADY)
    ADD_ENUM(COMM_MGR_SUBMSG_PROTO_ACK)
    ADD_ENUM(COMM_MGR_SUBMSG_PROTO_NACK)
    ADD_ENUM(COMM_MGR_SUBMSG_DATA_ACK)
    ADD_ENUM(COMM_MGR_SUBMSG_DATA_NACK) 
} END_ENUM(COMM_MGR_SUBMSG_TYPE);


// Below are the Communication Manager msg priority in Order
BEGIN_ENUM(COMM_MGR_MSG_PRIORITY) {
    ADD_ENUM_VAL(COMM_MGR_MSG_PRIORITY_CRITICAL, 0xA)
    ADD_ENUM_VAL(COMM_MGR_MSG_PRIORITY_HIGH, 0xB)
    ADD_ENUM_VAL(COMM_MGR_MSG_PRIORITY_NORMAL, 0xC) // Default priority
    ADD_ENUM_VAL(COMM_MGR_MSG_PRIORITY_LOW, 0xD)
    ADD_ENUM_VAL(COMM_MGR_MSG_PRIORITY_DEBUG, 0xE)
} END_ENUM(COMM_MGR_MSG_PRIORITY);

#endif /* INCLUDE_COMM_MGR_CMN_ENUMS_H__ */ 
