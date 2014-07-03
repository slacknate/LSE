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

namespace LSE {

class LSE_IOHandler : public LSE_IOHandler_Base {
        
    public:
        LSE_IOHandler(LSE_Object *e);
        
        void RegisterInput(HWND hwnd, unsigned short page, unsigned short id);
        void Setup(HWND hwnd);
        static LRESULT CALLBACK WindowHandler(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);
};

}

#endif
