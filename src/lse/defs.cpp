#include "lse/defs.h"

/*
OpenGL error messages.
*/
static const char *const GL_ERRORS[] = {
    
    "GL_INVALID_ENUM",
    "GL_INVALID_VALUE",
    "GL_INVALID_OPERATION",
    "GL_INVALID_FRAMEBUFFER_OPERATION",
    "GL_OUT_OF_MEMORY",
    "GL_STACK_UNDERFLOW",
    "GL_STACK_OVERFLOW"
};

/*
LSE Shader type strings.
*/
static const char *const SHADER_STRINGS[] = {
    
    "Invalid",
    "Vertex",
    "Tesselation control",
    "Tesselation evaluation",
    "Geometry",
    "Fragment"
};

/*

*/
static const char *const ERROR_ID_STRINGS[] = {
    
    "LSE_OK",
    "LSE_GL_INIT_FAIL",
    "LSE_GL_PROG_FAIL",
    "LSE_BAD_ALLOC",
    "LSE_BAD_CAST",
    "LSE_BAD_EXCEPTION",
    "LSE_BAD_TYPE_ID",
    "LSE_IOS_FAIL",
    "LSE_RUNTIME_ERR",
    "LSE_LOGIC_ERR",
    "LSE_WIN_REG_FAIL",
    "LSE_WIN_CREATE_FAIL",
    "LSE_GL_CON_FAIL",
    "LSE_IO_SETUP_FAIL",
    "LSE_STAT_LAST"
};

/*
LSE Status strings.
*/
static const char *const ERROR_STRINGS[] = {
    
    "No errors. ",
    "OpenGL failed to initialize. ",
    "OpenGL shader program failed to verify. ",
    "Bad memory allocation. ",
    "Bad dynamic cast. ",
    "Unhandled exceptions. ",
    "NULL pointer passed to typeid(). ",
    "Stream error. ",
    "Logic error. ",
    "Runtime error. ",
    "Failed to register window. ",
    "Failed to create window. ",
    "Failed to obtain an OpenGL context. ",
    "Failed to setup IO handlers. ",
    "Unknown error code. "
};

/*
Global viewing and projection matrices.
They are column major format:

0 4 8  12
1 5 9  13
2 6 10 14
3 7 11 15
*/
static float viewing[16], projection[16];

/*
LSE Error status.
*/
static int errorStatus = LSE_OK;

/*
Return the string equivalent of an
OpenGL error code.
*/
const char* LSE_GLErrorString(GLenum e) {
    
    int i = e - 0x0500;
    if(i >= 0 && i < 7)
        return GL_ERRORS[i];
    else
        return "Unknown OpenGL error.";
}

/*
Return the shader type name as a string.
*/
const char* LSE_ShaderString(LSE_ShaderType s) {
    
    return SHADER_STRINGS[s];
}

/*
Return a pointer to the viewing matrix.
*/
float* LSE_GetViewingMatrix() {
    
    return &viewing[0];
}

/*
Return a pointer to the projection matrix.
*/
float* LSE_GetProjectionMatrix() {
    
    return &projection[0];
}

/*

*/
int LSE_ErrorStatus(int c) {
    
    if(c >= LSE_OK && c < LSE_STAT_LAST)
        errorStatus = c;
        
    return errorStatus;
}

/*

*/
const char* LSE_ErrorString(int c) {
    
    if(c >= LSE_OK && c < LSE_STAT_LAST)
        return ERROR_STRINGS[c];
    else
        return ERROR_STRINGS[errorStatus];
}

/*

*/
const char* LSE_ErrorIDString(int c) {
    
    if(c >= LSE_OK && c < LSE_STAT_LAST)
        return ERROR_ID_STRINGS[c];
    else
        return ERROR_ID_STRINGS[errorStatus];
}

void LSE_WriteLog(FILE *stream, ...) {
    
    char *timeStr = new (std::nothrow) char [9];
    if(stream != NULL && timeStr != NULL) {
        
        memset(timeStr, 0, 9);
        
        time_t t;
        time(&t);
        char *static_time = ctime(&t);
    
        strncpy(timeStr, &static_time[11], 8);
        
        fprintf(stream, "[%s]: ", timeStr);
        
        delete[] timeStr;
        timeStr = NULL;
        
        va_list argList;
        va_start(argList, stream);
        
        const char *format = va_arg(argList, const char *);
        vfprintf(stream, format, argList);
    
        va_end(argList);
        
        fprintf(stream, "\n");
    }
    else {
        
        LSE_ERROR_LOG("Could not create time string or NULL log stream supplied.");
    }
}
