#ifndef LSE_IO_HANDLER_WIN_H
#define LSE_IO_HANDLER_WIN_H

/*
Defining WINVER and _WIN32_WINNT as 0x501
tells the compiler that we assume we are
at least Windows XP.
*/
#define WINVER          0x0501
#define _WIN32_WINNT    0x0501

#include <windows.h>
#include "io/base.h"

class LSE_IOHandler_Win : public LSE_IOHandler_Base {
        
    public:
        LSE_IOHandler_Win(LSE_Object *e);
        
        void Setup(HWND hwnd);
        static LRESULT CALLBACK WindowHandler(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);
};

#define LSE_IOHandler LSE_IOHandler_Win

#endif
