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

```
/* Make our log calls easy to see */
#define SIMPLELOGGER_ENABLE_SMALL_MACROS
#include "../simplelogger.h"

/* define our global log function pointer */
simplelogger_log_function simplelogger_global_log_function;

void log_function(const char* logger_name, 
    const struct SL_LogLocation* location,
    const enum SL_LogLevel level,
    const char* log_string ){
    /* Log implementation(to stderr, stdout, etc)
}

int main( int argc, char** argv ){
    simplelogger_global_log_function = stderr_log_function;

    LOG_INFO( "main_logger", "Set our logger!" );

    return 0;
}
```

Note that this is designed to allow all log functions to be handled through 
some sort of secondary logging facility(such as log4cxx for C++ code).  
Alternatively, you can simply implement your own output(such as printing 
directly to `stdout` or to a file.

## Configuring
All configuration is done through preprocessor macros.  Configurations 
availible:

|Macro|What it does|
|-----|------------|
|`SIMPLELOGGER_ENABLE_AUTO_MACROS`|Automatically choose between `SIMPLELOGGER_[level]_STDSTR` and `SIMPLELOGGER_[level]_CSTR` depending on if we are in C or C++.  The call to log now becomes `SIMPLELOGGER_LEVEL` |
|`SIMPLELOGGER_ENABLE_SMALL_MACROS`|Use macros `LOG_[level]` instead of `SIMPLELOGGER_[level]`|
