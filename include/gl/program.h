#ifndef LSE_GL_PROG_H
#define LSE_GL_PROG_H

#include "lse/defs.h"
#include "lse/list.h"

namespace LSE {

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
} ShaderType;

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
} AttrPos;

/*
GLSL uniform type identifiers.
*/
typedef enum {
    
    FL1 = 0,
    FL2,
    FL3,
    FL4,
    IN1,
    IN2,
    IN3,
    IN4,
    UI1,
    UI2,
    UI3,
    UI4,
    FLV1,
    FLV2,
    FLV3,
    FLV4,
    INV1,
    INV2,
    INV3,
    INV4,
    UIV1,
    UIV2,
    UIV3,
    UIV4,
    MAT2,
    MAT3,
    MAT4,
    MAT23,
    MAT24,
    MAT32,
    MAT34,
    MAT42,
    MAT43,
} UniformType;

/*
Class which describes an OpenGL shader program.

TODO:
    include render/frame buffer objects in this?
*/
class GLProgram {
    
    public:
        
        unsigned int progID, lastID; // program IDs used to bind and unbind to this program
        List shaderIDs; // list of all shader IDs
        
        char* ReadShader(const char *fileName);
        GLenum GetShaderType(const char *fileName);
        GLenum GetShaderType(ShaderType type);
        bool ValidateShader(const char *fileName, unsigned int shaderID, ShaderType type);
        bool ValidateProgram();
             
    public:
        
        GLProgram();
        ~GLProgram();
        
        int AddShader(const char *buffer, ShaderType type=SHADER_INVALID);
        bool RemoveShader(unsigned int shaderID);
        
        void bind_attrib(AttrPos position, const char *const name);
        void uniform(UniformType type, const char *const name, ...);
        
        bool finalize();
        
        void bind();
        void unbind();
};

bool valid_shader_type(ShaderType type);

}

#endif
