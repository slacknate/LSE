#ifndef LSE_IO_HANDLER_WIN_H
#define LSE_IO_HANDLER_WIN_H

/*
Defining WINVER and _WIN32_WINNT as 0x501
tells the compiler that we assume we are
at least Windows XP.
*/

#ifdef WINVER
#undef WINVER
#endif

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#define WINVER          0x0501
#define _WIN32_WINNT    0x0501

#include <windows.h>
#include "io/base.h"

namespace LSE {

class IOHandler : public IOHandlerBase {
        
    public:
        IOHandler(Object *e);
        
        void register_input(HWND hwnd, unsigned short page, unsigned short id);
        void setup(HWND hwnd);
        static LRESULT CALLBACK window_proc(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam);
};

}

#endif
