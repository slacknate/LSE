#ifndef LSE_ENGINE_H
#define LSE_ENGINE_H

#include "io/handler.h"
#include "lse/semaphore.h"
#include "gui/window/window.h"

namespace LSE {

/*

*/
class Engine : public Thread {
    
    private:
        
        static const EventTable<Engine> table;
        
        List eventList; // 
        Object *keyFocus, *mouseFocus;
        Semaphore event_sem;
        IOHandler handler;
        GLWindow *window; // OpenGL window
        FILE *messgLog, *errorLog; // logging file handles
        bool run; // keep the engine running
        int status; // exit status
        
        void CreateLogs();
        void CloseLogs();
        
    public:
        
        Engine(int argc, char *argv[]);
        ~Engine();
        
        void InitWindow(const char *const windowTitle, unsigned int m, int w, int h, double angle, double zi, double za);
        int Run();
        
        void* Execute();
        
        enum {
            
            ID_QUIT = 1,
            ID_EVENT
        };
        
        int OnEvent(Object *sender, unsigned int type, unsigned int id, void *ptr);
        int OnQuit(Object *sender, unsigned int type, unsigned int id, void *ptr);
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
