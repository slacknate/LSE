#include <csignal>
#include "lse/signals.h"
#include "lse/defs.h"
using namespace LSE;

static Engine *engine = NULL;

void AbortHandler(int code) {
    
    LOG(LOG_LEVEL_ERROR, "Abort signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    exit(code);
}

void FPEHandler(int code) {
    
    LOG(LOG_LEVEL_ERROR, "Floating Point Exception signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    exit(code);
}

void IIHandler(int code) {
    
    LOG(LOG_LEVEL_ERROR, "Illegal Instruction signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    system("pause");
    exit(code);
}

void InterruptHandler(int code) {
    
    LOG(LOG_LEVEL_ERROR, "Interrupt signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    system("pause");
    exit(code);
}

void SegfaultHandler(int code) {
    
    LOG(LOG_LEVEL_ERROR, "Segfault signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    system("pause");
    exit(code);
}

void TerminateHandler(int code) {
    
    LOG(LOG_LEVEL_ERROR, "Terminate signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    system("pause");
    exit(code);
}

namespace LSE {

void InitSignals(Engine *e) {
    
    engine = e;
    
    if(signal(SIGABRT, &AbortHandler) == SIG_ERR)
        ERRNO("Failed to initialize Abort Signal handler");
    
    if(signal(SIGFPE, &FPEHandler) == SIG_ERR)
        ERRNO("Failed to initialize FPR Signal handler");
    
    if(signal(SIGILL, &IIHandler) == SIG_ERR)
        ERRNO("Failed to initialize II Signal handler");
    
    if(signal(SIGINT, &InterruptHandler) == SIG_ERR)
        ERRNO("Failed to initialize Interrupt Signal handler");
    
    if(signal(SIGSEGV, &SegfaultHandler) == SIG_ERR)
        ERRNO("Failed to initialize Segfault Signal handler");
    
    if(signal(SIGTERM, &TerminateHandler) == SIG_ERR)
        ERRNO("Failed to initialize Terminate Signal handler");   
}

}
