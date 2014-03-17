#ifndef LSE_GL_PROG_H
#define LSE_GL_PROG_H

#include "lse/defs.h"
#include "lse/list.h"

/*
LSE Shader type validation function macro.
*/
#define VALID_SHADER_TYPE(X)    (X >= 0 && X < 6)

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
GLSL Shader attribute constants.
*/
typedef enum {
    
    VERT_POSITION = 0,
    VERT_NORMAL,
    VERT_COLOR,
    VERT_TEX_COORD,
    LIGHT_DATA,    
    MATERIAL_DATA
} LSE_AttrPos;

/*
GLSL uniform type identifiers.
*/
typedef enum {
    
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
} LSE_UniformType;

/*
Class which describes an OpenGL shader program.

TODO:
    include render/frame buffer objects in this?
*/
class LSE_GLProgram {
    
    private:
        
        unsigned int progID, lastID; // program IDs used to bind and unbind to this program
        LSE_List shaderIDs; // list of all shader IDs
        
        char* ReadShader(const char *fileName);
        GLenum ShaderType(const char *fileName);
        GLenum ShaderType(LSE_ShaderType lseType);
        bool ValidateShader(const char *fileName, unsigned int shaderID, LSE_ShaderType lseType);
        bool ValidateProgram();
             
    public:
        
        LSE_GLProgram();
        ~LSE_GLProgram();
        
        int AddShader(const char *buffer, LSE_ShaderType lseType=SHADER_INVALID);
        bool RemoveShader(unsigned int shaderID);
        
        void BindAttrib(LSE_AttrPos position, const char *const name);
        void BindUniform(LSE_UniformType type, const char *const name, ...);
        
        bool Finalize();
        
        void Bind();
        void Unbind();
};

#endif
