#include <csignal>
#include "lse/signals.h"
#include "lse/defs.h"

namespace LSE_Signal {

static LSE_Engine *engine = NULL;

void AbortHandler(int code) {
    
    LSE_ERROR_LOG("Abort signal received.\n");
    engine->Dispatch(NULL, LSE_QUIT, LSE_Engine::ID_QUIT, NULL);
    exit(code);
}

void FPEHandler(int code) {
    
    LSE_ERROR_LOG("Floating Point Exception signal received.\n");
    engine->Dispatch(NULL, LSE_QUIT, LSE_Engine::ID_QUIT, NULL);
    exit(code);
}

void IIHandler(int code) {
    
    LSE_ERROR_LOG("Illegal Instruction signal received.\n");
    engine->Dispatch(NULL, LSE_QUIT, LSE_Engine::ID_QUIT, NULL);
    system("pause");
    exit(code);
}

void InterruptHandler(int code) {
    
    LSE_ERROR_LOG("Interrupt signal received.\n");
    engine->Dispatch(NULL, LSE_QUIT, LSE_Engine::ID_QUIT, NULL);
    system("pause");
    exit(code);
}

void SegfaultHandler(int code) {
    
    LSE_ERROR_LOG("Segfault signal received.\n");
    engine->Dispatch(NULL, LSE_QUIT, LSE_Engine::ID_QUIT, NULL);
    system("pause");
    exit(code);
}

void TerminateHandler(int code) {
    
    LSE_ERROR_LOG("Terminate signal received.\n");
    engine->Dispatch(NULL, LSE_QUIT, LSE_Engine::ID_QUIT, NULL);
    system("pause");
    exit(code);
}

void LSE_InitSignals(LSE_Engine *e) {
    
    engine = e;
    
    if(signal(SIGABRT, &AbortHandler) == SIG_ERR)
        LSE_ERRNO_LOG("Failed to initialize Abort Signal handler");
    
    if(signal(SIGFPE, &FPEHandler) == SIG_ERR)
        LSE_ERRNO_LOG("Failed to initialize FPR Signal handler");
    
    if(signal(SIGILL, &IIHandler) == SIG_ERR)
        LSE_ERRNO_LOG("Failed to initialize II Signal handler");
    
    if(signal(SIGINT, &InterruptHandler) == SIG_ERR)
        LSE_ERRNO_LOG("Failed to initialize Interrupt Signal handler");
    
    if(signal(SIGSEGV, &SegfaultHandler) == SIG_ERR)
        LSE_ERRNO_LOG("Failed to initialize Segfault Signal handler");
    
    if(signal(SIGTERM, &TerminateHandler) == SIG_ERR)
        LSE_ERRNO_LOG("Failed to initialize Terminate Signal handler");   
}

};
