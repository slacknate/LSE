#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

/*
Directory structure character/string
*/
#ifdef WIN32
#define DIR_CHR                 '\\'
#define DIR_STR                 "\\"
#else
#define DIR_CHR                 '/'
#define DIR_STR                 "/"
#endif


const char const SHADER_INCLUDE_B[] = "#include \"";

const char const SHADER_INCLUDE_E[] = "\"\n\n";

const char *const SHADER_COMMENTS[] = {
    
    "\0", // invalid
    
    "/*\nBuilt in vertex shader for LSE.\n*/\n",
    
    "/*\nBuilt in tesselation control shader for LSE.\n*/\n",
    
    "/*\nBuilt in tesselation evaluation shader for LSE.\n*/\n",
    
    "/*\nBuilt in geometry shader for LSE.\n*/\n",
    
    "/*\nBuilt in fragment shader for LSE.\n*/\n",
};

const char *const SHADER_ARRAY_DECL[] = {
    
    "\0", // invalid
    
    "static const char VERTEX_SHADER[] = {\n",
    
    "static const char TESS_CONTROL_SHADER[] = {\n",
    
    "static const char TESS_EVAL_SHADER[] = {\n",
    
    "static const char GEOMETRY_SHADER[] = {\n",
    
    "static const char FRAGMENT_SHADER[] = {\n"
};

const char const SHADER_ARRAY_CLOSE[] = "\n};\n\n";

const char const ARRAY_OF_SHADERS[] = "/*\nArray of all built in LSE Shaders.\n\
*/\nstatic const char *const SHADERS[] = {\n\
\n\
\t\"Invalid\\0\",\n\
\tVERTEX_SHADER,\n\
\tTESS_CONTROL_SHADER,\n\
\tTESS_EVAL_SHADER,\n\
\tGEOMETRY_SHADER,\n\
\tFRAGMENT_SHADER\n\
};\n\n";

const char const SHADER_GET_FUNC_B[] = "/*\n\
Get the shader of the specified type.\n\
This function is used to obtain the shaders\n\
built into the engine.\n\
*/\n\
const char* ";

const char const SHADER_GET_FUNC_E[] = "(ShaderType type) {\n\
    \n\
    if(VALID_SHADER_TYPE(type))\n\
        return SHADERS[type];\n\
    \n\
    ERROR_LOG(\"Invalid Shader type.\");\n\
    return NULL;\n\
}\n";

const char const SHADER_HEADER_B[] = "#include \"Defs.h\"\n\nconst char* ";

const char const SHADER_HEADER_E[] = "(ShaderType type);\n\n#endif\n";

void WriteShader(char *fileName, FILE *shaderArrayFile) {
    
    printf("Opening shader file \"%s\"\n", fileName);
    FILE *shaderFile = fopen(fileName, "rb");
    if(shaderFile != NULL) {    
        
        fseek(shaderFile, 0, SEEK_END);
        int size = ftell(shaderFile);
        rewind(shaderFile);
        
        char shaderText[size];
        fread(shaderText, sizeof(char), size, shaderFile);
        
        fclose(shaderFile);
        shaderFile = NULL;
        
        int newSize = 3*size;
        char shaderArray[newSize];
        memset(shaderArray, 0, newSize);
        
        if(shaderArrayFile) {

            int i;
            for(i = 0; i < size; ++i) {
                
                // newline and indent after reading 10 characters
                if(i % 10 == 0)
                    fprintf(shaderArrayFile, "\n\t");
                
                // print the current character in hex
                fprintf(shaderArrayFile, "0x%02X, ", shaderText[i]);
            }
            
            // NULL terminate the array
            fprintf(shaderArrayFile, "0x%02X", 0);
        }
        else {
            
            printf("Cannot pass NULL file handle to WriteShader().\n");
        }
    }
    else {
        
        perror("Could not open shader file");
    }
}

/*
Return the shader type, given the file name.
*/
int ShaderType(const char *fileName) {
    
    int type = 0;
    
    int hasExtension = 0;
    char *extension = NULL;
    int extLength = 0;
        
    // check for the shader file extension
    int ext;
    for(ext = 0; ext < strlen(fileName) && !hasExtension; ++ext) {
        
        if(fileName[ext] == '.')
            hasExtension = 1;
    }
       
    if(hasExtension) {
            
        extLength = strlen(fileName) - ext;
        extension = malloc(extLength+1);
    }
    
    if(extension) {
            
        strncpy(extension, &fileName[ext], extLength);
        extension[extLength] = '\0';
            
        // determine the shader type
        if(!strcmp(extension, "vert"))
            type = 1;
        else if(!strcmp(extension, "tcon"))
            type = 2;
        else if(!strcmp(extension, "teva"))
            type = 3;
        else if(!strcmp(extension, "geom"))
            type = 4;
        else if(!strcmp(extension, "frag"))
            type = 5;
        else
            printf("Unknown file extension \"%s\". Unable to determine OpenGL shader type.\n", extension);
            
        free(extension);
    }
    else {
            
        printf("No shader file extension found for \"%s\". Unable to determine OpenGL shader type.\n", fileName);
    }
        
    return type;
}

/*
Check of a character is lower case.
*/
int IsLowerCase(char c) {
    
    return (c > 96 && c < 123);
}

/*
Check if a character is upper case.
*/
int IsUpperCase(char c) {
    
    return (c > 64 && c < 91);
}

/*
Capitalize a string.
*/
void Capitalize(char *s) {
    
    if(s != NULL) {
        
        int i;
        for(i = 0; i < strlen(s); ++i) {
            
            if(IsLowerCase(s[i]))
                s[i] -= 32;
        }
    }
}

int main(int argc, char *argv[]) {
    
    // print out how to use this program if no arguments supplied
    if(argc < 4) {
        
        printf("usage: ShaderDump src-directory name cpp-dest-directory h-dest-directory\n");
    }
    else {
        
        printf("Opening directory \"%s\"\n", argv[1]);
        
        // try to open up a directory with the given name
        DIR *dir;
        struct dirent *ent;
        if((dir = opendir(argv[1])) != NULL) {
            
            // open our dump files in the correct locations before reading shader files
            char destCppFile[strlen(argv[3]) + strlen(argv[2]) + 8];
            strcpy(destCppFile, argv[3]);
            strcat(destCppFile, DIR_STR);
            strcat(destCppFile, "");
            strcat(destCppFile, argv[2]);
            strcat(destCppFile, ".cpp");
            FILE *shaderArrayFile = fopen(destCppFile, "wb");
            
            char destHFile[strlen(argv[4]) + strlen(argv[2]) + 6];
            strcpy(destHFile, argv[4]);
            strcat(destHFile, DIR_STR);
            strcat(destHFile, "");
            strcat(destHFile, argv[2]);
            strcat(destHFile, ".h");
            FILE *shaderArrayHeader = fopen(destHFile, "wb");
            if(shaderArrayFile && shaderArrayHeader) {
            
                // if the directory was found and we opened our dump files, change current working directory
                chdir(argv[1]);
                
                // write out the include directive
                fprintf(shaderArrayFile, "%s", SHADER_INCLUDE_B);
                fprintf(shaderArrayFile, "%s.h", argv[2]);
                fprintf(shaderArrayFile, "%s", SHADER_INCLUDE_E);
                
                // skip over the special directory entries . and ..
                while((ent = readdir(dir)) != NULL && (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, "..")));
                int dirStartPos = telldir(dir) - 1;
                seekdir(dir, dirStartPos);
                
                // dump each shader type to the cpp file
                int i;
                for(i = 1; i < 6; ++i) {
                    
                    // write out array declaration and related comments
                    fprintf(shaderArrayFile, "%s", SHADER_COMMENTS[i]);
                    fprintf(shaderArrayFile, "%s", SHADER_ARRAY_DECL[i]);
                    
                    // look for a shader of the correct type
                    int found = 0;
                    while(!found && (ent = readdir(dir)) != NULL) { 
                        
                        DIR *dirTest;
                        if((dirTest = opendir(ent->d_name)) == NULL && !strncmp(ent->d_name, argv[2], strlen(argv[2])) && ShaderType(ent->d_name) == i)
                            found = 1;
                    }
                    
                    // if the shader exists, read the file, hex dump it, and write it out
                    // otherwise set the array to zero
                    if(ent != NULL)
                        WriteShader(ent->d_name, shaderArrayFile);
                    else
                        fprintf(shaderArrayFile, "\n\t0x%02X", 0);
                    
                    // write out array close brace
                    fprintf(shaderArrayFile, "%s", SHADER_ARRAY_CLOSE);
                    
                    // seek back to the beginning of the list
                    seekdir(dir, dirStartPos);
                }
                
                // write out an array of all the shader arrays
                fprintf(shaderArrayFile, "%s", ARRAY_OF_SHADERS);
                
                // create the name for the shader get function
                char getFunction[strlen(argv[2]) + 8];
                memset(getFunction, 0, strlen(argv[2]) + 8);
                
                strcpy(getFunction, "Get");
                strcat(getFunction, argv[2]);
                
                // write out a get function to obtain the arrays
                fprintf(shaderArrayFile, "%s", SHADER_GET_FUNC_B);
                fprintf(shaderArrayFile, "%s", getFunction);
                fprintf(shaderArrayFile, "%s", SHADER_GET_FUNC_E);
                
                fclose(shaderArrayFile);
                shaderArrayFile = NULL;
                
                // create the inclusion guard for the header
                char includeGuard[strlen(argv[2]) + 7];
                memset(includeGuard, 0, strlen(argv[2]) + 7);
                
                strcpy(includeGuard, "");
                strcat(includeGuard, argv[2]);
                strcat(includeGuard, "_H");
                
                Capitalize(includeGuard);
                
                fprintf(shaderArrayHeader, "#ifndef ");
                fprintf(shaderArrayHeader, "%s\n", includeGuard);
                fprintf(shaderArrayHeader, "#define ");
                fprintf(shaderArrayHeader, "%s\n\n", includeGuard);
                
                // create a header file to access the get function
                fprintf(shaderArrayHeader, "%s", SHADER_HEADER_B);
                
                fprintf(shaderArrayHeader, "%s", getFunction);
                
                fprintf(shaderArrayHeader, "%s", SHADER_HEADER_E);
                
                fclose(shaderArrayHeader);
                shaderArrayHeader = NULL;
            }
            else {
            
                perror("Could not create source and/or header file(s)");
            }
        }
        else {
            
            perror("Could not open directory");
        }
    }
    
    system("pause");	
    return 0;
}
