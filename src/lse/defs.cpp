#include "lse/defs.h"
#if defined(_WIN32) || defined(_WIN64) // all windows variants
#include <windows.h>
#elif defined(__unix__) && !defined(__APPLE__) // all unix variants, non-mac
// put nix include here
#elif defined(__APPLE__) && !defined(__MACH__) // mac osx, non-ios
// put mac include here
#endif
using namespace LSE;

/*

*/
static const char *const STATUS_ID_STRINGS[] = {
    
    "OK",
    "GL_INIT_FAIL",
    "GL_PROG_FAIL",
    "BAD_ALLOC",
    "BAD_CAST",
    "BAD_EXCEPTION",
    "BAD_TYPE_ID",
    "IOS_FAIL",
    "RUNTIME_ERR",
    "LOGIC_ERR",
    "WIN_REG_FAIL",
    "WIN_CREATE_FAIL",
    "GL_CON_FAIL",
    "IO_SETUP_FAIL",
    "STAT_LAST"
};

/*
LSE Status strings.
*/
static const char *const STATUS_STRINGS[] = {
    
    "No errors. ",
    "OpenGL failed to initialize. ",
    "OpenGL shader program failed to verify. ",
    "Bad memory allocation. ",
    "Bad dynamic cast. ",
    "Unhandled exceptions. ",
    "NULL pointer passed to typeid(). ",
    "Stream error. ",
    "Logic error. ",
    "Runtime error. ",
    "Failed to register window. ",
    "Failed to create window. ",
    "Failed to obtain an OpenGL context. ",
    "Failed to setup IO handlers. ",
    "Unknown error code. "
};

namespace LSE {

/*
LSE Error status.
*/
static int error_status = OK;


/*

*/
int StatusCode(int code) {
    
    if(code >= OK && code < STAT_LAST)
        error_status = code;
        
    return error_status;
}

/*
Platform specific error code fetcher.

TODO: make this less sloochy?
*/
int ExtendedStatusCode() {
#if defined(_WIN32) || defined(_WIN64) // all windows variants
    return GetLastError();
#elif defined(__unix__) && !defined(__APPLE__) // all unix variants, non-mac
    return 0; // FIXME
#elif defined(__APPLE__) && !defined(__MACH__) // mac osx, non-ios
    return 0; // FIXME
#endif
}

/*

*/
const char* StatusString(int code) {
    
    if(code >= OK && code < STAT_LAST)
        return STATUS_STRINGS[code];
        
    else
        return STATUS_STRINGS[error_status];
}

/*

*/
const char* StatusID(int code) {
    
    if(code >= OK && code < STAT_LAST)
        return STATUS_ID_STRINGS[code];
        
    else
        return STATUS_ID_STRINGS[error_status];
}

}
