//
//  OnInit.cpp
//  
//
//  Created by Ellis Sparky Hoag on 6/15/14.
//
//

#include "World.h"

bool World::OnCleanup() {
    
    delete torus;
    
    delete fluid;
    
    glDeleteBuffers(1, &torusVertexBufferObject);
    
    glDeleteBuffers(1, &torusIndexBufferObject);
    
    glDeleteBuffers(1, &torusTextureObject);
    
    delete [] torusTextureData;
    
    SDL_DestroyWindow(SDLWindow);
    
    SDL_GL_DeleteContext(GLContext);
    
    SDL_Quit();

    
    return true;
}