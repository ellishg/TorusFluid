//
//  OnInit.cpp
//  
//
//  Created by Ellis Sparky Hoag on 6/15/14.
//
//

#include "World.h"

void World::OnLoop()    {
    
    z_rot = SDL_GetTicks() / 70.f;
    
    fluid->addFluid(32, 3, 2, 10, Color(255, 0, 0));
    fluid->addFluid(fluid->getGridWidth() / 2, fluid->getGridHeight() - 40, 2, 10, Color(0, 255, 0));
    fluid->addFluid(fluid->getGridWidth() - 20, 20, 2, 10, Color(0, 0, 255));
    
    fluid->addVelocity(32, 32, Vector(0, 1), 2);
    fluid->addVelocity(fluid->getGridWidth() / 2, fluid->getGridHeight() - 20, Vector((rand() % 10 / 10.f) - 0.5f, -1), 2);
    //fluid->addVelocity(fluid->getGridWidth() - 20, 20, Vector(rand() % 10 / -10.f, -1), 2);
    
    fluid->OnLoop();
    
    fluid->prepareRender();
    
    Color * colors = fluid->getColors();
    
    int i, u, v;
    
    for (v = 0; v < torusTextureHeight; v++) {
        
        for (u = 0; u < torusTextureWidth; u++) {
            
            i = u + v * torusTextureWidth;
            
            torusTextureData[3 * i + 0] = colors[i].getRed();
            torusTextureData[3 * i + 1] = colors[i].getGreen();
            torusTextureData[3 * i + 2] = colors[i].getBlue();
            
        }
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, torusTextureWidth, torusTextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, torusTextureData);

}