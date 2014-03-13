#ifndef LSE_DEFS_H
#define LSE_DEFS_H

/*
Platform specific includes.
*/
#if defined(_WIN32) || defined(_WIN64) // windows
// defining these constants as 0x0501 tells the compiler we are at least Windows XP
// super hack inc
#ifdef WINVER
#undef WINVER
#endif

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#define WINVER       0x0501
#define _WIN32_WINNT 0x0501
#include <windows.h>
#elif defined(__unix__) && !defined(__APPLE__) // all unix variants, non-mac

#elif defined(__APPLE__) && !defined(__MACH__) // mac osx, non-ios

#endif

/*
C++ includes.
*/
#include <new>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cerrno>
#include <cstdarg>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <typeinfo>
#include <iostream>

/*
Standard C++ exception includes.
*/
#include <stdexcept>
#include <exception>

/*
OpenGL and Extension Wrangler includes.
*/
#include <gl/glew.h>
#include <gl/gl.h>

/*
LSE includes.
*/
#include "lse/event.h"
#include "lse/exception.h"

/*
Exception function macros.
*/
#define LSE_TRY()               try { try {
#define LSE_THROW(X)            throw LSE_Exception(__FILE__, __LINE__, X);
#define LSE_CATCH()             } catch(const std::bad_alloc& ba) { throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_ALLOC); } \
                                catch(const std::bad_cast& bc) { throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_CAST); } \
                                catch(const std::bad_typeid& bc) { throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_TYPE_ID); } \
                                catch(const std::bad_exception& be) { throw LSE_Exception(__FILE__, __LINE__, LSE_BAD_EXCEPTION); } \
                                catch(const std::ios_base::failure& iof) { throw LSE_Exception(__FILE__, __LINE__, LSE_IOS_FAIL); } \
                                catch(const std::runtime_error& re) { throw LSE_Exception(__FILE__, __LINE__, LSE_RUNTIME_ERR); } \
                                catch(const std::logic_error& le) { throw LSE_Exception(__FILE__, __LINE__, LSE_LOGIC_ERR); } \
                                } catch(const LSE_Exception& e) { LSE_WriteLog(stderr, "%s", e.what()); LSE_ErrorStatus(e.code()); }


/*
Logging function macros.
*/
#define LSE_MESSG_LOG(...)      LSE_WriteLog(stdout, __VA_ARGS__)
#define LSE_ERROR_LOG(...)      LSE_WriteLog(stderr, __VA_ARGS__)
#define LSE_ERRNO_LOG(X)        LSE_WriteLog(stderr, "%s: %s", X, strerror(errno))

/*
Extended error code macros.
*/
#if defined(_WIN32) || defined(_WIN64)
#define LSE_EXT_ERR_CODE        (GetLastError())
#else
#define LSE_EXT_ERR_CODE        ??? // FIXME
#endif

/*
LSE Engine status macros.
*/
#define LSE_STATUS              (LSE_ErrorStatus())
#define LSE_ERROR_STRING        (LSE_ErrorString())
#define LSE_ERROR_ID_STRING     (LSE_ErrorIDString())

/*  
Directory structure character/string.
*/
#if defined(_WIN32) || defined(_WIN64)
#define DIR_CHR                 '\\'
#define DIR_STR                 "\\"
#else
#define DIR_CHR                 '/'
#define DIR_STR                 "/"
#endif

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
LSE Shader type validation function macro.
*/
#define VALID_SHADER_TYPE(X)    (X >= 0 && X < 6)

/*

*/
#define LSE_VIEW_MATRIX         (LSE_GetViewingMatrix())
#define LSE_PROJ_MATRIX         (LSE_GetProjectionMatrix())

/*
Class event map type declaration.
*/
#define \
LSE_DECLARE(classname) \
public: \
typedef struct { unsigned int type; unsigned int id; bool (classname::*func)(LSE_Object *, unsigned int, unsigned int, void *); } LSE_MapKey; \
virtual bool Dispatch(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr); \
private: \
static const int mapSize;

/*
Event map declaration.
*/
#define LSE_EVTMAP(classname) static const classname::LSE_MapKey 

/*
Event map entry.
*/
#define LSE_EVTFUNC(type, id, handler) {type, id, &handler}

/*
Event handler implementation.
*/
#define LSE_EVTIMP(classname, map) \
const int classname::mapSize = (sizeof(map)/sizeof(map[0])); \
bool classname::Dispatch(LSE_Object *sender, unsigned int type, unsigned int id, void *ptr) { \
for(int i = 0; i < mapSize; ++i) { if((map[i].type == type && map[i].id == id) || (map[i].type == LSE_ANY && map[i].id == LSE_ANY)) \
{ int result = (this->*(map[i].func))(sender, type, id, ptr); if(result != 0) { return result; } continue; } } return false; }

/*
Logging level constants.
*/
#define INFO     0
#define DEBUG    1
#define CRITICAL 2
#define VERBOSE  3
#define RAW      4

/*
Physics constants.
*/
#define PHY_UPD_TIME            1
#define PHY_UPD_MULT            0.001
#define PI                      3.14159265359

/*
Keyboard event constants.
*/
#define LSE_KEY_STATE_DOWN      0
#define LSE_KEY_STATE_UP        1

#define LSE_KEY_LSHIFT          1
#define LSE_KEY_RSHIFT          2
#define LSE_KEY_LCTRL           3
#define LSE_KEY_RCTRL           4
#define LSE_KEY_LALT            5
#define LSE_KEY_RALT            6
#define LSE_KEY_BACKSPACE       7
#define LSE_KEY_TAB             8
#define LSE_KEY_RETURN          9
#define LSE_KEY_PAUSE           10
#define LSE_KEY_CAPSLOCK        11
#define LSE_KEY_ESCAPE          12
#define LSE_KEY_SPACE           13
#define LSE_KEY_PAGEUP          14
#define LSE_KEY_PAGEDOWN        15
#define LSE_KEY_END             16
#define LSE_KEY_DOWN            17
#define LSE_KEY_LEFT            18
#define LSE_KEY_UP              19
#define LSE_KEY_RIGHT           20
#define LSE_KEY_HOME            21
#define LSE_KEY_PRNTSCRN        22
#define LSE_KEY_INSERT          23
#define LSE_KEY_DELETE          24
#define LSE_KEY_LSUPER          25
#define LSE_KEY_RSUPER          26
#define LSE_KEY_APP             27
#define LSE_KEY_NUM0            28
#define LSE_KEY_NUM1            29
#define LSE_KEY_NUM2            30
#define LSE_KEY_NUM3            31
#define LSE_KEY_NUM4            32
#define LSE_KEY_NUM5            33
#define LSE_KEY_NUM6            34
#define LSE_KEY_NUM7            35
#define LSE_KEY_NUM8            36
#define LSE_KEY_NUM9            37
#define LSE_KEY_MULT            38
#define LSE_KEY_ADD             39
#define LSE_KEY_SUB             40
#define LSE_KEY_DIV             41
#define LSE_KEY_DECIMAL         42
#define LSE_KEY_SEP             43
#define LSE_KEY_F1              44
#define LSE_KEY_F2              45
#define LSE_KEY_F3              46
#define LSE_KEY_F4              47
#define LSE_KEY_F5              48
#define LSE_KEY_F6              49
#define LSE_KEY_F7              50
#define LSE_KEY_F8              51
#define LSE_KEY_F9              52
#define LSE_KEY_F10             53
#define LSE_KEY_F11             54
#define LSE_KEY_F12             55
#define LSE_KEY_NUMLOCK         56
#define LSE_KEY_SCROLLOCK       57

/*
Mouse event constants
*/
// ...lol...

/*
GLSL Shader attribute constants.
*/
enum {
    
    VERT_POSITION = 0,
    VERT_NORMAL,
    VERT_COLOR,
    VERT_TEX_COORD,
    LIGHT_DATA,    
    MATERIAL_DATA
};

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
GLSL uniform type identifiers.
*/
enum {
    
    LSE_FL1 = 0,
    LSE_FL2,
    LSE_FL3,
    LSE_FL4,
    LSE_IN1,
    LSE_IN2,
    LSE_IN3,
    LSE_IN4,
    LSE_UI1,
    LSE_UI2,
    LSE_UI3,
    LSE_UI4,
    LSE_FLV1,
    LSE_FLV2,
    LSE_FLV3,
    LSE_FLV4,
    LSE_INV1,
    LSE_INV2,
    LSE_INV3,
    LSE_INV4,
    LSE_UIV1,
    LSE_UIV2,
    LSE_UIV3,
    LSE_UIV4,
    LSE_MAT2,
    LSE_MAT3,
    LSE_MAT4,
    LSE_MAT23,
    LSE_MAT24,
    LSE_MAT32,
    LSE_MAT34,
    LSE_MAT42,
    LSE_MAT43,
};

/*
LSE Shader types.
*/
typedef enum {
    
    SHADER_INVALID = 0,
    SHADER_VERT,
    SHADER_TCON,
    SHADER_TEVA,
    SHADER_GEOM,
    SHADER_FRAG,
} LSE_ShaderType;

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
const char* LSE_ShaderString(LSE_ShaderType s);
int LSE_ErrorStatus(int c=-1);
const char* LSE_ErrorString(int c=-1);
const char* LSE_ErrorIDString(int c=-1);
void LSE_WriteLog(FILE *stream, ...);

/*

*/
float* LSE_GetViewingMatrix();
float* LSE_GetProjectionMatrix();

#endif
