#include "io/win.h"
#include "lse/engine.h"

/*
TODO:
    function key support?
*/

/*
These constants are used for opening
raw device input.

Reference: msdn.microsoft.com/en-us/library/ff543477(VS.85).aspx
*/
const unsigned short POINTER_ID    = 0x01;
const unsigned short POINTER_PAGE  = 0x01;

const unsigned short MOUSE_ID      = 0x02;
const unsigned short MOUSE_PAGE    = 0x01;

const unsigned short JOYSTICK_ID   = 0x04;
const unsigned short JOYSTICK_PAGE = 0x01;

const unsigned short GAME_PAD_ID   = 0x05;
const unsigned short GAME_PAD_PAGE = 0x01;

const unsigned short KEYBOARD_ID   = 0x06;
const unsigned short KEYBOARD_PAGE = 0x01;

const unsigned short KEYPAD_ID     = 0x07;
const unsigned short KEYPAD_PAGE   = 0x01;

/*

*/
unsigned int vkey_to_lkey(unsigned int vkey, unsigned int make_code, unsigned int left_right) {
    
    LSE_MESSG_LOG(LOG_LEVEL_RAW, "Got vkey code: 0x%.2X, make code: 0x%.2X, left/right flag: 0x%.2X", vkey, make_code, left_right);
    
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
        case VK_CLEAR:
            lkey = LSE_KEY_CLEAR; break;
        case VK_OEM_1: // ;: on US standard keyboard
            lkey = LSE_KEY_COLONS; break;
        case VK_OEM_2: // /? on US standard keyboard
            lkey = LSE_KEY_FSLASH; break;
        case VK_OEM_3: // `~ on US standard keyboard
            lkey = LSE_KEY_TILDE; break;
        case VK_OEM_4: // [{ on US standard keyboard
            lkey = LSE_KEY_LEFT_BRACKET; break;
        case VK_OEM_5: // \| on US standard keyboard
            lkey = LSE_KEY_BSLASH; break;
        case VK_OEM_6: // ]} on US standard keyboard
            lkey = LSE_KEY_RIGHT_BRACKET; break;
        case VK_OEM_7: // '" on US standard keyboard
            lkey = LSE_KEY_QUOTES; break;
        case VK_OEM_COMMA: // ,
            lkey = LSE_KEY_COMMA; break;
        case VK_OEM_PERIOD: // .
            lkey = LSE_KEY_PERIOD; break;
        case VK_OEM_MINUS: // -_
            lkey = LSE_KEY_UNDERSCORE; break;
        case VK_OEM_PLUS: // +=
            lkey = LSE_KEY_EQUALS; break;
        case VK_SHIFT:
            if(make_code == 42) // left shift
                lkey = LSE_KEY_LSHIFT;
            
            else if(make_code == 54) // right shift
                lkey = LSE_KEY_RSHIFT;
                 
            break;
        case VK_CONTROL:
            if(left_right == RI_KEY_E0) // left control
                lkey = LSE_KEY_LCTRL;
            
            else if(left_right == RI_KEY_E1) // right control
                lkey = LSE_KEY_RCTRL;
                 
            break;
        case VK_MENU:
            if(left_right == RI_KEY_E0) // left alt
                lkey = LSE_KEY_LALT;
            
            else if(left_right == RI_KEY_E1) // right alt
                lkey = LSE_KEY_RALT;
                 
            break;
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
    
    LSE_MESSG_LOG(LOG_LEVEL_RAW, "Returning lkey code: 0x%.2X", lkey);
    
    return lkey;
}

/*

*/
int* vbutton_to_lbutton(unsigned int vbutton) {
    
    int *lbutton = new int[2];
    
    switch(vbutton) {
        
        case RI_MOUSE_LEFT_BUTTON_DOWN:
            lbutton[0] = LSE_LEFT_BUTTON; lbutton[1] = LSE_BUTTON_STATE_DOWN; break;
        case RI_MOUSE_LEFT_BUTTON_UP:
            lbutton[0] = LSE_LEFT_BUTTON; lbutton[1] = LSE_BUTTON_STATE_UP; break;
        case RI_MOUSE_MIDDLE_BUTTON_DOWN:
            lbutton[0] = LSE_MIDDLE_BUTTON; lbutton[1] = LSE_BUTTON_STATE_DOWN; break;
        case RI_MOUSE_MIDDLE_BUTTON_UP:
            lbutton[0] = LSE_MIDDLE_BUTTON; lbutton[1] = LSE_BUTTON_STATE_UP; break;
        case RI_MOUSE_RIGHT_BUTTON_DOWN:
            lbutton[0] = LSE_RIGHT_BUTTON; lbutton[1] = LSE_BUTTON_STATE_DOWN; break;
        case RI_MOUSE_RIGHT_BUTTON_UP:
            lbutton[0] = LSE_RIGHT_BUTTON; lbutton[1] = LSE_BUTTON_STATE_UP; break;
        case RI_MOUSE_WHEEL:
            lbutton[0] = LSE_MOUSE_WHEEL; lbutton[1] = 0; break;
        default:
            LSE_ERROR_LOG("Unhandled vbutton code: 0x%.4X", vbutton);
    }
    
    return lbutton;
}

/*

*/
LSE_IOHandler_Win::LSE_IOHandler_Win(LSE_Object *e) : LSE_IOHandler_Base(e) { }

/*

*/
void LSE_IOHandler_Win::RegisterInput(HWND hwnd, unsigned short page, unsigned short id) {
    
    RAWINPUTDEVICE raw_io;
    
    raw_io.usUsagePage = page; 
    raw_io.usUsage = id; 
    raw_io.dwFlags = RIDEV_NOLEGACY;
    raw_io.hwndTarget = hwnd;

    if(RegisterRawInputDevices(&raw_io, 1, sizeof(RAWINPUTDEVICE)) == false)
        LSE_THROW(LSE_IO_SETUP_FAIL);
}

/*

*/
void LSE_IOHandler_Win::Setup(HWND hwnd) {
    
    this->RegisterInput(hwnd, MOUSE_PAGE, MOUSE_ID);
    this->RegisterInput(hwnd, KEYBOARD_PAGE, KEYBOARD_ID);
}

/*

*/
LRESULT CALLBACK LSE_IOHandler_Win::WindowHandler(HWND hwnd, unsigned int message, WPARAM wParam, LPARAM lParam) {
    
    LRESULT result = 0;
    
    switch(message) {
        
        case WM_CLOSE:
        case WM_DESTROY:
            // close our window
            PostQuitMessage(0);
            // terminate the engine
            LSE_IOHandler_Base::HandleEvent(NULL, LSE_QUIT, LSE_Engine::ID_QUIT, NULL);
            break;
            
        case WM_INPUT:
            HRAWINPUT r_input = (HRAWINPUT)lParam;
            
            unsigned int num_bytes;
            GetRawInputData(r_input, RID_INPUT, NULL, &num_bytes, sizeof(RAWINPUTHEADER));
            
            BYTE *raw_memory = new BYTE[num_bytes];
            if(raw_memory == NULL) {
                
                LSE_ERROR_LOG("raw_memory is NULL!"); // TODO: proper error handling/logging
                return 0;
            }
            
            if(GetRawInputData(r_input, RID_INPUT, raw_memory, &num_bytes, sizeof(RAWINPUTHEADER)) != num_bytes) {
                
                LSE_ERROR_LOG("GetRawInputData did not return correct size!"); // TODO: proper error handling/logging
                return 0;
            }

            RAWINPUT* raw_input = (RAWINPUT*)raw_memory;
            if(raw_input->header.dwType == RIM_TYPEKEYBOARD) {
                
                RAWKEYBOARD *r_keyboard = &raw_input->data.keyboard;
                
                // Not sure why the flags don't seem to match the MSDN documentation.
                // Adding 0x02 to them DOES make them work like the docs though soooo... o_O
                unsigned int keyboard_flags = r_keyboard->Flags + 0x02;
                unsigned int make_break = keyboard_flags & 0x01;
                unsigned int left_right = keyboard_flags & 0x06;
                
                unsigned int key_state = (unsigned int)-1;
                if(make_break == RI_KEY_BREAK)
                    key_state = LSE_KEY_STATE_UP;
                    
                else if(make_break == RI_KEY_MAKE)
                    key_state = LSE_KEY_STATE_DOWN;
                    
                else
                    LSE_ERROR_LOG("Invalid make/break state: %d", make_break); // TODO: real error handling
                
                LSE_KeyEvent *key_event = new LSE_KeyEvent;
                key_event->key = vkey_to_lkey(r_keyboard->VKey, r_keyboard->MakeCode, left_right);
                key_event->state = key_state;
                
                LSE_IOHandler_Base::HandleEvent(NULL, LSE_KEYBOARD, LSE_ANY, key_event);
            }
            else if(raw_input->header.dwType == RIM_TYPEMOUSE) {
            
                RAWMOUSE *r_mouse = &raw_input->data.mouse;
                LSE_MouseEvent *mouse_event = new LSE_MouseEvent;
                
                if(r_mouse->usButtonFlags) {
                    
                    int *lbutton = vbutton_to_lbutton(r_mouse->usButtonFlags);
                    
                    if(lbutton[0] == LSE_MOUSE_WHEEL) {
                        
                        short scroll_magnitude = (short)r_mouse->usButtonData;
                        
                        mouse_event->button = lbutton[0];
                        mouse_event->state = scroll_magnitude > 0;
                        mouse_event->dW = scroll_magnitude;
                    }
                    else {
                        
                        mouse_event->button = lbutton[0];
                        mouse_event->state = lbutton[1];
                    }
                }
                else if(r_mouse->usFlags == MOUSE_MOVE_RELATIVE) {
                    
                    mouse_event->dX = r_mouse->lLastX;
                    mouse_event->dY = r_mouse->lLastY;
                }
                else {
                    
                    LSE_ERROR_LOG("Invalid mouse state"); // TODO: real error handling
                }
                
                LSE_IOHandler_Base::HandleEvent(NULL, LSE_MOUSE, LSE_ANY, mouse_event);
            }
            else if(raw_input->header.dwType == RIM_TYPEHID) {
                
                
            }
            else {
                
                LSE_ERROR_LOG("Invalid raw input type %d", raw_input->header.dwType); // TODO: real error handling
            }
            
        case WM_SIZING: // window being resized
            RECT *new_size = (RECT *)lParam;
            unsigned int new_width = new_size->right - new_size->left;
            unsigned int new_height = new_size->bottom - new_size->top;
            break;
            
        case WM_MOVING:
            RECT *new_pos = (RECT *)lParam;
            unsigned int new_x_pos = new_pos->left;
            unsigned int new_y_pos = new_pos->top;
            break;
        
        default:
            result = DefWindowProc(hwnd, message, wParam, lParam);
    }
    
    return result;
}
