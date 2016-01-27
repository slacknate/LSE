#include <iostream>
#include "lse/engine.h"
#include "lse/globals.h"
#include "lse/signals.h"
#include "lse/exception.h"
#include "util/time.h"
#include "util/memory.h"
using namespace LSE;


/*

*/
Engine::Engine(int argc, char *argv[]) : handler(this) {

    this->window = NULL;
    this->status = OK;

    this->create_logs();

    LSE::InitSignals(this);
}


/*

*/
Engine::~Engine() {
    
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
    
    //std::cout.rdbuf(this->cout_buff);
    //std::cerr.rdbuf(this->cerr_buff);
    
    //this->message_log.close();
    //this->error_log.close();
}


/*

*/
void* Engine::execute() {
    
    logger.debug("Event queue thread started.");
    
    while(this->running) {

        this->event_sem.wait();

//        Event *event = ::pop_event();
//
//        if(event == nullptr) {
//
//            logger.verbose("No events in queue.");
//        }
//        else {
//
//            logger.verbose("Handling %s event.", event->name);
//
//            switch(event->type) {
//
//                case EVENT_KEYBOARD:
//                    if(this->key_focus)
//                        this->key_focus->dispatch(this, EVENT_KEYBOARD, ID_ANY, event);
//                    break;
//                case EVENT_MOUSE:
//                    if(this->mouse_focus)
//                        this->mouse_focus->dispatch(this, EVENT_MOUSE, ID_ANY, event);
//                    break;
//                default:
//                    break;
//            }
//
//            delete event;
//        }
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

            try {

                this->window->setup_gl();

                while(this->running)
                    this->window->render();
            }
            catch(std::exception &e) {

                logger.error(e.what());
            }

            this->window->teardown_gl();
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
void Engine::on_event(Event *event) {
    
    if(event != NULL) {
        
        logger.verbose("Adding %s event to queue.", event->name);

        this->event_sem.post();
    }
    else {
        
        logger.verbose("NULL event received.");
    }
}


/*
Quit the application.
*/
void Engine::on_quit(Event *) {
    
    logger.debug("Received quit event. Stopping event loop.");
    this->running = false;
    
    this->event_sem.post();
}
