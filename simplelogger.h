/*
 * Simple logging framework.
 * 
 * License: Unlicense(http://unlicense.org)
 *
 * Find the latest version at https://github.com/rm5248/simplelogger
 *
 * To use: Copy this file into your source directory and define storage for
 * simplelogger_global_log_function in a source file.  Then set your 
 * simplelogger_global_log_function to be a function pointer to a function
 * that you control.
 */
#ifndef SIMPLELOGGER_H
#define SIMPLELOGGER_H

#ifndef SIMPLELOGGER_FUNCTION
  #ifdef _MSC_VER
    #define SIMPLELOGGER_FUNCTION __FUNCSIG__
  #else
    #define SIMPLELOGGER_FUNCTION __func__
  #endif
#endif

/**
 * Where the log message was generated from.
 */
struct SL_LogLocation{
    int line_number;
    const char* function;
    const char* file;
};

/**
 * Level of the log message
 */
enum SL_LogLevel{
    SL_TRACE,
    SL_DEBUG,
    SL_INFO,
    SL_WARN,
    SL_ERROR,
    SL_FATAL
};

#define SL_LOGLEVEL_TO_STRING( stringPtr, level ) do{\
  switch( level ){ \
  case SL_TRACE: stringPtr = "TRACE"; break;\
  case SL_DEBUG: stringPtr = "DEBUG"; break;\
  case SL_INFO: stringPtr = "INFO"; break;\
  case SL_WARN: stringPtr = "WARN"; break;\
  case SL_ERROR: stringPtr = "ERROR"; break;\
  case SL_FATAL: stringPtr = "FATAL"; break;\
  default: stringPtr = "UNKN"; break;\
  }}while(0)

/**
 * Pointer to a function that does the actual log operation.
 */
typedef void (*simplelogger_log_function)(const char* logger_name, 
    const struct SL_LogLocation* location,
    const enum SL_LogLevel level,
    const char* log_string );

/**
 * Global log pointer
 */
extern simplelogger_log_function simplelogger_global_log_function;

#define SIMPLELOGGER_LOG_CSTR( logger, message, level ) do{\
    if( !simplelogger_global_log_function ) break;\
    struct SL_LogLocation location;\
    location.line_number = __LINE__;\
    location.file = __FILE__;\
    location.function = SIMPLELOGGER_FUNCTION;\
    simplelogger_global_log_function( logger, &location, level, message );\
    } while(0)

#define SIMPLELOGGER_TRACE_CSTR( logger, message ) do{\
    SIMPLELOGGER_LOG_CSTR( logger, message, SL_TRACE);\
    } while(0)
#define SIMPLELOGGER_DEBUG_CSTR( logger, message ) do{\
    SIMPLELOGGER_LOG_CSTR( logger, message, SL_DEBUG);\
    } while(0)
#define SIMPLELOGGER_INFO_CSTR( logger, message ) do{\
    SIMPLELOGGER_LOG_CSTR( logger, message, SL_INFO);\
    } while(0)
#define SIMPLELOGGER_WARN_CSTR( logger, message ) do{\
    SIMPLELOGGER_LOG_CSTR( logger, message, SL_WARN);\
    } while(0)
#define SIMPLELOGGER_ERROR_CSTR( logger, message ) do{\
    SIMPLELOGGER_LOG_CSTR( logger, message, SL_ERROR);\
    } while(0)
#define SIMPLELOGGER_FATAL_CSTR( logger, message ) do{\
    SIMPLELOGGER_LOG_CSTR( logger, message, SL_FATAL);\
    } while(0)

#ifdef __cplusplus
#include <string>
#include <sstream>

#define SIMPLELOGGER_TRACE_STDSTR( logger, message ) do{\
    std::stringstream stream;\
    stream << message;\
    SIMPLELOGGER_LOG_CSTR( logger, stream.str().c_str(), SL_TRACE);\
    } while(0)
#define SIMPLELOGGER_DEBUG_STDSTR( logger, message ) do{\
    std::stringstream stream;\
    stream << message;\
    SIMPLELOGGER_LOG_CSTR( logger, stream.str().c_str(), SL_DEBUG);\
    } while(0)
#define SIMPLELOGGER_INFO_STDSTR( logger, message ) do{\
    std::stringstream stream;\
    stream << message;\
    SIMPLELOGGER_LOG_CSTR( logger, stream.str().c_str(), SL_INFO);\
    } while(0)
#define SIMPLELOGGER_WARN_STDSTR( logger, message ) do{\
    std::stringstream stream;\
    stream << message;\
    SIMPLELOGGER_LOG_CSTR( logger, stream.str().c_str(), SL_WARN);\
    } while(0)
#define SIMPLELOGGER_ERROR_STDSTR( logger, message ) do{\
    std::stringstream stream;\
    stream << message;\
    SIMPLELOGGER_LOG_CSTR( logger, stream.str().c_str(), SL_ERROR);\
    } while(0)
#define SIMPLELOGGER_FATAL_STDSTR( logger, message ) do{\
    std::stringstream stream;\
    stream << message;\
    SIMPLELOGGER_LOG_CSTR( logger, stream.str().c_str(), SL_FATAL);\
    } while(0)

#ifdef SIMPLELOGGER_ENABLE_AUTO_MACROS
  #define SIMPLELOGGER_TRACE( logger, message )\
    SIMPLELOGGER_TRACE_STDSTR(logger, message )
  #define SIMPLELOGGER_DEBUG( logger, message )\
    SIMPLELOGGER_DEBUG_STDSTR(logger, message )
  #define SIMPLELOGGER_INFO( logger, message )\
    SIMPLELOGGER_INFO_STDSTR(logger, message )
  #define SIMPLELOGGER_WARN( logger, message )\
    SIMPLELOGGER_WARN_STDSTR(logger, message )
  #define SIMPLELOGGER_ERROR( logger, message )\
    SIMPLELOGGER_ERROR_STDSTR(logger, message )
  #define SIMPLELOGGER_FATAL( logger, message )\
    SIMPLELOGGER_FATAL_STDSTR(logger, message )
#endif /* SIMPLELOGGER_ENABLE_AUTO_MACROS */

#ifdef SIMPLELOGGER_ENABLE_SMALL_MACROS
  #define LOG_TRACE( logger, message )\
    SIMPLELOGGER_TRACE_STDSTR( logger, message )
  #define LOG_DEBUG( logger, message )\
    SIMPLELOGGER_DEBUG_STDSTR( logger, message )
  #define LOG_INFO( logger, message )\
    SIMPLELOGGER_INFO_STDSTR( logger, message )
  #define LOG_WARN( logger, message )\
    SIMPLELOGGER_WARN_STDSTR( logger, message )
  #define LOG_ERROR( logger, message )\
    SIMPLELOGGER_ERROR_STDSTR( logger, message )
  #define LOG_FATAL( logger, message )\
    SIMPLELOGGER_FATAL_STDSTR( logger, message )
#endif /* SIMPLELOGGER_ENABLE_SMALL_MACROS */

#else
/* C macros */

#ifdef SIMPLELOGGER_ENABLE_AUTO_MACROS
  #define SIMPLELOGGER_TRACE( logger, message )\
    SIMPLELOGGER_TRACE_CSTR(logger, message )
  #define SIMPLELOGGER_DEBUG( logger, message )\
    SIMPLELOGGER_DEBUG_CSTR(logger, message )
  #define SIMPLELOGGER_INFO( logger, message )\
    SIMPLELOGGER_INFO_CSTR(logger, message )
  #define SIMPLELOGGER_WARN( logger, message )\
    SIMPLELOGGER_WARN_CSTR(logger, message )
  #define SIMPLELOGGER_ERROR( logger, message )\
    SIMPLELOGGER_ERROR_CSTR(logger, message )
  #define SIMPLELOGGER_FATAL( logger, message )\
    SIMPLELOGGER_FATAL_CSTR(logger, message )
#endif /* SIMPLELOGGER_ENABLE_AUTO_MACROS */

#ifdef SIMPLELOGGER_ENABLE_SMALL_MACROS
  #define LOG_TRACE( logger, message )\
    SIMPLELOGGER_TRACE_CSTR( logger, message )
  #define LOG_DEBUG( logger, message )\
    SIMPLELOGGER_DEBUG_CSTR( logger, message )
  #define LOG_INFO( logger, message )\
    SIMPLELOGGER_INFO_CSTR( logger, message )
  #define LOG_WARN( logger, message )\
    SIMPLELOGGER_WARN_CSTR( logger, message )
  #define LOG_ERROR( logger, message )\
    SIMPLELOGGER_ERROR_CSTR( logger, message )
  #define LOG_FATAL( logger, message )\
    SIMPLELOGGER_FATAL_CSTR( logger, message )
#endif /* SIMPLELOGGER_ENABLE_SMALL_MACROS */

#endif /* __cplusplus */


#endif /* SIMPLELOGGER_H */