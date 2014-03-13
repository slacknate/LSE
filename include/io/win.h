#ifndef LSE_IO_HANDLER_WIN_H
#define LSE_IO_HANDLER_WIN_H

#include "io/base.h"

class LSE_IOHandler_Win : public LSE_IOHandler_Base {
        
    public:      
        void Setup(HWND hwnd);
        static LRESULT CALLBACK WindowHandler(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);
};

#define LSE_IOHandler LSE_IOHandler_Win

#endif
