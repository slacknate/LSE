#ifndef LSE_ENGINE_H
#define LSE_ENGINE_H

#include <fstream>
#include "io/handler.h"
#include "gui/window/window.h"

namespace LSE {

/*

*/
class Engine : public Thread {
    
    private:
        
        IOHandler handler;
        GLWindow *window; // OpenGL window
        std::streambuf *cout_buff, *cerr_buff;
        std::filebuf message_log, error_log; // logging file handles
        int status; // exit status
        
        void log_banner(const char *const title);
        void create_log();
        void close_log();

        void* execute();

    public:

        Engine(int argc, char *argv[]);
        ~Engine();
        
        void attach_window(GLWindow *w);
        /*
         * TODO: determine if this ready callback is shitty or not.
         */
        int run(void (*ready)(GLWindow *w));
};

}

#endif
