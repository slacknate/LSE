#ifndef LSE_ENGINE_H
#define LSE_ENGINE_H

#include "io/handler.h"
#include "lse/semaphore.h"
#include "gui/window/window.h"

/*
Callback typedefs.
*/
typedef void (*LSE_GLInitCB)();
typedef void (*LSE_SceneCB)(LSE_GLWindow *);

/*

*/
class LSE_Engine : public LSE_Thread {
    
    // event map type and handler declaration
    LSE_DECLARE(LSE_Engine)
    
    private:
        
        LSE_GLInitCB glCB; // 
        LSE_SceneCB scCB; //
        LSE_List eventList; // 
        LSE_Object *keyFocus, *mouseFocus;
        LSE_Semaphore event_sem;
        LSE_IOHandler handler;
        LSE_GLWindow *window; // OpenGL window
        FILE *messgLog, *errorLog; // logging file handles
        bool run; // keep the engine running
        int status; // exit status
        
        void CreateLogs();
        void CloseLogs();
        
    public:
        
        LSE_Engine(LSE_GLInitCB g, LSE_SceneCB s);
        ~LSE_Engine();
        
        void InitWindow(const char *const windowTitle, unsigned int m, int w, int h, double angle, double zi, double za);
        int Run();
        
        void* Execute();
        
        enum {
            
            ID_QUIT = 1,
            ID_EVENT
        };
        
        bool OnEvent(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr);
        bool OnQuit(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr);
};

#endif
