/*******************************************************************************
    Description : Comm manager client library
          Note  : Clients modules should spwan a thread for communications 
*******************************************************************************/
#ifndef INCLUDE_TEST_APP_COMM_MGR_LIB_H__
#define INCLUDE_TEST_APP_COMM_MGR_LIB_H__

#include "comm_mgr_lib.h"
#include "comm_mgr_cmn.h"
#include "comm_mgr_lib_test_app_enums.h"
#include "interface.h"

/******************************************************************************/
/*                           Functions                                        */
/******************************************************************************/
void *comm_mgr_test_app_communication_handler(void *arg);
void *comm_mgr_test_app_housekeeper(void *arg);
void *comm_mgr_test_app_data_receiver(void *arg);
void comm_mgr_lib_test_app_cb(COMM_MGR_LIB_EVENT event);
COMM_MGR_LIB_TEST_APP_ERR comm_mgr_test_app_process_events(uint16_t masterID, boolean isLocalMode, uint32_t event);
void comm_mgr_test_app_register_receiver_events(uint32_t taskID);
COMM_MGR_LIB_TEST_APP_ERR comm_mgr_test_app_process_comm_msg(COMM_MGR_MSG *comm_msg);

INTERFACE_LIB_ERR comm_mgr_lib_test_app_intf_text_cb(INTERFACE_LIB_QUERY_REQ_TYPE req_type, const char *query,
                                                    char *buf, uint16_t bufsize);
INTERFACE_LIB_ERR comm_mgr_lib_test_app_intf_process_token_query(uint16_t token, char *buf, uint16_t bufsize);
INTERFACE_LIB_ERR comm_mgr_lib_test_app_intf_process_full_query(const char *query, char *buf, uint16_t bufsize);

#endif /*INCLUDE_TEST_APP_COMM_MGR_LIB_H__*/
