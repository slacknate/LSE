#include "io/win.h"
#include "lse/engine.h"

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
                key_event->key = 0;
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
