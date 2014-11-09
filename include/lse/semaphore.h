#ifndef LSE_SEM_H
#define LSE_SEM_H

#include <pthread.h>
#include <semaphore.h>

namespace LSE {

/*

*/
class Semaphore {
    
    private:
        
        sem_t semaphore; // semaphore structure

    public:
        
        Semaphore(int initial=0, int shared=0);
        ~Semaphore();
        
        void Wait();
        void TryWait();
        void Post();
        int Value();
};

}

#endif

