# Simple Logger

This is a simple logging implementation.  It is designed to be used from 
either C or C++.

## To Use
Download the .h file and import it into your project.  See the examples
for C and C++ under the examples/ directory for more detailed information.

In general, define any configuration you want with preprocessor macros before 
including the header.  To make things simple, define both 
`SIMPLELOGGER_ENABLE_AUTO_MACROS` and `SIMPLELOGGER_ENABLE_SMALL_MACROS` to 
make your log calls simple.

Here's a quick example on how to use:

```c
/* Make our log calls easy to see */
#define SIMPLELOGGER_ENABLE_SMALL_MACROS
#include "../simplelogger.h"

/* define our global log function pointer */
simplelogger_log_function simplelogger_global_log_function;

void log_function(const char* logger_name, 
    const struct SL_LogLocation* location,
    const enum SL_LogLevel level,
    const char* log_string ){
    /* Log implementation(to stderr, stdout, etc) */
    fprintf( stderr, "%s", log_string );
}

int main( int argc, char** argv ){
    simplelogger_global_log_function = stderr_log_function;

    LOG_INFO( "main_logger", "Set our logger!" );

    return 0;
}
```

Note that this is designed to allow all log functions to be handled through 
some sort of secondary logging facility(such as log4cxx for C++ code).  Alternatively, you can simply implement your own output(such as printing 
directly to `stdout` or to a file.

## Configuring
All configuration is done through preprocessor macros.  Configurations 
availible:

|Macro|What it does|
|-----|------------|
|`SIMPLELOGGER_ENABLE_AUTO_MACROS`|Automatically choose between `SIMPLELOGGER_[level]_STDSTR` and `SIMPLELOGGER_[level]_CSTR` depending on if we are in C or C++.  The call to log now becomes `SIMPLELOGGER_LEVEL` |
|`SIMPLELOGGER_ENABLE_SMALL_MACROS`|Use macros `LOG_[level]` instead of `SIMPLELOGGER_[level]`|
|`SIMPLELOGGER_LOG_FUNCTION_NAME`|Change the name of the global variable to use as the function pointer.  By default, the global variable name is `simplelogger_global_log_function`.  This is useful so that you can namespace your simplelogger call for use in a library.|

### Extra Configuration

Sometimes, you may need to configure the logger not through pre-processor macros.  This may be the case in C++ where you have template functions for your library in a header file, but you still need debug statements at that point.  At that point, the simplest way forward is to define your own custom macro for logging that will call the correct log function pointer for your library.

Let's say that your library(mylib) has a log function pointer of `simplelogger_log_function mylib_function`.  In that case, you could define a macro called `MYLIB_LOG_HEADER` like the follwing(note: what follows is a modification of `SIMPLELOGGER_LOG_CSTR` and `SIMPLELOGGER_DEBUG_STDSTR`):

```
#define MYLIB_LOG_CSTR_HEADER( logger, message, level ) do{\
    if( !mylib_function ) break;\ /* CHANGED THIS LINE */
    struct SL_LogLocation location;\
    location.line_number = __LINE__;\
    location.file = __FILE__;\
    location.function = SIMPLELOGGER_FUNCTION;\
    mylib_function( logger, &location, level, message );\ /* CHANGED THIS LINE */
    } while(0)

#define MYLIB_DEBUG_STDSTR( logger, message ) do{\
    std::stringstream stream;\
    stream << message;\
    MYLIB_LOG_CSTR_HEADER( logger, stream.str().c_str(), SL_DEBUG);\ /* CHANGED THIS LINE */
    } while(0)
```

This allows for still just one header to be installed for the library(`simplelogger_defs.h`).  Simply add the above macros to your library before you want to log in a header file.
