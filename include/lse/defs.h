#ifndef LSE_DEFS_H
#define LSE_DEFS_H

/*
OpenGL and Extension Wrangler includes.
*/
#include <gl/glew.h>
#include <gl/gl.h>

/*
LSE includes.
*/
#include "lse/logger.h"
#include "lse/exception.h"

/*
Extended error code macros.
*/
#if defined(_WIN32) || defined(_WIN64)
#define LSE_EXT_ERR_CODE        (GetLastError())
#elif defined(__unix__) && !defined(__APPLE__) // all unix variants, non-mac
#define LSE_EXT_ERR_CODE        ??? // FIXME
#elif defined(__APPLE__) && !defined(__MACH__) // mac osx, non-ios
#define LSE_EXT_ERR_CODE        ??? // FIXME
#endif

/*
LSE Engine status macros.
*/
#define LSE_STATUS              (LSE_ErrorStatus())
#define LSE_ERROR_STRING        (LSE_ErrorString())
#define LSE_ERROR_ID_STRING     (LSE_ErrorIDString())

/*
OpenGL function macros.
*/
#define LSE_GL_VERSION          (LSE_GLVersion())
#define LSE_GL_VERSION_STR      (LSE_GLVersionString())
#define LSE_SL_VERSION          (LSE_SLVersion())
#define LSE_SL_VERSION_STR      (LSE_SLVersionString())
#define LSE_GL_MIN_VERT_ATTRIB  6
#define LSE_GL_MAX_VERT_ATTRIB  (LSE_MaxGLVertAttrib())
#define LSE_GL_MIN_COLOR_ATTACH 2
#define LSE_GL_MAX_COLOR_ATTACH (LSE_MaxFBOColorAttachments())
#define LSE_MIN_GL_VERSION      320
#define LSE_MIN_GL_VERSION_STR  "320"
#define LSE_MIN_SL_VERSION      150
#define LSE_MIN_SL_VERSION_STR  "150"
#define LSE_GL_VENDOR_VERSION   ((const char* const)glGetString(GL_VERSION))
#define LSE_SL_VENDOR_VERSION   ((const char* const)glGetString(GL_SHADING_LANGUAGE_VERSION))

/*
Keyboard event constants.
*/
#define LSE_KEY_STATE_DOWN      0
#define LSE_KEY_STATE_UP        1

#define LSE_KEY_LSHIFT          0x100
#define LSE_KEY_RSHIFT          0x101
#define LSE_KEY_LCTRL           0x102
#define LSE_KEY_RCTRL           0x103
#define LSE_KEY_LALT            0x104
#define LSE_KEY_RALT            0x105
#define LSE_KEY_BACKSPACE       0x106
#define LSE_KEY_TAB             0x107
#define LSE_KEY_RETURN          0x108
#define LSE_KEY_PAUSE           0x109
#define LSE_KEY_ESCAPE          0x10A
#define LSE_KEY_SPACE           0x10B
#define LSE_KEY_NUMLOCK         0x10C
#define LSE_KEY_SCROLLOCK       0x10D
#define LSE_KEY_CAPSLOCK        0x10E
#define LSE_KEY_PAGEUP          0x10F
#define LSE_KEY_PAGEDOWN        0x110
#define LSE_KEY_END             0x111
#define LSE_KEY_DOWN            0x112
#define LSE_KEY_LEFT            0x113
#define LSE_KEY_UP              0x114
#define LSE_KEY_RIGHT           0x115
#define LSE_KEY_HOME            0x116
#define LSE_KEY_PRNTSCRN        0x117
#define LSE_KEY_INSERT          0x118
#define LSE_KEY_DELETE          0x119
#define LSE_KEY_LSUPER          0x11A
#define LSE_KEY_RSUPER          0x11B
#define LSE_KEY_MENU            0x11C
#define LSE_KEY_NUM0            0x11D
#define LSE_KEY_NUM1            0x11E
#define LSE_KEY_NUM2            0x11F
#define LSE_KEY_NUM3            0x120
#define LSE_KEY_NUM4            0x121
#define LSE_KEY_NUM5            0x122
#define LSE_KEY_NUM6            0x123
#define LSE_KEY_NUM7            0x124
#define LSE_KEY_NUM8            0x125
#define LSE_KEY_NUM9            0x126
#define LSE_KEY_MULT            0x127
#define LSE_KEY_ADD             0x128
#define LSE_KEY_SUB             0x129
#define LSE_KEY_DIV             0x12A
#define LSE_KEY_DECIMAL         0x12B
#define LSE_KEY_F1              0x12C
#define LSE_KEY_F2              0x12D
#define LSE_KEY_F3              0x12E
#define LSE_KEY_F4              0x12F
#define LSE_KEY_F5              0x130
#define LSE_KEY_F6              0x131
#define LSE_KEY_F7              0x132
#define LSE_KEY_F8              0x133
#define LSE_KEY_F9              0x134
#define LSE_KEY_F10             0x135
#define LSE_KEY_F11             0x136
#define LSE_KEY_F12             0x137
#define LSE_KEY_INVALID         ((unsigned int)-1)

/*
Mouse event constants
*/
// ...lol...

/*
LSE engine return types.
*/
enum {
    
    LSE_OK = 0,
    LSE_GL_INIT_FAIL,
    LSE_GL_PROG_FAIL,
    LSE_BAD_ALLOC,
    LSE_BAD_CAST,
    LSE_BAD_EXCEPTION,
    LSE_BAD_TYPE_ID,
    LSE_IOS_FAIL,
    LSE_RUNTIME_ERR,
    LSE_LOGIC_ERR,
    LSE_WIN_REG_FAIL,
    LSE_WIN_CREATE_FAIL,
    LSE_GL_CON_FAIL,
    LSE_IO_SETUP_FAIL,
    LSE_STAT_LAST
};

/*
OpenGL Version and Attribute fetching functions.
*/
const int LSE_GLVersion();
const char *const LSE_GLVersionString();
const int LSE_SLVersion();
const char *const LSE_SLVersionString();
const int LSE_MaxGLVertAttrib();
const int LSE_MaxFBOColorAttachments();

/*
Utility functions.
*/
const char* LSE_GLErrorString(GLenum e);
int LSE_ErrorStatus(int c=-1);
const char* LSE_ErrorString(int c=-1);
const char* LSE_ErrorIDString(int c=-1);

/*

*/
float* LSE_GetViewingMatrix();
float* LSE_GetProjectionMatrix();

#endif
