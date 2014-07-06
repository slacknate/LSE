#include "lse/exception.h"
#include "lse/defs.h"
using namespace LSE;

void call_safe() {
    
    try {
        
        
    }
    catch(const std::bad_alloc &ba) { 
        
        throw Exception(__FILE__, __LINE__, BAD_ALLOC);
    }
    catch(const std::bad_cast &bc) { 
    
        throw Exception(__FILE__, __LINE__, BAD_CAST);
    }
    catch(const std::bad_typeid &bt) { 
    
        throw Exception(__FILE__, __LINE__, BAD_TYPE_ID);
    }
    catch(const std::bad_exception &be) { 
    
        throw Exception(__FILE__, __LINE__, BAD_EXCEPTION);
    }
    catch(const std::ios_base::failure &iof) { 
    
        throw Exception(__FILE__, __LINE__, IOS_FAIL);
    }
    catch(const std::runtime_error &re) { 
    
        throw Exception(__FILE__, __LINE__, RUNTIME_ERR);
    }
    catch(const std::logic_error &le) { 
    
        throw Exception(__FILE__, __LINE__, LOGIC_ERR);
    }
}

/*
Create an exception, with a corresponding error message.
*/
Exception::Exception(const char *f, int l, int c) throw() {
    
    memset(output, 0, ERROR_BUFFER_SIZE + 1);
    fileName = f;
    lineNumber = l;
    errCode = c;
}

/*
Return the error message.
*/
const char* Exception::what() const throw() {
    
    snprintf((char *)output, ERROR_BUFFER_SIZE, "An exception was thrown in \"%s\" at line %d, code %s: %s", fileName, lineNumber, StatusID(errCode), StatusString(errCode));
    return output;
}

/*
Return the error code.
*/
const int Exception::code() const throw() {
    
    return errCode;
}
