//
//  World.h
//  
//
//  Created by Ellis Sparky Hoag on 6/15/14.
//
//

#ifndef ____World__
#define ____World__

#define FRAMES_PER_SECOND 60

#define SCREEN_SIZE 600

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "Vector.h"
#include "Color.h"
#include "Fluid.h"
#include "Torus.h"


#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"


enum SIM_MODE{
    WRITE_TO_FILE,
    READ_FILE,
    REALTIME_SIM
};

class World {
    
private:
    
    bool running;
    
    SDL_Window * SDLWindow;
    
    SDL_GLContext GLContext;
    
    SDL_Event Event;
    
    Torus * torus;
    
    Fluid * fluid;
    
    
    GLuint torusVertexBufferObject;
    
    GLuint torusIndexBufferObject;
    
    GLuint torusTextureObject;

    unsigned char * torusTextureData;
    
    int torusTextureWidth;
    
    int torusTextureHeight;
    
    
    GLfloat z_rot;
        
public:
    
    World() : running(true), z_rot(0) {};
        
    bool OnInit();
    
    bool SDLInit();
    
    bool SDLGLInit();
    
    void OnLoop();
    
    void OnRender();
    
    void OnEvent();
    

    void SDLKeyDown(SDL_Keycode sym);
    
    void SDLKeyUp(SDL_Keycode sym);
    
    void SDLMouseEvent(SDL_MouseButtonEvent mouseButton, int x, int y);
    
    void setWindowTitle(const char * title) {SDL_SetWindowTitle(SDLWindow, title);}
    
    bool OnCleanup();
    
    bool isRunning()    {return running;}
};

#endif /* defined(____World__) */
