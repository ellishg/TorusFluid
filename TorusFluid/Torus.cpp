//
//  Torus.cpp
//  TorusFluid
//
//  Created by Ellis Sparky Hoag on 10/2/15.
//  Copyright © 2015 Ellis Sparky Hoag. All rights reserved.
//

#include "Torus.h"

Torus::Torus(float _outerRadius, float _innerRadius, int numFacesPerUnit) : outerRingRadius(_outerRadius), innerRingRadius(_innerRadius)/*, scale(1, 1, 1)*/ {
    
    numOuterRingVertices = outerRingRadius * numFacesPerUnit + 1;   //add vertices for seam
    
    numInnerRingVertices = innerRingRadius * numFacesPerUnit + 1;   //add vertices for seam
    
    numVertices = numOuterRingVertices * numInnerRingVertices;
    
    numIndices = 4 * numOuterRingVertices * numInnerRingVertices;
    
    vertices = new float[TORUS_VERTEX_STRIDE * numVertices];
    
    indices = new unsigned int[numIndices];
    
    makeTorus();
    
}

Torus::Torus(const Torus & source) {
    copy(source);
}

Torus::~Torus() {
    clear();
}

const Torus & Torus::operator=(const Torus & source) {
    
    if (this != &source) {
        
        clear();
        
        copy(source);
        
    }
    
    return source;
}

void Torus::copy(const Torus & source) {
    
    outerRingRadius = source.outerRingRadius;
    
    innerRingRadius = source.innerRingRadius;
    
    numOuterRingVertices = source.numOuterRingVertices;
    
    numInnerRingVertices = source.numInnerRingVertices;
    
    numVertices = source.numVertices;
    
    numIndices = source.numIndices;
    
    vertices = new float[TORUS_VERTEX_STRIDE * numVertices];
    
    indices = new unsigned int[numIndices];

    for (int i = 0; i < TORUS_VERTEX_STRIDE *  numVertices; i++) {
        vertices[i] = source.vertices[i];
    }
    
    for (int i = 0; i <  numVertices; i++) {
        indices[i] = source.indices[i];
    }
    
    /*rotation = source.rotation;
    
    translation = source.translation;
    
    scale = source.scale;*/
}

void Torus::clear() {
    
    delete vertices;
    
    delete indices;
}

void Torus::makeTorus() {
    
    int u, v;
    int i;
    int k = 0;
    
    for (v = 0; v < numInnerRingVertices; v++) {
        
        for (u = 0; u < numOuterRingVertices; u++) {
            
            i = v * numOuterRingVertices + u;
            
            vertices[TORUS_VERTEX_STRIDE * i + 0] = (outerRingRadius + innerRingRadius * cosf( v * TWO_PI / (numInnerRingVertices-1) )) * cosf( u * TWO_PI / (numOuterRingVertices-1) );
            vertices[TORUS_VERTEX_STRIDE * i + 1] = (outerRingRadius + innerRingRadius * cosf( v * TWO_PI / (numInnerRingVertices-1) )) * sinf( u * TWO_PI / (numOuterRingVertices-1) );
            vertices[TORUS_VERTEX_STRIDE * i + 2] = innerRingRadius * sinf( v * TWO_PI / (numInnerRingVertices-1) );
            
            vertices[TORUS_VERTEX_STRIDE * i + 3] = (float)u / (numOuterRingVertices - 1);  //u-coord
            vertices[TORUS_VERTEX_STRIDE * i + 4] = (float)v / (numInnerRingVertices - 1);  //v-coord
            
            indices[4 * k + 0] = v * numOuterRingVertices + u;                                                                  //top left courner
            indices[4 * k + 1] = v * numOuterRingVertices + ((u + 1) % numOuterRingVertices);                                   //top right
            indices[4 * k + 2] = ((v + 1) % numInnerRingVertices) * numOuterRingVertices + ((u + 1) % numOuterRingVertices);    //bottom right
            indices[4 * k + 3] = ((v + 1) % numInnerRingVertices) * numOuterRingVertices + u;                                   //bottom left
            
            k++;
            
        }
    }
}