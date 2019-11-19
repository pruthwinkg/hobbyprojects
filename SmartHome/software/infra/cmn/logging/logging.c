/*******************************************************************************
    Description : Logging library

*******************************************************************************/

#include "logging.h"

LOG_PROPERTIES log_property;

const char *log_level_str[] = {
    "Critical",
    "Error",
    "Trace", 
    "Debug"
};

void log_lib_init(const char *filename, LOG_LEVEL level) {
    memset(&log_property, 0, sizeof(LOG_PROPERTIES));
    log_property.level = level;

    if(filename != NULL) {
        strcpy(log_property.fileName, filename);
        log_property.isFileLoggingEn = TRUE;
        log_property.fp = fopen(filename, "w+");
    }
}

void log_lib_message(LOG_LEVEL level, 
                    const char *func, 
                    const int line, 
                    const char *msg) { 
    time_t now;
    time(&now);
    
    if(log_property.isFileLoggingEn) {
        fprintf(log_property.fp, "[%.19s] %s [%d] (%s) : %s\n", ctime(&now), func, line, log_level_str[level], msg);
    } else {
        fprintf(stdout, "[%.19s] %s [%d] (%s) : %s\n", ctime(&now), func, line, log_level_str[level], msg);
       
    }
}

void log_lib_close() {
    if(log_property.isFileLoggingEn) {
        fclose(log_property.fp);
    }
}

#ifdef TEST_LOG_LIB

int main() {
    log_lib_init(NULL, LOG_LVL_DEBUG);


    LOG_ERROR("This is an error message %d", 1);
    LOG_TRACE("This is an trace message");
    LOG_DEBUG("This is an debug message");

    log_lib_close();
}

#endif
