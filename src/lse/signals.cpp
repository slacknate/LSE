#include <csignal>
#include "lse/signals.h"
#include "lse/globals.h"
using namespace LSE;

static Engine *engine = NULL;

void AbortHandler(int code) {
    
    logger.error("Abort signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    exit(code);
}

void FPEHandler(int code) {
    
    logger.error("Floating Point Exception signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    exit(code);
}

void IIHandler(int code) {
    
    logger.error("Illegal Instruction signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    exit(code);
}

void InterruptHandler(int code) {
    
    logger.error("Interrupt signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    exit(code);
}

void SegfaultHandler(int code) {
    
    logger.error("Segfault signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    exit(code);
}

void TerminateHandler(int code) {
    
    logger.error("Terminate signal received.\n");
    QuitEvent *quit_event = new QuitEvent();
    engine->Dispatch(NULL, EVENT_QUIT, Engine::ID_QUIT, quit_event);
    exit(code);
}

namespace LSE {

void InitSignals(Engine *e) {
    
    engine = e;
    
    if(signal(SIGABRT, &AbortHandler) == SIG_ERR)
        logger.errn("Failed to initialize Abort Signal handler");
    
    if(signal(SIGFPE, &FPEHandler) == SIG_ERR)
        logger.errn("Failed to initialize FPR Signal handler");
    
    if(signal(SIGILL, &IIHandler) == SIG_ERR)
        logger.errn("Failed to initialize II Signal handler");
    
    if(signal(SIGINT, &InterruptHandler) == SIG_ERR)
        logger.errn("Failed to initialize Interrupt Signal handler");
    
    if(signal(SIGSEGV, &SegfaultHandler) == SIG_ERR)
        logger.errn("Failed to initialize Segfault Signal handler");
    
    if(signal(SIGTERM, &TerminateHandler) == SIG_ERR)
        logger.errn("Failed to initialize Terminate Signal handler");   
}

}
