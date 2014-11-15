#ifndef LSE_ENGINE_H
#define LSE_ENGINE_H

#include <fstream>
#include "io/handler.h"
#include "lse/semaphore.h"
#include "gui/window/window.h"

namespace LSE {

/*

*/
class Engine : public Thread {
    
    private:
        
        static const EventTable<Engine> table;
        
        List event_list; //
        Object *key_focus, *mouse_focus;
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
        
        void init_window(const char *const title, unsigned int m, int w, int h, double angle, double zi, double za);
        int run();
        
        void* execute();
        
        enum {
            
            ID_QUIT = 1,
        };
        
        int on_event(Object *sender, unsigned int type, unsigned int id, void *ptr);
        int on_quit(Object *sender, unsigned int type, unsigned int id, void *ptr);
};

typedef EventTable<Engine> EngineEventTable;
typedef EventTableEntry<Engine> EngineTableEntry;

}

/*
User defined initialization functions.
*/
void GLInit();
void InitScene(LSE::GLWindow *window);

#endif
