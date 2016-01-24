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

    EngineTableEntry(EVENT_QUIT, Engine::ID_QUIT, &Engine::on_quit),
    EngineTableEntry(EVENT_ANY, ID_ANY, &Engine::on_event)
});


/*

*/
Engine::Engine(int argc, char *argv[]) : handler(this) {

    this->window = NULL;
    this->status = OK;
    this->key_focus = this->mouse_focus = NULL;
    
    this->create_logs();
    this->register_table(&Engine::table);

    LSE::InitSignals(this);
}


/*

*/
Engine::~Engine() {
    
    this->event_list.Clear();
    this->close_logs();
}


/*

*/
void Engine::attach_window(GLWindow *w) {
    
    this->window = w;
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

    logger.start();
    
    char *date_and_day_str = LSE::calloc<char>(DAY_DATE_STR_LENGTH);
    LSE::get_day_and_date(date_and_day_str);
    
    char *message_log_name = LSE::calloc<char>(DAY_DATE_STR_LENGTH + 9);
    strncpy(message_log_name, date_and_day_str, DAY_DATE_STR_LENGTH);
    strncat(message_log_name, "_cout.log", 9);
    
    for(unsigned int i = 0; i < DAY_DATE_STR_LENGTH + 9; ++i) {
        
        if(message_log_name[i] == ' ')
            message_log_name[i] = '_';
    }
        
    //this->message_log.open(message_log_name, std::fstream::out | std::fstream::app);
    //this->cout_buff = std::cout.rdbuf(&this->message_log);
    
    char *error_log_name = LSE::calloc<char>(DAY_DATE_STR_LENGTH + 9);
    strncpy(error_log_name, date_and_day_str, DAY_DATE_STR_LENGTH);
    strncat(error_log_name, "_cerr.log", 9);
    
    for(unsigned int i = 0; i < DAY_DATE_STR_LENGTH + 9; ++i) {
        
        if(error_log_name[i] == ' ')
            error_log_name[i] = '_';
    }
        
    //this->error_log.open(error_log_name, std::fstream::out | std::fstream::app);
    //this->cerr_buff = std::cerr.rdbuf(&this->error_log);
    
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

    logger.join();
    
    std::cout.rdbuf(this->cout_buff);
    std::cerr.rdbuf(this->cerr_buff);
    
    this->message_log.close();
    this->error_log.close();
}


/*

*/
void* Engine::execute() {
    
    logger.debug("Event queue thread started.");
    
    while(this->running) {

        this->event_sem.wait();

        ListNode *node = this->event_list.PopBack();
        if(node) {
            
            Event *event = (Event *)node->GetData();
            logger.verbose("Popping %s event off queue.", event->name);
            
            switch(event->type) {
                
                case EVENT_KEYBOARD:
                    if(this->key_focus)
                        this->key_focus->dispatch(this, EVENT_KEYBOARD, ID_ANY, event);
                    break;
                case EVENT_MOUSE:
                    if(this->mouse_focus)
                        this->mouse_focus->dispatch(this, EVENT_MOUSE, ID_ANY, event);
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
int Engine::run() {
    
    try {

        this->start();

        if(this->window != NULL) {

            this->window->setup_io(&this->handler);
            this->window->start();
            this->window->wait_for_ready();

            if(StatusCode() != GL_INIT_FAIL) {

                /*this->window->setup_gl();

                while(this->running)
                    this->window->render();

                this->window->teardown_gl();*/
            }
            else {

                if(gl_manager.gl_version < MIN_GL_VERSION)
                    logger.error("OpenGL version too low.");

                if(gl_manager.max_vertex_attributes < GL_MIN_VERT_ATTRIB)
                    logger.error("Too few bindable vertex attributes available.");

                if(gl_manager.max_fbo_color_attachments < GL_MIN_COLOR_ATTACH)
                    logger.error("Too few bindable Frame buffer object color attachmentments available.");
            }

            this->window->join();
        }
        else {

            logger.error("An OpenGL window was never associated with this instance of LSE::Engine.");
        }

        this->join();
    }
    catch(std::exception &e) {

        logger.error(e.what());
    }
    
    return this->status;
}


/*
Post an event to the event queue.
*/
int Engine::on_event(Object *, unsigned int, unsigned int, void *ptr) {
    
    if(ptr != NULL) {
        
        Event *event = (Event *)ptr;
        logger.verbose("Adding %s event to queue.", event->name);
        this->event_list.PushFront(event);

        this->event_sem.post();
    }
    else {
        
        logger.verbose("NULL event received.");
    }
    
    return ptr != NULL;
}


/*
Quit the application.
*/
int Engine::on_quit(Object *, unsigned int, unsigned int, void *ptr) {
    
    logger.debug("Received quit event. Stopping event loop.");
    this->running = false;
    
    Event *event = (Event *)ptr;
    logger.debug("Sending quit event to event queue.");
    this->event_list.PushFront(event);

    this->event_sem.post();
    return true;
}
