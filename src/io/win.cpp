#include "io/win.h"
#include "lse/engine.h"

/*

*/
unsigned int vkey_to_lkey(unsigned int vkey) {
    
    unsigned int lkey = LSE_KEY_INVALID;
    
    switch(vkey) {
        
        case VK_BACK:
            lkey = LSE_KEY_BACKSPACE; break;
        case VK_TAB:
            lkey = LSE_KEY_TAB; break;
        case VK_RETURN:
            lkey = LSE_KEY_RETURN; break;
        case VK_PAUSE:
            lkey = LSE_KEY_PAUSE; break;
        case VK_ESCAPE:
            lkey = LSE_KEY_ESCAPE; break;
        case VK_SPACE:
            lkey = LSE_KEY_SPACE; break;
        case VK_PRIOR: // page up
            lkey = LSE_KEY_PAGEUP; break;
        case VK_NEXT: // page down
            lkey = LSE_KEY_PAGEDOWN; break;
        case VK_END:
            lkey = LSE_KEY_END; break;
        case VK_HOME:
            lkey = LSE_KEY_HOME; break;
        case VK_LEFT:
            lkey = LSE_KEY_LEFT; break;
        case VK_UP:
            lkey = LSE_KEY_UP; break;
        case VK_RIGHT:
            lkey = LSE_KEY_RIGHT; break;
        case VK_DOWN:
            lkey = LSE_KEY_DOWN; break;
        case VK_SNAPSHOT: // print screen
            lkey = LSE_KEY_PRNTSCRN; break;
        case VK_INSERT:
            lkey = LSE_KEY_INSERT; break;
        case VK_DELETE:
            lkey = LSE_KEY_DELETE; break;
        case VK_LWIN: // left windows key
            lkey = LSE_KEY_LSUPER; break;
        case VK_RWIN: // right windows key
            lkey = LSE_KEY_RSUPER; break;
        case VK_APPS: // menu key
            lkey = LSE_KEY_MENU; break;
        case VK_NUMPAD0:
            lkey = LSE_KEY_NUM0; break;
        case VK_NUMPAD1:
            lkey = LSE_KEY_NUM1; break;
        case VK_NUMPAD2:
            lkey = LSE_KEY_NUM2; break;
        case VK_NUMPAD3:
            lkey = LSE_KEY_NUM3; break;
        case VK_NUMPAD4:
            lkey = LSE_KEY_NUM4; break;
        case VK_NUMPAD5:
            lkey = LSE_KEY_NUM5; break;
        case VK_NUMPAD6:
            lkey = LSE_KEY_NUM6; break;
        case VK_NUMPAD7:
            lkey = LSE_KEY_NUM7; break;
        case VK_NUMPAD8:
            lkey = LSE_KEY_NUM8; break;
        case VK_NUMPAD9:
            lkey = LSE_KEY_NUM9; break;
        case VK_MULTIPLY:
            lkey = LSE_KEY_MULT; break;
        case VK_ADD:
            lkey = LSE_KEY_ADD; break;
        case VK_SUBTRACT:
            lkey = LSE_KEY_SUB; break;
        case VK_DECIMAL:
            lkey = LSE_KEY_DECIMAL; break;
        case VK_DIVIDE:
            lkey = LSE_KEY_DIV; break;
        case VK_F1:
            lkey = LSE_KEY_F1; break;
        case VK_F2:
            lkey = LSE_KEY_F2; break;
        case VK_F3:
            lkey = LSE_KEY_F3; break;
        case VK_F4:
            lkey = LSE_KEY_F4; break;
        case VK_F5:
            lkey = LSE_KEY_F5; break;
        case VK_F6:
            lkey = LSE_KEY_F6; break;
        case VK_F7:
            lkey = LSE_KEY_F7; break;
        case VK_F8:
            lkey = LSE_KEY_F8; break;
        case VK_F9:
            lkey = LSE_KEY_F9; break;
        case VK_F10:
            lkey = LSE_KEY_F10; break;
        case VK_F11:
            lkey = LSE_KEY_F11; break;
        case VK_F12:
            lkey = LSE_KEY_F12; break;
        case VK_NUMLOCK:
            lkey = LSE_KEY_NUMLOCK; break;
        case VK_SCROLL:
            lkey = LSE_KEY_SCROLLOCK; break;
        case VK_CAPITAL:
            lkey = LSE_KEY_CAPSLOCK; break;
        case VK_LSHIFT:
            lkey = LSE_KEY_LSHIFT; break;
        case VK_RSHIFT:
            lkey = LSE_KEY_RSHIFT; break;
        case VK_LCONTROL:
            lkey = LSE_KEY_LCTRL; break;
        case VK_RCONTROL:
            lkey = LSE_KEY_RCTRL; break;
        case VK_LMENU: // left alt
            lkey = LSE_KEY_LALT; break;
        case VK_RMENU: // right alt
            lkey = LSE_KEY_RALT; break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':    
            lkey = vkey; break;
        default:
            LSE_ERROR_LOG("Unhandled vkey code: 0x%.2X", vkey);
    }
    
    LSE_MESSG_LOG(LOG_LEVEL_DEBUG, "Returning lkey code: 0x%.2X", lkey);
    
    return lkey;
}

/*

*/
LSE_IOHandler_Win::LSE_IOHandler_Win(LSE_Object *e) : LSE_IOHandler_Base(e) { }

/*

*/
void LSE_IOHandler_Win::Setup(HWND hwnd) {
    
    RAWINPUTDEVICE raw_io[2];
        
    raw_io[0].usUsagePage = 0x01; 
    raw_io[0].usUsage = 0x02; 
    raw_io[0].dwFlags = RIDEV_NOLEGACY;
    raw_io[0].hwndTarget = hwnd;

    raw_io[1].usUsagePage = 0x01; 
    raw_io[1].usUsage = 0x06; 
    raw_io[1].dwFlags = RIDEV_NOLEGACY;
    raw_io[1].hwndTarget = hwnd;

    if(RegisterRawInputDevices(raw_io, 2, sizeof(raw_io[0])) == false)
        LSE_THROW(LSE_IO_SETUP_FAIL);
}

/*
Catch all window activate, create, destroy,
minimize, maximize, move, or sizing events.
*/
LRESULT CALLBACK LSE_IOHandler_Win::WindowHandler(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam) {
    
    switch(message) {
        
        case WM_QUIT:
        case WM_CLOSE:
        case WM_DESTROY:
            // close our window
            PostQuitMessage(0);
            // terminate the engine
            HandleEvent(NULL, LSE_QUIT, LSE_Engine::ID_QUIT, NULL);
            break;
        case WM_INPUT:
            HRAWINPUT r_input = (HRAWINPUT)lParam;
            
            unsigned int dwSize;
            GetRawInputData(r_input, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
            
            BYTE *raw_memory = new BYTE[dwSize];
            if(raw_memory == NULL) {
                
                LSE_ERROR_LOG("lpb is NULL!"); // TODO: proper error handling/logging
                return 0;
            }
            
            if(GetRawInputData(r_input, RID_INPUT, raw_memory, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize) {
                
                LSE_ERROR_LOG("GetRawInputData does not return correct size!"); // TODO: proper error handling/logging
                return 0;
            }

            RAWINPUT* raw_input = (RAWINPUT*)raw_memory;
            if (raw_input->header.dwType == RIM_TYPEKEYBOARD) {
                
                RAWKEYBOARD *r_keyboard = &raw_input->data.keyboard;
                
                unsigned int key_state = (unsigned int)-1;
                if(r_keyboard->Flags == RI_KEY_BREAK)
                    key_state = LSE_KEY_STATE_UP;
                    
                else if(r_keyboard->Flags == RI_KEY_BREAK)
                    key_state = LSE_KEY_STATE_DOWN;
                
                LSE_KeyEvent *key_event = new LSE_KeyEvent;
                key_event->key = vkey_to_lkey(r_keyboard->VKey);
                key_event->state = key_state;
                
                LSE_IOHandler_Base::HandleEvent(NULL, LSE_ANY, LSE_ANY, key_event);
            }
            else if(raw_input->header.dwType == RIM_TYPEMOUSE) {
            
                RAWMOUSE *r_mouse = &raw_input->data.mouse;
            
                /*LSE_MESSG_LOG("mouse:\n%hu\n%lu\n%hu\n%hu\n%lu\n%d\n%d\n%lu\n",
                       r_mouse->usFlags, 
                       r_mouse->ulButtons, 
                       r_mouse->usButtonFlags, 
                       r_mouse->usButtonData, 
                       r_mouse->ulRawButtons, 
                       r_mouse->lLastX, 
                       r_mouse->lLastY, 
                       r_mouse->ulExtraInformation);  */
            }
            return DefRawInputProc(&raw_input, 1, sizeof(RAWINPUTHEADER));
        case WM_SIZING: // window being resized
            RECT *newSize = (RECT *)lParam;
            unsigned int newWidth = newSize->right - newSize->left;
            unsigned int newHeight = newSize->bottom - newSize->top;
            break;
        case WM_MOVING:
            RECT *newPos = (RECT *)lParam;
            unsigned int newXPos = newPos->left;
            unsigned int newYPos = newPos->top;
            break;
        
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    
    return 0;
}
