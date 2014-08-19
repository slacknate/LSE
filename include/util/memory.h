#ifndef LSE_MEMORY_H
#define LSE_MEMORY_H

#include "lse/defs.h"
#include "lse/exception.h"

namespace LSE {

/*
Allocate a block of memory and initialze to zero.
Throw an exception in the event of allocation failure.
This should be used for basic types and structs.
*/
template <class T> T* calloc(unsigned int size=1) {
    
    T *t_ptr = new (std::nothrow) T [size];
    if(t_ptr != nullptr) {
        
        memset(t_ptr, 0, sizeof(T) * size);
    }
    else{
        
        throw Exception("NOT_REAL", 0, BAD_ALLOC); // FIXME: get real file and line
    }
    
    return t_ptr;
}


/*
Allocate a block of memory.
Throw an exception in the event of allocation failure.
This should be used for classes. Note that this will only
call a default constructor; if a more specialized constructor
is required, use template specialization to override this function.
*/
template <class T> T* malloc(unsigned int size=1, ...) {
    
    T *t_ptr = new (std::nothrow) T [size];
    if(t_ptr == nullptr) {
        
        throw Exception("NOT_REAL", 0, BAD_ALLOC); // FIXME: get real file and line
    }
    
    return t_ptr;
}

}

#endif
