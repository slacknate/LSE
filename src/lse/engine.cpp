#include "lse/engine.h"
#include "lse/signals.h"

/*
LSE_Engine event table.
*/
LSE_EVTMAP(LSE_Engine) EngineMap[] = {
    
    LSE_EVTFUNC(LSE_ANY, LSE_ANY, LSE_Engine::OnEvent),
    LSE_EVTFUNC(LSE_QUIT, LSE_Engine::ID_QUIT, LSE_Engine::OnQuit)
};

/*
Event handler implementation.
*/
LSE_EVTIMP(LSE_Engine, EngineMap)

/*
Engine-wide variables.
*/
LSE_LogLevel LSE_Engine::log_level = LOG_LEVEL_DEBUG;

/*

*/
LSE_Engine::LSE_Engine(int argc, char *argv[]) : handler(this) {
    
    window = NULL;
    messgLog = errorLog = NULL;
    run = false;
    status = LSE_OK;
    keyFocus = mouseFocus = NULL;
    
//    CreateLogs();
    
    LSE_Signal::LSE_InitSignals(this);
}

/*

*/
LSE_Engine::~LSE_Engine() {
    
    eventList.Clear();
    CloseLogs();
}

/*

*/
void LSE_Engine::InitWindow(const char *const windowTitle, unsigned int mask, int width, int height, double angle, double zi, double za) {
    
    window = new LSE_GLWindow(windowTitle, mask, width, height, angle, zi, za);
    run = true;
}

/*
Create message and error logs.
*/
void LSE_Engine::CreateLogs() {
    
    time_t t;
    time(&t);
    char *time = ctime(&t);
    
    int len = strlen(time) + 3;
    
    char *messgLogFileName = new (std::nothrow) char [len + 1];
    char *errorLogFileName = new (std::nothrow) char [len + 5];
    
    if(messgLogFileName != NULL && errorLogFileName != NULL) {
        
        strncpy(messgLogFileName, time, 11);
        strncat(messgLogFileName, &time[20], 4);
        strncat(messgLogFileName, ".log", 4);
    
        for(int i = 0; i < len; ++i) {
        
            if(messgLogFileName[i] == ' ')
                messgLogFileName[i] = '_';
        }
    
        messgLog = freopen(messgLogFileName, "a", stdout);
        
        strncpy(errorLogFileName, time, 11);
        strncat(errorLogFileName, &time[20], 4);
        strncat(errorLogFileName, "_err.log", 8);
    
        for(int i = 0; i < len; ++i) {
        
            if(errorLogFileName[i] == ' ')
                errorLogFileName[i] = '_';
        }
    
        errorLog = freopen(errorLogFileName, "a", stderr);
    
        delete[] messgLogFileName;
        delete[] errorLogFileName;
        
        fprintf(stdout, "--------------------");
        fprintf(stderr, "--------------------");
        
        char *timeStr = new (std::nothrow) char [9];
        if(timeStr != NULL) {
        
            memset(timeStr, 0, 9);
        
            time_t t;
            ::time(&t);
            char *static_time = ctime(&t);
    
            strncpy(timeStr, &static_time[11], 8);
        
            fprintf(stdout, " Log Open:  [%s] ", timeStr);
            fprintf(stderr, " Log Open:  [%s] ", timeStr);
        }
        
        fprintf(stdout, "--------------------\n\n");
        fprintf(stderr, "--------------------\n\n");
    }
    else {
        
        // need to write this to disk....
        LSE_ERROR_LOG("Error creating error log files!");
    }
}

/*

*/
void LSE_Engine::CloseLogs() {
    
    fprintf(stdout, "\n--------------------");
    fprintf(stderr, "\n--------------------");
        
    char *timeStr = new (std::nothrow) char [9];
    if(timeStr != NULL) {
        
        memset(timeStr, 0, 9);
        
        time_t t;
        ::time(&t);
        char *static_time = ctime(&t);
    
        strncpy(timeStr, &static_time[11], 8);
        
        fprintf(stdout, " Log Close: [%s] ", timeStr);
        fprintf(stderr, " Log Close: [%s] ", timeStr);
    }
        
    fprintf(stdout, "--------------------\n\n");
    fprintf(stderr, "--------------------\n\n");
    
    if(messgLog != NULL)
        fclose(messgLog);
        
    if(errorLog != NULL)    
        fclose(errorLog);
}

/*

*/
void* LSE_Engine::Execute() {
    
    while(run) {
        
        event_sem.Wait();
            
        LSE_ListNode *node = eventList.PopBack();
        LSE_Event *event = (LSE_Event *)node->GetData();
            
        switch(event->type) {
                
            case LSE_KEYBOARD:
                //keyFocus->Dispatch(this, LSE_KEYBOARD, LSE_ANY, event);
                break;
            case LSE_MOUSE:
                break;
            default:
                break;
        }
            
        delete event;
        delete node;
    }
    
    return NULL;
}

/*
Run the engine.
We set the engine pointer of 
the LSE_GLContext object, and 
begin the context event loop thread.
*/
int LSE_Engine::Run() {
    
    if(window != NULL) {
        
        window->SetupIO(&this->handler);
        window->Start();
        
        while(!window->Ready() && LSE_STATUS != LSE_GL_INIT_FAIL);
        
        if(LSE_STATUS != LSE_GL_INIT_FAIL) {
            
            window->GLInit(); 
            ::GLInit();
            ::InitScene(this->window);           
            this->Start();
            
            while(run)
                window->Render();
                
            this->Join();
        }
        else {
            
            if(LSE_GL_VERSION < LSE_MIN_GL_VERSION)
                LSE_ERROR_LOG("OpenGL version too low.");
        
            if(LSE_GL_MAX_VERT_ATTRIB < LSE_GL_MIN_VERT_ATTRIB)
                LSE_ERROR_LOG("Too few bindable vertex attributes available.");
                
            if(LSE_GL_MAX_COLOR_ATTACH < LSE_GL_MIN_COLOR_ATTACH)
                LSE_ERROR_LOG("Too few bindable Frame buffer object color attachmentments available.");
        }
        
        window->Join();
    }
    else {
        
        LSE_ERROR_LOG("Cannot render NULL OpenGL window.");
    }
    
    return status;
}

/*
Post an event to the event queue.
*/
bool LSE_Engine::OnEvent(LSE_Object *, unsigned int, unsigned int, void *ptr) {
    
    if(ptr != NULL) {
        
        LSE_Event *event = (LSE_Event *)ptr;
        eventList.PushFront(event);
        
        event_sem.Post();
    }
    
    return ptr != NULL;
}

/*
Quit the application.
*/
bool LSE_Engine::OnQuit(LSE_Object *, unsigned int, unsigned int, void *) {
    
    run = false;
    return true;
}
