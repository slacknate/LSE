#include <cstdlib>
#include <iostream>
#include <cmath>
#include <signal.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <sdl/sdl.h>

#ifdef WIN32
#include <windows.h>
#include <wincrypt.h>
#endif

#include "include/util/terrain/2D.h"
#include "include/util/terrain/3D.h"

#define PI 3.14159265359f

bool quit = false;
float posX = 0.0, posY = 0.0, posZ = -2.0;
float rotX = 0.0, rotY = 0.0, rotZ = 0.0;

void GLInit() {
            
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
    
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);    
    glViewport(0, 0, 639, 479);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(90.0, 640.0/480.0, -1.0, 1.0);
    //gluLookAt(posX, posY, posZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glMatrixMode(GL_MODELVIEW);
}

void ReadRandom(void *ptr, int numBytes) {
    
    if(ptr != NULL) {
    
        #ifdef WIN32
        HCRYPTPROV var;
        CryptAcquireContext(&var, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
        CryptGenRandom(var, numBytes, (unsigned char *)ptr);
        #else
        FILE *ranSrc = fopen("/dev/urandom", "r");
        if(ranSrc != NULL) {
        
            fread(&rand, numBytes, 1, ranSrc);
            fclose(ranSrc);
        }
        #endif
    }
    else {
        
        
    }
}

void segfault(int signum) {
    
    printf("segfault!\n");
    system("pause");
    exit(signum);
}

int main(int argc, char *argv[]) {
    
    signal(SIGSEGV, segfault);
    
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        
        SDL_WM_SetCaption("tgen", NULL);  
        int width = 640;
        int height = 480;
        int depth = 128;
        unsigned int flags = SDL_OPENGL | /*SDL_RESIZABLE |*/ SDL_HWSURFACE | SDL_DOUBLEBUF;
        SDL_Surface *canvas = SDL_SetVideoMode(640, 480, 32, flags);
        if(canvas != NULL) {
            
            SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
            SDL_EnableUNICODE(true);
            
            if(glewInit() == GLEW_OK) {
                 
                GLInit();
                
                unsigned int random = 0;
                ReadRandom(&random, sizeof(unsigned int));
                random %= RAND_MAX;
                //Terrain3D points = GenTerrain3D(random, 0.0, 0.0, 0.0, width, height, depth, -1.0, 1.0);
                Terrain2D points = GenTerrain2D(random, 0.0, 0.0, width, height, 0.0, 1.0);
                
                while(!quit) {
                    
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                    glLoadIdentity();
                    
                    /*SDL_Event event;
                    if(SDL_PollEvent(&event)) {
                        
                        if(event.type == SDL_QUIT) {
                            
                            quit = true;
                        }
                        else if(event.type == SDL_MOUSEMOTION) {
                            
                            rotX += event.motion.xrel;
                            rotZ += event.motion.yrel;
                        }
                        else if(event.type == SDL_KEYDOWN) {
                            
                            if(event.key.keysym.unicode == 'w') {
                
                                posZ += 0.1;
                            }
                            else if(event.key.keysym.unicode == 'a') {
                
                                posX -= 0.1;
                            }
                            else if(event.key.keysym.unicode == 's') {
                
                                posZ -= 0.1;
                            }
                            else if(event.key.keysym.unicode == 'd') {
                
                                posX += 0.1;
                            }
                            else if(event.key.keysym.unicode == 'q') {
                
                                posY += 0.1;
                            }
                            else if(event.key.keysym.unicode == 'z') {
                
                                posY -= 0.1;
                            }
                        }
                    }
                    
                    gluLookAt(posX, posY, posZ, posX+cos(PI/180.0*rotX), posY, posZ+sin(PI/180.0*rotZ), 0.0, 1.0, 0.0);
                    
                    for(int w = 0; w < width; ++w) {
                        
                        for(int h = 0; h < height; ++h) {
                            
                            //for(int d = 0; d < depth; ++d) {                            
                                
                                //if(points[w][h][d] >= 0.0) {
                                    
                                    glColor3f(1.0, 1.0, 1.0);
                                    glVertex3f(float(w), 0.0, float(h));
                                //}
                            //}
                        }
                    }*/
                    
                    gluOrtho2D(0, width-1, height-1, 0);
                    
                    glBegin(GL_POINTS);
                    for(int w = 0; w < width; ++w) {
                        
                        for(int h = 0; h < height; ++h) {
                            
                            glColor3f(points[w][h], points[w][h], points[w][h]);
                            glVertex2f(float(w), float(h));
                        }
                    }
                    glEnd();
                    
                    SDL_GL_SwapBuffers();
                    SDL_PumpEvents();
                }
            }
            else {
        
                printf("Failed to initialize GLEW.\n");
            }
        }
        else {
                    
            printf("Failed to create SDL canvas.\n");
        }
    }
    else {
                
        printf("Failed to initialize SDL.\n");
    }
    
    return 0;
}
