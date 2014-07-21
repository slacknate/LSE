#include "lse/engine.h"
#include "lse/signals.h"
using namespace LSE;

/*
Engine event table.
*/
EVTMAP(Engine) EngineMap[] = {
    
    EVTFUNC(EVENT_QUIT, Engine::ID_QUIT, Engine::OnQuit),
    EVTFUNC(EVENT_ANY,  ID_ANY,          Engine::OnEvent)
};

/*
Event handler implementation.
*/
EVTIMP(Engine, EngineMap)

/*

*/
Engine::Engine(int argc, char *argv[]) : handler(this) {
    
    window = NULL;
    messgLog = errorLog = NULL;
    run = false;
    status = OK;
    keyFocus = mouseFocus = NULL;
    
    CreateLogs();
    
    ::LOG_LEVEL = LOG_LEVEL_VERBOSE;
    ::InitSignals(this);
}

/*

*/
Engine::~Engine() {
    
    eventList.Clear();
    CloseLogs();
}

/*

*/
void Engine::InitWindow(const char *const windowTitle, unsigned int mask, int width, int height, double angle, double zi, double za) {
    
    window = new GLWindow(windowTitle, mask, width, height, angle, zi, za);
    run = true;
}

/*
Create message and error logs.
*/
void Engine::CreateLogs() {
    
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
        LOG(LOG_LEVEL_ERROR, "Error creating error log files!");
    }
}

/*

*/
void Engine::CloseLogs() {
    
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
void* Engine::Execute() {
    
    while(run) {
        
        event_sem.Wait();
            
        ListNode *node = eventList.PopBack();
        if(node) {
            
            Event *event = (Event *)node->GetData();
            LOG(LOG_LEVEL_VERBOSE, "Popping %s event off queue.", event->name);
            
            switch(event->type) {
                
                case EVENT_KEYBOARD:
                    //keyFocus->Dispatch(this, KEYBOARD, ANY, event);
                    break;
                case EVENT_MOUSE:
                    //mouseFocus->Dispatch(this, MOUSE, ANY, event);
                    break;
                default:
                    break;
            }
            
            delete node;
        }
        else {
            
            LOG(LOG_LEVEL_VERBOSE, "No events in queue to pop.");
        }
    }
    
    return NULL;
}

/*
Run the engine.
We set the engine pointer of 
the GLContext object, and 
begin the context event loop thread.
*/
int Engine::Run() {
    
    if(window != NULL) {
        
        window->SetupIO(&this->handler);
        window->Start();
        
        while(!window->Ready() && StatusCode() != GL_INIT_FAIL); // is there a way to make this semaphore bound?
        
        if(StatusCode() != GL_INIT_FAIL) {
            
            try {

                window->GLInit(); 
                ::GLInit();
                ::InitScene(this->window);           
                this->Start();
            
                while(run)
                    window->Render();
                
                this->Join();
            }
            catch(Exception &e) {
                
                LOG(LOG_LEVEL_ERROR, e.what());
            }
        }
        else {
            
            if(GLVersion() < MIN_GL_VERSION)
                LOG(LOG_LEVEL_ERROR, "OpenGL version too low.");
        
            if(MaxGLVertAttrib() < GL_MIN_VERT_ATTRIB)
                LOG(LOG_LEVEL_ERROR, "Too few bindable vertex attributes available.");
                
            if(MaxFBOColorAttachments() < GL_MIN_COLOR_ATTACH)
                LOG(LOG_LEVEL_ERROR, "Too few bindable Frame buffer object color attachmentments available.");
        }
        
        window->Join();
    }
    else {
        
        LOG(LOG_LEVEL_ERROR, "Cannot render NULL OpenGL window.");
    }
    
    return status;
}

/*
Post an event to the event queue.
*/
bool Engine::OnEvent(Object *, unsigned int, unsigned int, void *ptr) {
    
    if(ptr != NULL) {
        
        Event *event = (Event *)ptr;
        LOG(LOG_LEVEL_VERBOSE, "Adding %s event to queue.", event->name);
        eventList.PushFront(event);
        
        event_sem.Post();
    }
    else {
        
        LOG(LOG_LEVEL_VERBOSE, "NULL event received.");
    }
    
    return ptr != NULL;
}

/*
Quit the application.
*/
bool Engine::OnQuit(Object *, unsigned int, unsigned int, void *ptr) {
    
    LOG(LOG_LEVEL_DEBUG, "Received quit event. Stopping event loop.");
    this->run = false;
    
    Event *event = (Event *)ptr;
    LOG(LOG_LEVEL_DEBUG, "Sending quit event to event queue.");
    eventList.PushFront(event);
        
    event_sem.Post();
    return true;
}
