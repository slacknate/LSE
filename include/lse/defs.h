#ifndef LSE_DEFS_H
#define LSE_DEFS_H

/*
OpenGL and Extension Wrangler includes.
TODO: determine if these includes can be moved into more specialized headers
*/
#include <gl/glew.h>
#include <gl/gl.h>

// TODO: move functions into the util src/include directories in well named files
namespace LSE {
    
/*
Minimum OpenGL and GLSL requirements.
*/
const int MIN_GL_VERSION      = 320;
const int MIN_SL_VERSION      = 150;
const int GL_MIN_COLOR_ATTACH = 2;
const int GL_MIN_VERT_ATTRIB  = 6;

enum {
    
    STATE_DOWN = 0x000,
    STATE_UP   = 0x001
};

/*
Keyboard event constants.
*/
enum {

	KEY_LSHIFT        = 0x100,
	KEY_RSHIFT        = 0x101,
	KEY_LCTRL         = 0x102,
	KEY_RCTRL         = 0x103,
	KEY_LALT          = 0x104,
	KEY_RALT          = 0x105,
	KEY_BACKSPACE     = 0x106,
	KEY_TAB           = 0x107,
	KEY_RETURN        = 0x108,
	KEY_PAUSE         = 0x109,
	KEY_ESCAPE        = 0x10A,
	KEY_SPACE         = 0x10B,
	KEY_NUMLOCK       = 0x10C,
	KEY_SCROLLOCK     = 0x10D,
	KEY_CAPSLOCK      = 0x10E,
	KEY_PAGEUP        = 0x10F,
	KEY_PAGEDOWN      = 0x110,
	KEY_END           = 0x111,
	KEY_DOWN          = 0x112,
	KEY_LEFT          = 0x113,
	KEY_UP            = 0x114,
	KEY_RIGHT         = 0x115,
	KEY_HOME          = 0x116,
	KEY_PRNTSCRN      = 0x117,
	KEY_INSERT        = 0x118,
	KEY_DELETE        = 0x119,
	KEY_LSUPER        = 0x11A,
	KEY_RSUPER        = 0x11B,
	KEY_MENU          = 0x11C,
	KEY_NUM0          = 0x11D,
	KEY_NUM1          = 0x11E,
	KEY_NUM2          = 0x11F,
	KEY_NUM3          = 0x120,
	KEY_NUM4          = 0x121,
	KEY_NUM5          = 0x122,
	KEY_NUM6          = 0x123,
	KEY_NUM7          = 0x124,
	KEY_NUM8          = 0x125,
	KEY_NUM9          = 0x126,
	KEY_MULT          = 0x127,
	KEY_ADD           = 0x128,
	KEY_SUB           = 0x129,
	KEY_DIV           = 0x12A,
	KEY_DECIMAL       = 0x12B,
	KEY_F1            = 0x12C,
	KEY_F2            = 0x12D,
	KEY_F3            = 0x12E,
	KEY_F4            = 0x12F,
	KEY_F5            = 0x130,
	KEY_F6            = 0x131,
	KEY_F7            = 0x132,
	KEY_F8            = 0x133,
	KEY_F9            = 0x134,
	KEY_F10           = 0x135,
	KEY_F11           = 0x136,
	KEY_F12           = 0x137,
	KEY_TILDE         = 0x138,
	KEY_UNDERSCORE    = 0x139,
	KEY_EQUALS        = 0x13A,
	KEY_LEFT_BRACKET  = 0x13B,
	KEY_RIGHT_BRACKET = 0x13C,
	KEY_BSLASH        = 0x13D,
	KEY_COLONS        = 0x13E,
	KEY_QUOTES        = 0x13F,
	KEY_COMMA         = 0x140,
	KEY_PERIOD        = 0x141,
	KEY_FSLASH        = 0x142,
	KEY_CLEAR         = 0x143,
	KEY_INVALID       = ((unsigned int)-1)
};

/*
Mouse event constants
*/
enum {
    
	MOUSE_LEFT    = 0x1000,
	MOUSE_MIDDLE  = 0x1001,
	MOUSE_RIGHT   = 0x1002,
	MOUSE_WHEEL   = 0x1003,
	MOUSE_INVALID = ((unsigned int)-1)
};

/*
LSE engine return types.
*/
enum EngineStatus {
    
    OK = 0,
    GL_INIT_FAIL,
    GL_PROG_FAIL,
    BAD_ALLOC,
    BAD_CAST,
    BAD_EXCEPTION,
    BAD_TYPE_ID,
    IOS_FAIL,
    RUNTIME_ERR,
    LOGIC_ERR,
    WIN_REG_FAIL,
    WIN_CREATE_FAIL,
    GL_CON_FAIL,
    IO_SETUP_FAIL,
    STAT_LAST
};

/*
OpenGL Version and Attribute fetching functions.
*/
int GLVersion();
const char* GLVendorVersion();
int SLVersion();
const char* SLVendorVersion();
int MaxGLVertAttrib();
int MaxFBOColorAttachments();

/*
Utility functions.
*/
const char* GLErrorString(GLenum e);


/*
LSE Engine status functions.
*/
int StatusCode(int code=-1);
int ExtendedStatusCode();
const char* StatusString(int code=-1);
const char* StatusID(int code=-1);

}

#endif
