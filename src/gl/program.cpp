#include <new>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "gl/program.h"
#include "gl/manager.h"
#include "lse/globals.h"
#include "lse/exception.h"
using namespace LSE;

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
 * Return the shader type name as a string.
 */
const char* ShaderString(ShaderType s) {
    
    return SHADER_STRINGS[s];
}

namespace LSE {

/*
 * LSE Shader type validation function.
 */
bool valid_shader_type(ShaderType s) {
    
    return s >= SHADER_INVALID && s < SHADER_FRAG;
}

}

/*
 * Initialize our OpenGL program.
 */
GLProgram::GLProgram() {
    
    this->last_id = 0;
    this->prog_id = glCreateProgram();
}

/*
 * Detach and delete all attached shaders,
 * as well as the program.
 */
GLProgram::~GLProgram() {
    
    for(unsigned int i = 0; i < this->shaders.size(); ++i)
        glDeleteShader(this->shaders[i]);

    glDeleteProgram(this->prog_id);
}


/*
 * Get the OpenGL shader type from the LSE shader type.
 */
GLenum GLProgram::gl_shader_type(ShaderType type) {
    
    GLenum gl_type = 0; // FIXME: check to make sure this is indeed an invalid value
    
    if(type == SHADER_VERT)
        gl_type = GL_VERTEX_SHADER;

    else if(type == SHADER_TCON)
        gl_type = GL_TESS_CONTROL_SHADER;

    else if(type == SHADER_TEVA)
        gl_type = GL_TESS_EVALUATION_SHADER;

    else if(type == SHADER_GEOM)
        gl_type = GL_GEOMETRY_SHADER;

    else if(type == SHADER_FRAG)
        gl_type = GL_FRAGMENT_SHADER;

    else
        throw EXCEPTION("Invalid LSE Shader type. Unable to determine OpenGL shader type.");
    
    return gl_type;
}

/*
 * Check if the shader attached to the given ID is valid.
 */
bool GLProgram::validate_shader(unsigned int shader_id, ShaderType type) {
    
    int compile_success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_success);

    if(!compile_success) {

        int buff_size = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &buff_size);

        char buffer[buff_size];
        memset(buffer, 0, (size_t)buff_size);

        glGetShaderInfoLog(shader_id, buff_size, &buff_size, buffer);

        throw EXCEPTION("Shader %d failed validation: %s", shader_id, buffer);
    }
    
    return (bool)compile_success;
}

/*
 * Check if the whole program is valid.
 */
bool GLProgram::validate_program() {
    
    glValidateProgram(this->prog_id);
    
    int validate_success = 0;
    glGetProgramiv(this->prog_id, GL_VALIDATE_STATUS, &validate_success);
    
    return (bool)validate_success;
}

/*
 * Add a new shader to the program.
 * The parameter ``buffer`` contains the shader
 * source code which is passed to the compiler.
 */
int GLProgram::add_shader(const char *buffer, ShaderType type) {
    
    unsigned int shader_id = 0;
    
    if(buffer) {

        shader_id = glCreateShader(gl_shader_type(type));
        if(shader_id) {

            char sl_version_str[64];
            memset(sl_version_str, 0, 64);
            snprintf((char *)sl_version_str, 64, "%d", sl_version());

            unsigned int size[] = { 9, strlen(sl_version_str), 1, strlen(buffer) };
            const char *const src_with_version[] = { "#version ", sl_version_str, "\n", buffer };

            logger.verbose("Prepending GLSL version '%s' to shader source.", sl_version_str);

            // send the shader source code to the GPU, and compile it
            glShaderSource(shader_id, 4, (const char**)src_with_version, (int *)size);
            glCompileShader(shader_id);

            if(this->validate_shader(shader_id, type)) {

                // attach the compiled shader to the program and put it in our shaders vector
                glAttachShader(this->prog_id, shader_id);
                shaders.push_back(shader_id);
            }
            else {

                logger.error("An error occurred while creating shader: %s.", gl_error());
                glDeleteShader(shader_id);
            }
        }
        else {

            logger.error("An error occurred while creating shader: %s.", gl_error());
        }
    }
    else {
        
       logger.error("Shader input may not be NULL."); 
    }
    
    return shader_id;
}

/*
 * Remove the shader with the given ID from the program.
 */
void GLProgram::remove_shader(unsigned int shader_id) {
    
    // only try to remove the shader if we are in fact in possession of it
    if(glIsShader(shader_id)) {
        
        glDetachShader(this->prog_id, shader_id);
        glDeleteShader(shader_id);
        
        logger.debug("Shader %u was removed from program %u.", shader_id, this->prog_id);
    }
}

/*
 * Bind a vertex attribute.
 */
void GLProgram::bind_attrib(AttrPos position, const char *const name) {
    
    glBindAttribLocation(this->prog_id, position, name);
}

/*
 * Set the value for a uniform variable.
 */
void GLProgram::uniform(UniformType type, const char *const name, ...) {

    bind();

    int location = glGetUniformLocation(this->prog_id, name);
    
    va_list argList;
    va_start(argList, name);
    
    if(type == FL1) {
        
        float v0 = va_arg(argList, float);
        
        glUniform1f(location, v0);
    }
    else if(type == FL2) {
        
        float v0 = va_arg(argList, float);
        float v1 = va_arg(argList, float);
        
        glUniform2f(location, v0, v1);
    }
    else if(type == FL3) {
        
        float v0 = va_arg(argList, float);
        float v1 = va_arg(argList, float);
        float v2 = va_arg(argList, float);
        
        glUniform3f(location, v0, v1, v2);
    }
    else if(type == FL4) {
        
        float v0 = va_arg(argList, float);
        float v1 = va_arg(argList, float);
        float v2 = va_arg(argList, float);
        float v3 = va_arg(argList, float);
        
        glUniform4f(location, v0, v1, v2, v3);
    }
    else if(type == IN1) {
        
        int v0 = va_arg(argList, int);
        
        glUniform1i(location, v0);
    }
    else if(type == IN2) {
        
        int v0 = va_arg(argList, int);
        int v1 = va_arg(argList, int);
        
        glUniform2i(location, v0, v1);
    }
    else if(type == IN3) {
        
        int v0 = va_arg(argList, int);
        int v1 = va_arg(argList, int);
        int v2 = va_arg(argList, int);
        
        glUniform3i(location, v0, v1, v2);
    }
    else if(type == IN4) {
        
        int v0 = va_arg(argList, int);
        int v1 = va_arg(argList, int);
        int v2 = va_arg(argList, int);
        int v3 = va_arg(argList, int);
        
        glUniform4i(location, v0, v1, v2, v3);
    }
    else if(type == UI1) {
        
        unsigned int v0 = va_arg(argList, unsigned int);
        
        glUniform1ui(location, v0);
    }
    else if(type == UI2) {
        
        unsigned int v0 = va_arg(argList, unsigned int);
        unsigned int v1 = va_arg(argList, unsigned int);
        
        glUniform2ui(location, v0, v1);
    }
    else if(type == UI3) {
        
        unsigned int v0 = va_arg(argList, unsigned int);
        unsigned int v1 = va_arg(argList, unsigned int);
        unsigned int v2 = va_arg(argList, unsigned int);
        
        glUniform3ui(location, v0, v1, v2);
    }
    else if(type == UI4) {
        
        unsigned int v0 = va_arg(argList, unsigned int);
        unsigned int v1 = va_arg(argList, unsigned int);
        unsigned int v2 = va_arg(argList, unsigned int);
        unsigned int v3 = va_arg(argList, unsigned int);
        
        glUniform4ui(location, v0, v1, v2, v3);
    }
    else if(type == FLV1 || type == FLV2 || type == FLV3 || type == FLV4) {
        
        int count = va_arg(argList, int);
        float *value = va_arg(argList, float *);
        
        switch(type) {
            
            case FLV1:
                glUniform1fv(location, count, value); break;
            case FLV2:
                glUniform2fv(location, count, value); break;
            case FLV3:
                glUniform3fv(location, count, value); break;
            case FLV4:
                glUniform4fv(location, count, value); break;
            default:
                break;
        }
    }
    else if(type == INV1 || type == INV2 || type == INV3 || type == INV4) {
        
        int count = va_arg(argList, int);
        int *value = va_arg(argList, int *);
        
        switch(type) {
            
            case FLV1:
                glUniform1iv(location, count, value); break;
            case FLV2:
                glUniform2iv(location, count, value); break;
            case FLV3:
                glUniform3iv(location, count, value); break;
            case FLV4:
                glUniform4iv(location, count, value); break;
            default:
                break;
        }
    }
    else if(type == UIV1 || type == UIV2 || type == UIV3 || type == UIV4) {
        
        int count = va_arg(argList, int);
        unsigned int *value = va_arg(argList, unsigned int *);
        
        switch(type) {
            
            case FLV1:
                glUniform1uiv(location, count, value); break;
            case FLV2:
                glUniform2uiv(location, count, value); break;
            case FLV3:
                glUniform3uiv(location, count, value); break;
            case FLV4:
                glUniform4uiv(location, count, value); break;
            default:
                break;
        }
    }
    else if(type == MAT2 || type == MAT3 || type == MAT4 || type == MAT23 || type == MAT24 || type == MAT32 || type == MAT34 || type == MAT42 || type == MAT43) {
        
        int count = va_arg(argList, int);
        bool transpose = va_arg(argList, int);
        float *value = va_arg(argList, float *);
        
        switch(type) {
            
            case MAT2:
                glUniformMatrix2fv(location, count, transpose, value); break;
            case MAT3:
                glUniformMatrix3fv(location, count, transpose, value); break;
            case MAT4:
                glUniformMatrix4fv(location, count, transpose, value); break;
            case MAT23:
                glUniformMatrix2x3fv(location, count, transpose, value); break;
            case MAT24:
                glUniformMatrix2x4fv(location, count, transpose, value); break;
            case MAT32:
                glUniformMatrix3x2fv(location, count, transpose, value); break;
            case MAT34:
                glUniformMatrix3x4fv(location, count, transpose, value); break;
            case MAT42:
                glUniformMatrix4x2fv(location, count, transpose, value); break;
            case MAT43:
                glUniformMatrix4x3fv(location, count, transpose, value); break;
            default:
                break;
        }
    }
    else {
        
        logger.error("Cannot bind uniform: unknown type.");
    }
    
    va_end(argList);

    unbind();
}

/*
 * Bind vertex attribute locations, link the program, and validate it.
 */
bool GLProgram::finalize() {
    
    glLinkProgram(this->prog_id);
    
    return validate_program();
}

/*
 * Set this program to be the one in current use.
 */
void GLProgram::bind() {

    glGetIntegerv(GL_CURRENT_PROGRAM, (int *)&this->last_id);
    glUseProgram(this->prog_id);
}

/*
 * Set the program to be the last known bound program.
 */
void GLProgram::unbind() {
    
    glUseProgram(this->last_id);
}
