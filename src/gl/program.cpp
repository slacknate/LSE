#include <cstdarg>
#include "gl/program.h"

/*
Generate out OpenGL program.
*/
LSE_GLProgram::LSE_GLProgram() {
    
    lastID = 0;
    progID = glCreateProgram();
}

/*
Detach and delete all attached shaders,
as well as the program.
*/
LSE_GLProgram::~LSE_GLProgram() {
    
    for(int i = 0; i < shaderIDs.Size(); ++i)
        RemoveShader(*(unsigned int *)shaderIDs[i]->GetData());
    
    shaderIDs.Clear();
    
    glDeleteProgram(progID);
}

/*
Read in the shader source file. Return a NULL
pointer if there were errors. On success, the
contents of the shader file are returned,
and the caller is responsible for freeing
the memory.
*/
char* LSE_GLProgram::ReadShader(const char *fileName) {
    
    char *shaderSource = NULL;
    
    FILE *shader = fopen(fileName, "rb");
    if(shader) {          
        
        // get shader source file size
        fseek (shader, 0, SEEK_END);
        int fileSize = ftell(shader);
        rewind(shader);
        
        shaderSource = new (std::nothrow) char [fileSize+1];
        if(shaderSource) {
            
            fread(shaderSource, sizeof(char), fileSize, shader);
            shaderSource[fileSize] = '\0'; // explicitly null terminate for safety with glShaderSource()
            
            if(ferror(shader)) {
                
                delete[] shaderSource;
                shaderSource = NULL;
                
                LSE_ERROR_LOG("An error occurred while reading the shader source.");
            }
        }
        else {
            
            LSE_ERROR_LOG("Failed to allocate memory for shader source.");
        }
    }
    else {
            
        LSE_ERROR_LOG("Shader source file unable to be read.");
    }
    
    return shaderSource;
}

/*
Get the shader type from the file extension.
*/
GLenum LSE_GLProgram::ShaderType(const char *fileName) {
    
    GLenum type = 0; // fix me -> check to make sure this is indeed an invalid value
    
    bool hasExtension = false;
    char *extension = NULL;
    int extLength = 0;
        
    // check for the shader file extension
    int ext;
    for(ext = 0; ext < strlen(fileName) && !hasExtension; ++ext) {
        
        if(fileName[ext] == '.')
            hasExtension = true;
    }
       
    if(hasExtension) {
            
        extLength = strlen(fileName) - ext;
        extension = new (std::nothrow) char [extLength+1];
    }
    
    if(extension) {
            
        strncpy(extension, &fileName[ext], extLength);
        extension[extLength] = '\0';
            
        // determine the shader type
        if(!strcmp(extension, "vert"))
            type = GL_VERTEX_SHADER;
        else if(!strcmp(extension, "tcon"))
            type = GL_TESS_CONTROL_SHADER;
        else if(!strcmp(extension, "teva"))
            type = GL_TESS_EVALUATION_SHADER;
        else if(!strcmp(extension, "geom"))
            type = GL_GEOMETRY_SHADER;
        else if(!strcmp(extension, "frag"))
            type = GL_FRAGMENT_SHADER;
        else
            LSE_ERROR_LOG("Unknown file extension. Unable to determine OpenGL shader type.");
            
        delete[] extension;   
    }
    else {
            
        LSE_ERROR_LOG("No shader file extension found. Unable to determine OpenGL shader type.");
    }
        
    return type;
}

/*
Get the OpenGL shader type from the LSE shader type.
*/
GLenum LSE_GLProgram::ShaderType(LSE_ShaderType lseType) {
    
    GLenum glType = 0; // fix me -> check to make sure this is indeed an invalid value
    
    if(lseType == SHADER_VERT)
        glType = GL_VERTEX_SHADER;
    else if(lseType == SHADER_TCON)
        glType = GL_TESS_CONTROL_SHADER;
    else if(lseType == SHADER_TEVA)
        glType = GL_TESS_EVALUATION_SHADER;
    else if(lseType == SHADER_GEOM)
        glType = GL_GEOMETRY_SHADER;
    else if(lseType == SHADER_FRAG)
        glType = GL_FRAGMENT_SHADER;
    else
        LSE_ERROR_LOG("Invalid LSE_Shader type. Unable to determine OpenGL shader type.");
    
    return glType;
}

/*
Check if the shader attached to the given ID is valid.
*/
bool LSE_GLProgram::ValidateShader(const char *fileName, unsigned int shaderID, LSE_ShaderType lseType) {
    
    int buffSize = 0;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &buffSize);
    if(buffSize > 0) {
                    
        char buffer[buffSize];
        memset(buffer, 0, buffSize);
        glGetShaderInfoLog(shaderID, buffSize, &buffSize, buffer);
        if(!strcmp(buffer, "No errors.\n") || !strcmp(buffer, "")) { // might need to add more here for compatibility
            
            return true;
        }
        else {
            
            if(lseType == SHADER_INVALID)
                LSE_ERROR_LOG("Shader read from \"%s\" failed validation:\n%s", fileName, buffer);
            else
                LSE_ERROR_LOG("%s shader read from stream failed validation:\n%s", LSE_ShaderString(lseType), buffer);
        }
    }
    else {
                    
        LSE_ERROR_LOG("An error occurred while obtaining the shader log.");
    }
    
    return false;
}

/*
Check if the whole program is valid.
*/
bool LSE_GLProgram::ValidateProgram() {
    
    glValidateProgram(progID);
    
    int success = false;
    glGetProgramiv(progID, GL_VALIDATE_STATUS, &success);
    
    return success;
}

/*
Add a new shader to the program.
If the shader type parameter is SHADER_INVALID,
the provided buffer is assumed to be a file name,
and the method attempts to open the file, read it,
and pass the read text to the shader compiler.
Otherwise, the buffer is treated as the shader source,
and the method passes the text to the shader compiler.
*/
int LSE_GLProgram::AddShader(const char *buffer, LSE_ShaderType lseType) {
    
    unsigned int shaderID = 0;
    
    if(buffer) {
        
        if(lseType == SHADER_INVALID) {
        
            char *shaderSource = ReadShader(buffer);
            if(shaderSource) {
            
                shaderID = glCreateShader(ShaderType(buffer));
                if(shaderID) {
                    
                    int size[] = { 9, strlen(LSE_GL_VERSION_STR), 1, strlen(shaderSource) };
                    const char *const sourceWithVersion[] = { "#version ", LSE_SL_VERSION_STR, "\n", shaderSource };
                    
                    // send the shader source code to the GPU, and compile it
                    glShaderSource(shaderID, 4, (const char**)sourceWithVersion, size);
                    glCompileShader(shaderID);
                        
                    if(ValidateShader(buffer, shaderID, lseType)) {
                    
                        // attach the compiled shader to the program, and store the shader ID in our list
                        glAttachShader(progID, shaderID);
                        
                        unsigned int *newID = new (std::nothrow) unsigned int;
                        if(newID != NULL) {
                            
                            *newID = shaderID;
                            shaderIDs.PushBack(newID);
                            
                            LSE_MESSG_LOG(LOG_LEVEL_DEBUG, "Shader file \"%s\" bound to ID %u and attached to program %u.", buffer, shaderID, progID);
                        }
                        else {
                            
                            LSE_ERROR_LOG("Failed to allocate memory for element in shader ID list.");
                            glDeleteShader(shaderID);
                        }
                    }
                    else {
                    
                        glDeleteShader(shaderID);
                    }
                }
                else {
                        
                    int error = glGetError();
                    if(error)
                        LSE_ERROR_LOG("An error occurred while creating shader from \"%s\": %s.", buffer, LSE_GLErrorString(error));
                    else
                        LSE_ERROR_LOG("An unknown error occurred while creating shader from \"%s.\"", buffer);
                }
            
                delete[] shaderSource;
                shaderSource = NULL;
            }
        }
        else {
            
            shaderID = glCreateShader(ShaderType(lseType));
            if(shaderID) {
                
                int size[] = { 9, strlen(LSE_GL_VERSION_STR), 1, strlen(buffer) };
                const char *const sourceWithVersion[] = { "#version ", LSE_SL_VERSION_STR, "\n", buffer };
                
                // send the shader source code to the GPU, and compile it
                glShaderSource(shaderID, 4, (const char**)sourceWithVersion, size);
                glCompileShader(shaderID);
                        
                if(ValidateShader(NULL, shaderID, lseType)) {
                    
                    // attach the compiled shader to the program, and store the shader ID in our list
                    glAttachShader(progID, shaderID);    
                    
                    unsigned int *newID = new (std::nothrow) unsigned int;
                    if(newID != NULL) {
                            
                        *newID = shaderID;
                        shaderIDs.PushBack(newID);
                            
                        LSE_MESSG_LOG(LOG_LEVEL_DEBUG, "%s shader loaded from stream bound to ID %u and attached to program %u.", LSE_ShaderString(lseType), shaderID, progID);
                    }
                    else {
                            
                        LSE_ERROR_LOG("Failed to allocate memory for element in shader ID list.");
                        glDeleteShader(shaderID);
                    }
                }
                else {
                    
                    glDeleteShader(shaderID);
                }
            }
            else {
                        
                int error = glGetError();
                if(error)
                    LSE_ERROR_LOG("An error occurred while creating shader from \"%s\": %s.", buffer, LSE_GLErrorString(error));
                else
                    LSE_ERROR_LOG("An unknown error occurred while creating shader from \"%s.\"", buffer);
            }
        }
    }
    else {
        
       LSE_ERROR_LOG("Shader input may not be NULL."); 
    }
    
    return shaderID;
}

/*
Remove the shader with the given ID from the program.
*/
bool LSE_GLProgram::RemoveShader(unsigned int shaderID) {
    
    // make sure the given shader is in the list of shaders present in this program
    bool valid = false;
    for(int i = 0; i < shaderIDs.Size() && !valid; ++i) {
        
        if(*(unsigned int*)shaderIDs[i]->GetData() == shaderID)
            valid = true;
    }
    
    // only try to remove the shader if we are in fact in possession of it
    if(valid) {
        
        glDetachShader(progID, shaderID);
        glDeleteShader(shaderID);
        
        LSE_MESSG_LOG(LOG_LEVEL_DEBUG, "Shader %u was removed from program %u.", shaderID, progID);
    }
    
    return valid;
}

/*
Bind a vertex attribute.
*/
void LSE_GLProgram::BindAttrib(unsigned int position, const char *const name) {
    
    glBindAttribLocation(progID, position, name);
}

/*
Bind a uniform variable.
*/
void LSE_GLProgram::BindUniform(unsigned int type, const char *const name, ...) {
    
    Bind();
    
    unsigned int location = glGetUniformLocation(progID, name);
    
    va_list argList;
    va_start(argList, name);
    
    if(type == LSE_FL1) {
        
        float v0 = va_arg(argList, double);
        
        glUniform1f(location, v0);
    }
    else if(type == LSE_FL2) {
        
        float v0 = va_arg(argList, double);
        float v1 = va_arg(argList, double);
        
        glUniform2f(location, v0, v1);
    }
    else if(type == LSE_FL3) {
        
        float v0 = va_arg(argList, double);
        float v1 = va_arg(argList, double);
        float v2 = va_arg(argList, double);
        
        glUniform3f(location, v0, v1, v2);
    }
    else if(type == LSE_FL4) {
        
        float v0 = va_arg(argList, double);
        float v1 = va_arg(argList, double);
        float v2 = va_arg(argList, double);
        float v3 = va_arg(argList, double);
        
        glUniform4f(location, v0, v1, v2, v3);
    }
    else if(type == LSE_IN1) {
        
        int v0 = va_arg(argList, int);
        
        glUniform1i(location, v0);
    }
    else if(type == LSE_IN2) {
        
        int v0 = va_arg(argList, int);
        int v1 = va_arg(argList, int);
        
        glUniform2i(location, v0, v1);
    }
    else if(type == LSE_IN3) {
        
        int v0 = va_arg(argList, int);
        int v1 = va_arg(argList, int);
        int v2 = va_arg(argList, int);
        
        glUniform3i(location, v0, v1, v2);
    }
    else if(type == LSE_IN4) {
        
        int v0 = va_arg(argList, int);
        int v1 = va_arg(argList, int);
        int v2 = va_arg(argList, int);
        int v3 = va_arg(argList, int);
        
        glUniform4i(location, v0, v1, v2, v3);
    }
    else if(type == LSE_UI1) {
        
        unsigned int v0 = va_arg(argList, unsigned int);
        
        glUniform1ui(location, v0);
    }
    else if(type == LSE_UI2) {
        
        unsigned int v0 = va_arg(argList, unsigned int);
        unsigned int v1 = va_arg(argList, unsigned int);
        
        glUniform2ui(location, v0, v1);
    }
    else if(type == LSE_UI3) {
        
        unsigned int v0 = va_arg(argList, unsigned int);
        unsigned int v1 = va_arg(argList, unsigned int);
        unsigned int v2 = va_arg(argList, unsigned int);
        
        glUniform3ui(location, v0, v1, v2);
    }
    else if(type == LSE_UI4) {
        
        unsigned int v0 = va_arg(argList, unsigned int);
        unsigned int v1 = va_arg(argList, unsigned int);
        unsigned int v2 = va_arg(argList, unsigned int);
        unsigned int v3 = va_arg(argList, unsigned int);
        
        glUniform4ui(location, v0, v1, v2, v3);
    }
    else if(type == LSE_FLV1 || type == LSE_FLV2 || type == LSE_FLV3 || type == LSE_FLV4) {
        
        int count = va_arg(argList, int);
        float *value = va_arg(argList, float *);
        
        switch(type) {
            
            case LSE_FLV1:
                glUniform1fv(location, count, value); break;
            case LSE_FLV2:
                glUniform2fv(location, count, value); break;
            case LSE_FLV3:
                glUniform3fv(location, count, value); break;
            case LSE_FLV4:
                glUniform4fv(location, count, value); break;
        }
    }
    else if(type == LSE_INV1 || type == LSE_INV2 || type == LSE_INV3 || type == LSE_INV4) {
        
        int count = va_arg(argList, int);
        int *value = va_arg(argList, int *);
        
        switch(type) {
            
            case LSE_FLV1:
                glUniform1iv(location, count, value); break;
            case LSE_FLV2:
                glUniform2iv(location, count, value); break;
            case LSE_FLV3:
                glUniform3iv(location, count, value); break;
            case LSE_FLV4:
                glUniform4iv(location, count, value); break;
        }
    }
    else if(type == LSE_UIV1 || type == LSE_UIV2 || type == LSE_UIV3 || type == LSE_UIV4) {
        
        int count = va_arg(argList, int);
        unsigned int *value = va_arg(argList, unsigned int *);
        
        switch(type) {
            
            case LSE_FLV1:
                glUniform1uiv(location, count, value); break;
            case LSE_FLV2:
                glUniform2uiv(location, count, value); break;
            case LSE_FLV3:
                glUniform3uiv(location, count, value); break;
            case LSE_FLV4:
                glUniform4uiv(location, count, value); break;
        }
    }
    else if(type == LSE_MAT2 || type == LSE_MAT3 || type == LSE_MAT4 || type == LSE_MAT23 || type == LSE_MAT24 || type == LSE_MAT32 || type == LSE_MAT34 || type == LSE_MAT42 || type == LSE_MAT43) {
        
        int count = va_arg(argList, int);
        bool transpose = va_arg(argList, int);
        float *value = va_arg(argList, float *);
        
        switch(type) {
            
            case LSE_MAT2:
                glUniformMatrix2fv(location, count, transpose, value); break;
            case LSE_MAT3:
                glUniformMatrix3fv(location, count, transpose, value); break;
            case LSE_MAT4:
                glUniformMatrix4fv(location, count, transpose, value); break;
            case LSE_MAT23:
                glUniformMatrix2x3fv(location, count, transpose, value); break;
            case LSE_MAT24:
                glUniformMatrix2x4fv(location, count, transpose, value); break;
            case LSE_MAT32:
                glUniformMatrix3x2fv(location, count, transpose, value); break;
            case LSE_MAT34:
                glUniformMatrix3x4fv(location, count, transpose, value); break;
            case LSE_MAT42:
                glUniformMatrix4x2fv(location, count, transpose, value); break;
            case LSE_MAT43:
                glUniformMatrix4x3fv(location, count, transpose, value); break;
        }
    }
    else {
        
        LSE_ERROR_LOG("Cannot bind uniform: unknown type.");
    }
    
    va_end(argList);
    
    Unbind();
}

/*
Bind vertex attribute locations, link the program,
and validate it.
*/
bool LSE_GLProgram::Finalize() {
    
    glLinkProgram(progID);
    
    return ValidateProgram();
}

/*
Set this program to be the one in current use.
*/
void LSE_GLProgram::Bind() {
    
    glGetIntegerv(GL_CURRENT_PROGRAM, (int*)&lastID);
    glUseProgram(progID);
}

/*
Set the "invalid" program to be the one in current use.
*/
void LSE_GLProgram::Unbind() {
    
    glUseProgram(lastID);
}
