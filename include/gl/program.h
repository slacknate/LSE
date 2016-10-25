#ifndef LSE_GL_PROG_H
#define LSE_GL_PROG_H

#include <vector>
#include "lse/defs.h"

namespace LSE {

/*
LSE Shader types.
*/
enum ShaderType {
    
    SHADER_VERT = 0,
    SHADER_TCON,
    SHADER_TEVA,
    SHADER_GEOM,
    SHADER_FRAG,
};

/*
GLSL Shader attribute constants.
*/
enum AttrPos {

    VERT_POSITION = 0,
    VERT_NORMAL,
    VERT_COLOR,
    VERT_TEX_COORD,

    LIGHT_DATA,
    MATERIAL_DATA
};

/*
GLSL uniform type identifiers.
*/
enum UniformType {
    
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
};

typedef std::vector<unsigned int> ShaderVector;

/*
Class which describes an OpenGL shader program.

TODO:
    include render/frame buffer objects in this?
*/
class GLProgram {
    
    public:
        
        unsigned int prog_id, last_id; // program IDs used to bind and unbind to this program
        ShaderVector shaders;

        GLenum gl_shader_type(ShaderType type);
        bool validate_shader(unsigned int shader_id, ShaderType type);
        bool validate_program();
             
    public:
        
        GLProgram();
        ~GLProgram();
        
        int add_shader(const char *buffer, ShaderType type);
        void remove_shader(unsigned int shader_id);
        
        void bind_attrib(AttrPos position, const char *const name);
        void uniform(UniformType type, const char *const name, ...);
        
        bool finalize();
        
        void bind();
        void unbind();
};

bool valid_shader_type(ShaderType type);

}

#endif
