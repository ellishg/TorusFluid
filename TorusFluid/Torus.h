//
//  Torus.h
//  TorusFluid
//
//  Created by Ellis Sparky Hoag on 10/2/15.
//  Copyright © 2015 Ellis Sparky Hoag. All rights reserved.
//

#ifndef Torus_h
#define Torus_h

#define TWO_PI 6.28318530718f

#define TORUS_VERTEX_STRIDE 5

#include "math.h"

#include "Vector.h"


class Torus {

public:
    
    Torus(float _outerRadius, float _innerRadius, int numFacesPerUnit);
    
    Torus(const Torus & source);
    
    ~Torus();
    
    const Torus & operator=(const Torus & source);
    
    float getOuterRingRadius() const {return outerRingRadius;}
    
    float getInnerRingRadius() const {return innerRingRadius;}
        
    int getVertexArrayLength() const {return TORUS_VERTEX_STRIDE *  numVertices;}
    
    int getIndexArrayLength() const {return numIndices;}
        
    float * getVertices() const {return vertices;}
    
    unsigned int * getIndices() const {return indices;}
    
    /*Vector rotation;
    
    Vector translation;
    
    Vector scale;*/
    
private:
    
    float * vertices;
    
    int numVertices;
    
    int numOuterRingVertices;
    
    int numInnerRingVertices;
    
    float outerRingRadius;
    
    float innerRingRadius;

    unsigned int * indices;

    int numIndices;
    
    void copy(const Torus & source);
    
    void clear();
    
    void makeTorus();
};

#endif /* Torus_h */
