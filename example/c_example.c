#include <stdio.h>

/* Make our log calls easy to see */
#define SIMPLELOGGER_ENABLE_SMALL_MACROS
#include "../simplelogger.h"

/* define our global log function pointer */
simplelogger_log_function simplelogger_global_log_function;

/* Our simple log function prints to stderr */
void stderr_log_function(const char* logger_name, 
    const struct SL_LogLocation* location,
    const enum SL_LogLevel level,
    const char* log_string ){
    const char* level_string;
    
    SL_LOGLEVEL_TO_STRING( level_string, level );

    /* Print message in format of:
     *  [LOGGER_NAME] LEVEL - message at FILE:FUNCTION:LINE
     */
    fprintf( stderr, "[%s] %s - %s at %s:%s:%d\n", 
        logger_name,
        level_string,
        log_string,
        location->file,
        location->function,
        location->line_number );
}

static void other_function( int arg ){
    {
        char buffer[ 1024 ];
        snprintf( buffer, 1024, "Called function with arg %d", arg );
        LOG_TRACE( "other_logger", buffer );
    }

    LOG_DEBUG( "main_logger", "Just calculated some value" );
}

int main( int argc, char** argv ){
    /* First set our global log function pointer */
    simplelogger_global_log_function = stderr_log_function;

    /* Be verbose about what our parameters are */
    SIMPLELOGGER_INFO_CSTR( "main_logger", "We just set our log function" );

    /* We have set SIMPLELOGGER_ENABLE_SMALL_MACROS, so we can just use 
     * LOG_[level] to log a message
     */
    LOG_INFO( "main_logger", "We are doing this the simple way" );

    other_function( argc );

    /* Various levels of log information */
    LOG_TRACE( "foo", "Logging a trace message" );
    LOG_DEBUG( "foo", "Logging a debug message" );
    LOG_INFO( "foo", "Logging an info message" );
    LOG_WARN( "foo", "Logging a warning message" );
    LOG_ERROR( "foo", "Logging an error message" );
    LOG_FATAL( "foo", "Logging a fatal message" );

    return 0;
}
