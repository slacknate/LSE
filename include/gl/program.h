#ifndef LSE_GL_PROG_H
#define LSE_GL_PROG_H

#include "lse/defs.h"
#include "lse/list.h"

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
        
        void BindAttrib(unsigned int position, const char *const name);
        void BindUniform(unsigned int type, const char *const name, ...);
        
        bool Finalize();
        
        void Bind();
        void Unbind();
};

#endif
