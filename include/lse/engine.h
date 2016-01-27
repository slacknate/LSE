#ifndef LSE_ENGINE_H
#define LSE_ENGINE_H

#include <fstream>
#include "io/handler.h"
#include "lse/semaphore.h"
#include "lse/event/table.h"
#include "gui/window/window.h"

namespace LSE {

/*

*/
class Engine : public Thread {
    
    private:
        
        Semaphore event_sem;
        IOHandler handler;
        GLWindow *window; // OpenGL window
        std::streambuf *cout_buff, *cerr_buff;
        std::filebuf message_log, error_log; // logging file handles
        int status; // exit status
        
        void log_banner(const char *const title);
        void create_logs();
        void close_logs();
        
    public:
        
        Engine(int argc, char *argv[]);
        ~Engine();
        
        void attach_window(GLWindow *w);
        int run();
        
        void* execute();
        
        enum {
            
            ID_QUIT = 1,
        };
        
        void on_event(Event *);
        void on_quit(Event *);
};

}

#endif
