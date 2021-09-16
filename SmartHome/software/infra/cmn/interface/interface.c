/*****************************************************************************
    Description : This is the interface library for interfacing with various
    componens of this system. This library provides various interfacing 
    mechansim to send user commands to various apps.

	Any user app can send certain messages to this library to get the internal
	details about various apps.	

    Example : apps/shell is one user app which can talk to this library.

******************************************************************************/

#include "interface.h"
#include <time.h>

static uint8_t interface_lib_initialized = 0;
static INTERFACE interface;
static INTERFACE_APP_CB *g_interface_app_cb = NULL;
/*
    This function needs to be called once by the app which is interested to
    expose its certain functionalities/data to others

    Depending on the security level specified, the interface library can
    make decisions like rejecting a query, filtering a query, allowing a
    query. It will also allow only certain INTERFACE_LIB_TYPE depending on security
    level of the app
*/
INTERFACE_LIB_ERR interface_lib_init(INTERFACE_LIB_SECURE_LEVEL level, INTERFACE_APP_CB *app_cb) {
    if(interface_lib_initialized == 1) {
        INTERFACE_LOG_ERROR("Interface library already intialized"); 
        return INTERFACE_LIB_FAILURE;
    }

    memset(&interface, 0, sizeof(INTERFACE));

    interface.level = level;
    interface.state = INTERFACE_LIB_STATE_ALLOW; // By default, when the library starts it allows queries
       
    g_interface_app_cb = app_cb;

    interface_lib_initialized = 1;
    return INTERFACE_LIB_SUCCESS;
}

/*
    Queries come to the library always comes in char array format

    The incoming buffer should have the below format: (INTERFACE_QUERY)

    <type (1 byte)> <req_type (1 byte)> <out_loc (2 byte)><query> <query>

    type : INTERFACE_LIB_QUERY_TYPE
    req_type : INTERFACE_LIB_QUERY_REQ_TYPE
    out_loc : How/where the responses should be sent back
    query : The query.

    The 'arg' parameter of this function is used to pass special hints to this function.
    But most of the times, simply the reference to the message via which this query request came in, is passed

*/
INTERFACE_LIB_ERR interface_lib_process_query(uint16_t req_uid, uint16_t res_uid, char *buf, 
                                              uint16_t bufsize, void *arg) {    
    if(interface_lib_initialized == 0) {
        return INTERFACE_LIB_NOT_INTIALIZED;
    }

    if(g_interface_app_cb == NULL) {
        INTERFACE_LOG_ERROR("Application callback is not registered");
        return INTERFACE_LIB_NOT_INTIALIZED;
    }

    if (interface.state == INTERFACE_LIB_STATE_DENY) {
        INTERFACE_LOG_DEBUG("Interface library currently in denied state. Cannot process the query");
        return INTERFACE_LIB_BAD_STATE;
    }

    if ((buf == NULL) || (bufsize < INTERFACE_QUERY_HEADER_SIZE)) {
        INTERFACE_LOG_ERROR("Bad buffer received. Size should be atleast %d bytes", INTERFACE_QUERY_HEADER_SIZE);
        return INTERFACE_LIB_BAD_QUERY;
    }

    INTERFACE_LIB_ERR rc = INTERFACE_LIB_SUCCESS;
    INTERFACE_QUERY query;
    char full_query[INTERFACE_LIB_MAX_QUERY_SIZE];
    memset(full_query, 0, sizeof(full_query));
    query.query = full_query;
    
    memcpy(&query, buf, INTERFACE_QUERY_HEADER_SIZE);
    memcpy(full_query, buf+INTERFACE_QUERY_HEADER_SIZE, bufsize-INTERFACE_QUERY_HEADER_SIZE);
    
    if(query.magic_num != INTERFACE_LIB_MAGIC_NUM) {
        INTERFACE_LOG_ERROR("Bad query received. Discarding");
        return INTERFACE_LIB_BAD_QUERY;
    }

    // Now process the query. The application registers during library init some callback functions.
    // The interface library will provide a local buffer for the app to write its response to it.
    // Once the response is written by the app, the interface library will take over
    // and start to process the data in the required format (lib_type), to the correct output
    // location considering various factors like Security level of the app, current state of library etc.
    // If the buffer supplied for the app to write its response is not sufficient, then the app needs to
    // return an error code INTERFACE_LIB_APP_RESPONSE_PENDING, so that the library will again call the 
    // application for more pending response.
    switch(query.query_type) {
        case INTERFACE_LIB_QUERY_TYPE_TEXT:
            rc = interface_lib_process_text_query(req_uid, res_uid, &query, arg);
            break;
        case INTERFACE_LIB_QUERY_TYPE_JSON:

            break;
        case INTERFACE_LIB_QUERY_TYPE_SCRIPT:

            break;
        default:
            INTERFACE_LOG_ERROR("Received an supported query type %d", query.query_type);
            return INTERFACE_LIB_BAD_QUERY;
    }
    return rc;
}

INTERFACE_LIB_ERR interface_lib_change_state(INTERFACE_LIB_STATE state) {
    if(interface_lib_initialized == 0) { 
        return INTERFACE_LIB_NOT_INTIALIZED; 
    }
    if(state > INTERFACE_LIB_STATE_RETRY) {
        return INTERFACE_LIB_BAD_STATE;
    }

    interface.state = state;

    return INTERFACE_LIB_SUCCESS;
}

/*
    For text type queries, most of the responses are handled by the apps itself. 
    The interface library takes care of writing the text responses from the apps to the
    required fd location considering factors like security level of the apps, state of library etc
*/
static INTERFACE_LIB_ERR interface_lib_process_text_query(uint16_t req_uid, uint16_t res_uid, 
                                                          INTERFACE_QUERY *query, void *arg) {
    if(query == NULL) {
        return INTERFACE_LIB_BAD_QUERY;
    }
    
    INTERFACE_LIB_ERR rc = INTERFACE_LIB_SUCCESS;
    char buf[INTERFACE_LIB_RES_BUF_SIZE];
    uint16_t bufsize = INTERFACE_LIB_RES_BUF_SIZE;
    uint16_t flags = 0;

    switch (query->query_req) {
        case INTERFACE_LIB_QUERY_REQ_TYPE_TOKEN:
            // This is the recommended request type for Text type of queries
            if(g_interface_app_cb->text_cb == NULL) {
                INTERFACE_LOG_ERROR("Text based Query type is not supported by the application");
                return INTERFACE_LIB_UNSUPPORTED_QUERY_TYPE;
            }
   
            interface_lib_create_response(query, req_uid, res_uid, arg);
            do {
                rc = g_interface_app_cb->text_cb(INTERFACE_LIB_QUERY_REQ_TYPE_TOKEN, query->query, 
                                                buf, bufsize);
                
                // Now ask the app to write the responses from the app to the response_type 
                // requested by the sender app. :)
                if (rc == INTERFACE_LIB_APP_RESPONSE_PENDING) {
                    INTERFACE_LIB_SET_FLAG(flags, INTERFACE_LIB_RES_IS_PENDING);
                    g_interface_app_cb->response_cb(query->response_type, buf, arg, flags);
                } else if (rc == INTERFACE_LIB_SUCCESS) {
                    INTERFACE_LIB_CLEAR_FLAG(flags, INTERFACE_LIB_RES_IS_PENDING);
                    g_interface_app_cb->response_cb(query->response_type, buf, arg, flags);
                } else {
                    break;
                }
            } while(rc != INTERFACE_LIB_APP_RESPONSE_PENDING);                                            

            break;
        case INTERFACE_LIB_QUERY_REQ_TYPE_FULL_QUERY:

            break;
        default:
            INTERFACE_LOG_ERROR("Received an supported query request type %d", query->query_req);
            return INTERFACE_LIB_BAD_QUERY;
    }
    return rc;
}

// Call this function once per request
static INTERFACE_LIB_ERR interface_lib_create_response(INTERFACE_QUERY *query, uint16_t req_uid, uint16_t res_uid, void *arg) {
    char buf[8096];
    uint16_t bufsize = sizeof(buf);
    memset(buf, 0, bufsize);
    uint16_t flags = 0;

    snprintf(buf, bufsize-strlen(buf), "<Magic magic_string=\"Interface Library:\"%d\">\n", req_uid);
    snprintf(buf+strlen(buf), bufsize-strlen(buf),"<ResponseApplication>%d</ResponseApplication>\n", res_uid);
    snprintf(buf+strlen(buf), bufsize-strlen(buf),"<QueryType>%s</QueryType>", interface_query_type_str[query->query_type]);
    snprintf(buf+strlen(buf), bufsize-strlen(buf),"<QueryReqType>%s</QueryReqType>\n", interface_query_req_type_str[query->query_req]);
    snprintf(buf+strlen(buf), bufsize-strlen(buf),"<Query>%s</Query>\n", query->query);
    snprintf(buf+strlen(buf), bufsize-strlen(buf),"<Response>\n");

    INTERFACE_LIB_SET_FLAG(flags, INTERFACE_LIB_RES_IS_HEADER);
    g_interface_app_cb->response_cb(query->response_type, buf, arg, flags);

    return INTERFACE_LIB_SUCCESS;
}
