#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

/*
 * Directory delimiter character/string.
 */
#ifdef WIN32
#define DIR_CHR                 '\\'
#define DIR_STR                 "\\"
#else
#define DIR_CHR                 '/'
#define DIR_STR                 "/"
#endif

/*
 * Shader type constants.
 */
enum ShaderType {

    NOT_SHADER = 0,

    SHADER_VERT,
    SHADER_TCON,
    SHADER_TEVA,
    SHADER_GEOM,
    SHADER_FRAG,
};


/*
 * Shader type names in upper-case.
 */
const char *const SHADER_NAMES_UPPER[] = {

    "NOT_SHADER",

    "VERT",
    "TCON",
    "TEVA",
    "GEOM",
    "FRAG",
};


/*
 * Shader type names in lower-case.
 */
const char *const SHADER_NAMES_LOWER[] = {

        "not_shader",

        "vert",
        "tcon",
        "teva",
        "geom",
        "frag",
};


const char *const HEADER_FMT_TOP = "#ifndef LSE_%s_%s_SHADER_H\n"
                                   "#define LSE_%s_%s_SHADER_H\n\n"
                                   "/*\n"
                                   " * Auto generated with sdump on %s.\n"
                                   " */\n\n"
                                   "namespace LSE {\n\n\n"
                                   "const char %s_SHADER[] = {\n\n";


const char *const HEADER_FMT_BOT = "\n\n};\n\n\n"
                                   "}\n\n"
                                   "#endif\n";


/*
 * Get the name of a while without
 * the file extension.
 */
void get_base_name(char *base_name) {

    char *remaining = base_name;
    char *ext_ptr = NULL;

    while(1) {

        ext_ptr = strchr(remaining, '.');

        if(ext_ptr != NULL)
            remaining = ext_ptr + 1;

        else
            break;
    }

    /*
     * Truncate the file name where the extension delimiter is.
     */
    unsigned int ext_index = (unsigned int)(remaining - base_name - 1);
    base_name[ext_index] = '\0';
}



/*
 * Return the shader type given the file name.
 * The type is determined by the file extension.
 * We tokenize the string on the '.' character
 * and use the last tokenized piece as the shader
 * type.
 */
unsigned int get_shader_type(char *file_name) {
    
    unsigned int type = NOT_SHADER;

    char *extension = strtok(file_name, ".");
    while (extension != NULL) {

        if(!strcmp(extension, "vert"))
            type = SHADER_VERT;

        else if(!strcmp(extension, "tcon"))
            type = SHADER_TCON;

        else if(!strcmp(extension, "teva"))
            type = SHADER_TEVA;

        else if(!strcmp(extension, "geom"))
            type = SHADER_GEOM;

        else if(!strcmp(extension, "frag"))
            type = SHADER_FRAG;

        extension = strtok(NULL, ".");
    }
       
    return type;
}


/*
Check of a character is lower case.
*/
int is_lower_case(char c) {
    
    return (c > 96 && c < 123);
}


/*
 * Make a string all upper-case.
 */
void upper(char *string, char *dest) {
    
    if(string != NULL) {

        /*
         * Copy str_len + 1 so we account for the
         * auto NULL termination provided by snprintf.
         */
        size_t str_len = strlen(string);
        snprintf(dest, str_len + 1, "%s", string);

        int i;
        for(i = 0; i < str_len; ++i) {
            
            if(is_lower_case(dest[i]))
                dest[i] -= 32;
        }
    }
}


/*
 * Check if a character is upper case.
 */
int is_upper_case(char c) {

    return (c > 64 && c < 91);
}


/*
 * Make a string all lower-case.
 */
void lower(char *string, char *dest) {

    if(string != NULL) {

        size_t str_len = strlen(string);
        snprintf(dest, str_len, "%s", string);

        int i;
        for(i = 0; i < str_len; ++i) {

            if(is_upper_case(dest[i]))
                dest[i] += 32;
        }
    }
}


void dump_shader(const char *const file_name, FILE *dest_fp) {

    printf("Opening shader file '%s'.\n", file_name);

    FILE *shader_fp = fopen(file_name, "rb");
    if(shader_fp != NULL) {

        /*
         * Get total size of the shader file.
         */
        fseek(shader_fp, 0, SEEK_END);
        size_t file_length = (size_t)ftell(shader_fp);
        rewind(shader_fp);

        /*
         * Array to contain shader data.
         */
        char shader_contents[file_length];

        /*
         * Read the file contents into the array.
         */
        fread(shader_contents, sizeof(char), file_length, shader_fp);

        fclose(shader_fp);
        shader_fp = NULL;

        int i;
        for(i = 0; i < file_length; ++i) {

            /*
             * Newline and indent after reading 10 characters
             */
            if(i % 10 == 0)
                fprintf(dest_fp, "\n\t");

            /*
             * Output the text as hexadecimal.
             */
            fprintf(dest_fp, "0x%02X, ", shader_contents[i]);
        }

        /*
         * NULL terminate the array.
         */
        fprintf(dest_fp, "0x00");
    }
    else {

        perror("Could not open shader file");
    }
}


int main(int argc, char *argv[]) {
    
    if(argc < 1) {
        
        printf("usage: sdump src-directory\n");
    }
    else {
        
        printf("Opening directory '%s'.\n", argv[1]);
        
        /*
         * Open our specified directory.
         */
        DIR *dir = opendir(argv[1]);
        if(dir != NULL) {

            /*
             * Make this directory our CWD so our
             * output files will end up here.
             */
            chdir(argv[1]);

            /*
             * Loop over a listing of the directory.
             */
            struct dirent *ent = NULL;
            while((ent = readdir(dir)) != NULL) {

                /*
                 * Calculate our necessary array length.
                 */
                size_t dn_length = strlen(argv[1]);
                size_t fn_length = strlen(argv[1]);
                size_t fp_length = dn_length + fn_length + 1;

                /*
                 * Build the file full path for use with stat.
                 * Make the array long enough to be null terminated.
                 * Note that snprintf NULL terminates the data for us.
                 */
                char full_path[fp_length + 1];
                snprintf(full_path, fp_length, "%s%s%s", argv[1], DIR_STR, ent->d_name);

                /*
                 * Get the status of the file.
                 */
                struct stat file_stat;
                stat(full_path, &file_stat);

                /*
                 * Check the mode member of the file status struct.
                 * This tells us what type of file the file is.
                 * Skip all directories in the current directory we are reading.
                 */
                if(!S_ISDIR(file_stat.st_mode)) {

                    /*
                     * The strtok call in get_shader_type
                     * in-place substitues '.' with '\0' so
                     * we should copy that string so we do not
                     * modify the stat struct data.
                     */
                    char tokenized_name[64];
                    snprintf(tokenized_name, 64, "%s", ent->d_name);
                    unsigned int shader_type = get_shader_type(tokenized_name);

                    /*
                     * Ensure we only read shader files.
                     */
                    if(shader_type != NOT_SHADER) {

                        printf("Reading shader '%s'.\n", full_path);

                        char base_name[64];
                        snprintf(base_name, 64, "%s", ent->d_name);
                        get_base_name(base_name);
                        if(base_name != NULL) {

                            char file_name[64];
                            snprintf(file_name, 64, "%s%s.h", base_name, SHADER_NAMES_LOWER[shader_type]);

                            /*
                             * Write out our compiled shader to a header.
                             */
                            FILE *header_fp = fopen(file_name, "wb");
                            if(header_fp != NULL) {

                                char obj_name[64];
                                upper(base_name, obj_name);

                                time_t raw_time;
                                time(&raw_time);
                                struct tm *tm_ptr = localtime(&raw_time);

                                char time_str[64];
                                strftime(time_str, 64, "%c", tm_ptr);

                                const char *const shader_type_name = SHADER_NAMES_UPPER[shader_type];

                                fprintf(header_fp, HEADER_FMT_TOP, obj_name, shader_type_name,
                                        obj_name, shader_type_name, time_str, shader_type_name);

                                dump_shader(full_path, header_fp);

                                fprintf(header_fp, HEADER_FMT_BOT);

                                fclose(header_fp);
                            }

                            free(base_name);
                        }
                    }
                }
            }
        }
        else {
            
            perror("Could not open directory");
        }
    }

    return 0;
}
