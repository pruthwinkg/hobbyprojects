/*******************************************************************************
    Description : Comm manager client library
          Note  : Clients modules should spwan a thread for communications 
*******************************************************************************/
#ifndef INCLUDE_TEST_APP_COMM_MGR_LIB_H__
#define INCLUDE_TEST_APP_COMM_MGR_LIB_H__

#include "comm_mgr_lib.h"
#include "comm_mgr_cmn.h"
#include "comm_mgr_lib_test_app_enums.h"

void *comm_mgr_test_app_communication_handler(void *arg);
void *comm_mgr_test_app_housekeeper(void *arg);
void *comm_mgr_test_app_data_receiver(void *arg);
void comm_mgr_lib_test_app_cb(COMM_MGR_LIB_EVENT event);



#endif /*INCLUDE_TEST_APP_COMM_MGR_LIB_H__*/
