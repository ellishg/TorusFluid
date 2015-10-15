//
//  OnInit.cpp
//  
//
//  Created by Ellis Sparky Hoag on 6/15/14.
//
//

#include "World.h"


void World::OnRender()   {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glLoadIdentity();
    
    glTranslatef(0, 0, -6);
    
    glRotatef(z_rot, 1, 1, 0);
        
    glBindBuffer(GL_ARRAY_BUFFER, torusVertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torusIndexBufferObject);
    
    glBindTexture(GL_TEXTURE_2D, torusTextureObject);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(GLfloat) * TORUS_VERTEX_STRIDE, (GLvoid *) 0);
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat) * TORUS_VERTEX_STRIDE, (GLvoid *)(sizeof(GLfloat) * 3));
    
    glDrawElements(GL_QUADS, torus->getIndexArrayLength(), GL_UNSIGNED_INT, (GLvoid *) 0);
    //glDrawArrays(GL_POINTS, 0, 3 * numTorusVertices);
    
    glLoadIdentity();
    
    glTranslatef(3, -3, -4);
    
    glBegin(GL_QUADS);
    
        glTexCoord2f(0, 0);
        glVertex3f(-1, -1, 0);
    
        glTexCoord2f(0, 1);
        glVertex3f(-1, 1, 0);
    
        glTexCoord2f(1, 1);
        glVertex3f(1, 1, 0);
    
        glTexCoord2f(1, 0);
        glVertex3f(1, -1, 0);
    
    glEnd();
    
    glDisableClientState(GL_ARRAY_BUFFER);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    SDL_GL_SwapWindow(SDLWindow);
}