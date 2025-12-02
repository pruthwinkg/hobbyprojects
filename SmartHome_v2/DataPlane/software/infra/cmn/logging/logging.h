/*******************************************************************************
    Description : Logging library

*******************************************************************************/

#ifndef INCLUDE_LOGGING_LIB_H__
#define INCLUDE_LOGGING_LIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "smarthome_essentials.h"

#define LOG_MAX_FILENAME_LEN    (512)
#define LOG_INTERNAL_BUF_SIZE   (240)

typedef enum {
    LOG_LVL_CRITICAL = 0,
    LOG_LVL_ERROR,
    LOG_LVL_TRACE,
    LOG_LVL_DEBUG,
    LOG_LVL_ALL
} LOG_LEVEL;

typedef struct {
    LOG_LEVEL level; // All logs < level will be recorded 
    boolean isFileLoggingEn;
    char fileName[LOG_MAX_FILENAME_LEN];
    FILE *fp;
} LOG_PROPERTIES;

extern LOG_PROPERTIES log_property;

#define LOG_ERROR(...)       { \
                             char __log_internal_buf[LOG_INTERNAL_BUF_SIZE]; \
                             if(log_property.level >= LOG_LVL_ERROR) { \
                                snprintf(__log_internal_buf, sizeof(__log_internal_buf), __VA_ARGS__); \
                                log_lib_message(LOG_LVL_ERROR, __func__, __LINE__, __log_internal_buf); \
                             } \
                             } \


#define LOG_TRACE(...)       { \
                             char __log_internal_buf[LOG_INTERNAL_BUF_SIZE]; \
                             if(log_property.level >= LOG_LVL_TRACE) { \
                                snprintf(__log_internal_buf, sizeof(__log_internal_buf), __VA_ARGS__); \
                                log_lib_message(LOG_LVL_TRACE, __func__, __LINE__, __log_internal_buf); \
                             } \
                             } \


#define LOG_DEBUG(...)       { \
                             char __log_internal_buf[LOG_INTERNAL_BUF_SIZE]; \
                             if(log_property.level >= LOG_LVL_DEBUG) { \
                                snprintf(__log_internal_buf, sizeof(__log_internal_buf), __VA_ARGS__); \
                                log_lib_message(LOG_LVL_DEBUG, __func__, __LINE__, __log_internal_buf); \
                             } \
                             } \


void log_lib_init(const char *filename, LOG_LEVEL level);
void log_lib_message(LOG_LEVEL level, const char *func, const int line, const char *msg);
void log_lib_close(void);

#endif /* INCLUDE_LOGGING_LIB_H__ */
