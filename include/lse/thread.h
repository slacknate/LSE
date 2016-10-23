#ifndef LSE_THREAD_H
#define LSE_THREAD_H

#include <pthread.h>
#include "lse/object.h"

namespace LSE {

/*
Thread class used to create objects
which can run an additional thread in the
background but still respond to events.
*/
class Thread : public Object {

    private:

        virtual void* execute()=0;

    protected:

        pthread_t thread; // event loop thread ID
        bool running; // thread execution state

        static void* thread_method(void *arg);

    public:

        Thread();

        bool start();
        bool detach();
        bool join();

        void on_quit(Event *);

        /*
         * FIXME: implement in LSE::Object.
         */
        void consume(Event *event, EventHandlerBase *event_handler) {

            this->consume_as<Thread>(event, event_handler);
        }
};

}

#endif
