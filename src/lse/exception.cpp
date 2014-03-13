#include "lse/exception.h"
#include "lse/defs.h"

/*
Create an exception, with a corresponding error message.
*/
LSE_Exception::LSE_Exception(const char *f, int l, int c) throw() {
    
    memset(output, 0, BUFFER_SIZE);
    fileName = f;
    lineNumber = l;
    errCode = c;
}

/*
Return our error message.
*/
const char* LSE_Exception::what() const throw() {
    
    snprintf((char*)output, BUFFER_SIZE, "An exception was thrown in \"%s\" at line %d, code %s: %s", fileName, lineNumber, LSE_ErrorIDString(errCode), LSE_ErrorString(errCode));
    return output;
}

/*
Return the error code.
*/
const int LSE_Exception::code() const throw() {
    
    return errCode;
}
