#include <iostream>
#include "lse/engine.h"
#include "lse/globals.h"
#include "lse/signals.h"
#include "lse/exception.h"
#include "util/time.h"
#include "util/memory.h"
using namespace LSE;


/*
Engine event table.
*/
const EngineEventTable Engine::table = EngineEventTable({
    
    EngineTableEntry(EVENT_QUIT, Engine::ID_QUIT, &Engine::OnQuit),
    EngineTableEntry(EVENT_ANY,  ID_ANY,          &Engine::OnEvent)
});


/*

*/
Engine::Engine(int argc, char *argv[]) : handler(this) {
    
    window = NULL;
    run = false;
    status = OK;
    keyFocus = mouseFocus = NULL;
    
    this->create_logs();
    
    LSE::InitSignals(this);
    
    this->register_table(&Engine::table);
}


/*

*/
Engine::~Engine() {
    
    this->eventList.Clear();
    this->close_logs();
}


/*

*/
void Engine::InitWindow(const char *const windowTitle, unsigned int mask, int width, int height, double angle, double zi, double za) {
    
    window = new GLWindow(windowTitle, mask, width, height, angle, zi, za);
    run = true;
}


/*

*/
void Engine::log_banner(const char *const title) {
    
    std::cout << "\n--------------------";
    std::cerr << "\n--------------------";
    
    char *time_str = LSE::calloc<char>(TIME_STR_LENGTH);
    LSE::get_local_time(time_str);
    
    std::cout << " Log " << title << ": [" << time_str << "] ";
    std::cerr << " Log " << title << ": [" << time_str << "] ";
    
    std::cout << "--------------------\n\n";
    std::cerr << "--------------------\n\n";
    
    delete[] time_str;
}


/*
Open a file on disk for logging std::cout and std::cerr.
Preserve the original stream buffer for both streams.
*/
void Engine::create_logs() {
    
    logger.Start();
    
    char *date_and_day_str = LSE::calloc<char>(DAY_DATE_STR_LENGTH);
    LSE::get_day_and_date(date_and_day_str);
    
    char *message_log_name = LSE::calloc<char>(DAY_DATE_STR_LENGTH + 9);
    strncpy(message_log_name, date_and_day_str, DAY_DATE_STR_LENGTH);
    strncat(message_log_name, "_cout.log", 9);
    
    for(int i = 0; i < DAY_DATE_STR_LENGTH + 9; ++i) {
        
        if(message_log_name[i] == ' ')
            message_log_name[i] = '_';
    }
        
    this->message_log.open(message_log_name, std::fstream::out | std::fstream::app);
    this->cout_buff = std::cout.rdbuf(&this->message_log);
    
    char *error_log_name = LSE::calloc<char>(DAY_DATE_STR_LENGTH + 9);
    strncpy(error_log_name, date_and_day_str, DAY_DATE_STR_LENGTH);
    strncat(error_log_name, "_cerr.log", 9);
    
    for(int i = 0; i < DAY_DATE_STR_LENGTH + 9; ++i) {
        
        if(error_log_name[i] == ' ')
            error_log_name[i] = '_';
    }
        
    this->error_log.open(error_log_name, std::fstream::out | std::fstream::app);
    this->cerr_buff = std::cerr.rdbuf(&this->error_log);
    
    this->log_banner("Open");
    
    delete[] message_log_name;
    delete[] error_log_name;
    delete[] date_and_day_str;
}


/*
Close the log files, reassociate std::cout and std::cerr to
their original stream buffers.
*/
void Engine::close_logs() {
    
    this->log_banner("Close");
    
    logger.Join();
    
    std::cout.rdbuf(this->cout_buff);
    std::cerr.rdbuf(this->cerr_buff);
    
    this->message_log.close();
    this->error_log.close();
}


/*

*/
void* Engine::Execute() {
    
    logger.debug("Event queue thread started.");
    
    while(run) {

        event_sem.wait();
        
        ListNode *node = eventList.PopBack();
        if(node) {
            
            Event *event = (Event *)node->GetData();
            logger.verbose("Popping %s event off queue.", event->name);
            
            switch(event->type) {
                
                case EVENT_KEYBOARD:
                    if(keyFocus)
                        keyFocus->Dispatch(this, EVENT_KEYBOARD, ID_ANY, event);
                    break;
                case EVENT_MOUSE:
                    if(mouseFocus)
                        mouseFocus->Dispatch(this, EVENT_MOUSE, ID_ANY, event);
                    break;
                default:
                    break;
            }
            
            //delete node;
        }
        else {
            
            logger.verbose("No events in queue to pop.");
        }
    }
    
    logger.debug("Event queue thread terminating.");
    
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
        window->wait_for_ready();

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
                
                logger.error(e.what());
            }
        }
        else {
            
            if(GLVersion() < MIN_GL_VERSION)
                logger.error("OpenGL version too low.");
        
            if(MaxGLVertAttrib() < GL_MIN_VERT_ATTRIB)
                logger.error("Too few bindable vertex attributes available.");
                
            if(MaxFBOColorAttachments() < GL_MIN_COLOR_ATTACH)
                logger.error("Too few bindable Frame buffer object color attachmentments available.");
        }
        
        window->Join();
    }
    else {
        
        logger.error("Cannot render NULL OpenGL window.");
    }
    
    return status;
}


/*
Post an event to the event queue.
*/
int Engine::OnEvent(Object *, unsigned int, unsigned int, void *ptr) {
    
    if(ptr != NULL) {
        
        Event *event = (Event *)ptr;
        logger.verbose("Adding %s event to queue.", event->name);
        eventList.PushFront(event);

        event_sem.post();
    }
    else {
        
        logger.verbose("NULL event received.");
    }
    
    return ptr != NULL;
}


/*
Quit the application.
*/
int Engine::OnQuit(Object *, unsigned int, unsigned int, void *ptr) {
    
    logger.debug("Received quit event. Stopping event loop.");
    this->run = false;
    
    Event *event = (Event *)ptr;
    logger.debug("Sending quit event to event queue.");
    eventList.PushFront(event);

    event_sem.post();
    return true;
}
