#include "lse/exception.h"
#include "lse/defs.h"
using namespace LSE;

void call_safe() {
    
    try {
        
        
    }
    catch(const std::bad_alloc &ba) { 
        
        throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_ALLOC);
    }
    catch(const std::bad_cast &bc) { 
    
        throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_CAST);
    }
    catch(const std::bad_typeid &bt) { 
    
        throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_TYPE_ID);
    }
    catch(const std::bad_exception &be) { 
    
        throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_EXCEPTION);
    }
    catch(const std::ios_base::failure &iof) { 
    
        throw LSE_Exception(__FILE__, __LINE__, LSE_IOS_FAIL);
    }
    catch(const std::runtime_error &re) { 
    
        throw LSE_Exception(__FILE__, __LINE__, LSE_RUNTIME_ERR);
    }
    catch(const std::logic_error &le) { 
    
        throw LSE_Exception(__FILE__, __LINE__, LSE_LOGIC_ERR);
    }
}

/*
Create an exception, with a corresponding error message.
*/
LSE_Exception::LSE_Exception(const char *f, int l, int c) throw() {
    
    memset(output, 0, ERROR_BUFFER_SIZE + 1);
    fileName = f;
    lineNumber = l;
    errCode = c;
}

/*
Return the error message.
*/
const char* LSE_Exception::what() const throw() {
    
    snprintf((char *)output, ERROR_BUFFER_SIZE, "An exception was thrown in \"%s\" at line %d, code %s: %s", fileName, lineNumber, LSE_ErrorIDString(errCode), LSE_ErrorString(errCode));
    return output;
}

/*
Return the error code.
*/
const int LSE_Exception::code() const throw() {
    
    return errCode;
}
