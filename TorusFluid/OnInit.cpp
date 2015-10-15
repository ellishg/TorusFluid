//
//  OnInit.cpp
//  
//
//  Created by Ellis Sparky Hoag on 6/15/14.
//
//

#include "World.h"

bool World::OnInit()    {
    
    if (!SDLInit()) {
        std::cout << "Error in SDLInit()\n";
        
        running =  false;
        
        return false;
    }
    
    torus = new Torus(2.5, 1, 50);
    
    //only square grid with power of two works due to textures....for now....
    fluid = new Fluid(64, 64, torus->getOuterRingRadius(), torus->getInnerRingRadius());
    
    
    if (!SDLGLInit()) {
        std::cout << "Error in SDLGLInit()\n";
        
        running = false;
        
        return false;
    }
    
    return true;
}


bool World::SDLInit()   {
    
    if(SDL_Init(SDL_INIT_VIDEO))   {
        printf("Error in SDL_Init(SDL_INIT_VIDEO)!\n");
        
        running = false;
        
        return false;
    }
    
    if((SDLWindow = SDL_CreateWindow("Fluid FPS:", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_OPENGL)) == NULL)   {
        printf("Error in SDL_CreateWindow()!\n");
        
        running = false;
        
        return false;
    }
    
    return true;
}

bool World::SDLGLInit()    {
    
    if ((GLContext = SDL_GL_CreateContext(SDLWindow)) == NULL) {
        printf("Error in SDL_GL_CreateContext()!\n");
        
        running = false;
        
        return false;
    }
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    glFrustum(-1, 1, -1, 1, 1, 20);
    
    glMatrixMode(GL_MODELVIEW);
    
    glClearColor(0.8f, 0.8f, 0.8f, 1);
    
    //glEnable(GL_CULL_FACE);
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_TEXTURE_2D);
    
    
    glGenBuffers(1, &torusVertexBufferObject);
    
    glBindBuffer(GL_ARRAY_BUFFER, torusVertexBufferObject);
    
    glBufferData(GL_ARRAY_BUFFER, torus->getVertexArrayLength() * sizeof(GLfloat), torus->getVertices(), GL_STATIC_DRAW);
    
    
    glGenBuffers(1, &torusIndexBufferObject);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torusIndexBufferObject);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, torus->getIndexArrayLength() * sizeof(GLuint), torus->getIndices(), GL_STATIC_DRAW);
    
    
    torusTextureWidth = 64;
    torusTextureHeight = 64;
    
    torusTextureData = new unsigned char[3 * torusTextureWidth * torusTextureHeight];
    
    
    for (int i = 0; i < 3 * torusTextureWidth * torusTextureHeight; i++) {
        torusTextureData[i] = 0;
    }
    
    glGenTextures(1, &torusTextureObject);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, torusTextureObject);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, torusTextureWidth, torusTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, torusTextureData);
    
    return true;
}