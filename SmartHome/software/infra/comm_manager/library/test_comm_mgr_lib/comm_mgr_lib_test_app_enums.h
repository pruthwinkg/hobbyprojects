#include "smarthome_essentials.h"

BEGIN_ENUM(COMM_MGR_LIB_TEST_APP_ERR) {
    ADD_ENUM(COMM_MGR_LIB_TEST_APP_SUCCESS)
    ADD_ENUM(COMM_MGR_LIB_TEST_APP_RECV_ERR)
    ADD_ENUM(COMM_MGR_LIB_TEST_APP_UNKNOWN_EVENT)
} END_ENUM(COMM_MGR_LIB_TEST_APP_ERR);

BEGIN_ENUM(COMM_MGR_TEST_APP_TASK_ID) {
    ADD_ENUM_STR(COMM_MGR_TEST_APP_TASK_ID_COMM, "Communication")
    ADD_ENUM_STR(COMM_MGR_TEST_APP_TASK_ID_ANC_COMM, "Ancillary Communication")
    ADD_ENUM_STR(COMM_MGR_TEST_APP_TASK_ID_HOUSEKEEPER, "HouseKeeper")
    ADD_ENUM_STR(COMM_MGR_TEST_APP_TASK_ID_DATA_RECEIVER, "Data Receiver")
    ADD_ENUM(COMM_MGR_TEST_APP_TASK_ID_MAX)
} END_ENUM(COMM_MGR_TEST_APP_TASK_ID);

BEGIN_ENUM(COMM_MGR_APP_LOCAL_EVENT) {
    ADD_ENUM_STR(COMM_MGR_APP_LOCAL_EVENT_DATA_RECV, "External Data available")
    ADD_ENUM(COMM_MGR_APP_LOCAL_EVENT_MAX)
} END_ENUM(COMM_MGR_APP_LOCAL_EVENT);

BEGIN_ENUM(COMM_MGR_APP_GLOBAL_EVENT) {
    ADD_ENUM(COMM_MGR_APP_GLOBAL_EVENT_MAX)
} END_ENUM(COMM_MGR_APP_GLOBAL_EVENT);
