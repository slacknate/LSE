#ifndef LSE_SEM_H
#define LSE_SEM_H

#include <pthread.h>
#include <semaphore.h>

namespace LSE {

/*

*/
class LSE_Semaphore {
    
    private:
        
        sem_t semaphore; // semaphore structure
        bool initialized; // state of the semaphore. true when sem_init succeeds
        
    public:
        
        LSE_Semaphore(int initial=0, int shared=0);
        ~LSE_Semaphore();
        
        void Wait();
        void TryWait();
        void Post();
        int Value();
};

}

#endif

