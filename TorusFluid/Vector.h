//
//  Vector.h
//  Fluid
//
//  Created by Ellis Sparky Hoag on 7/12/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#ifndef __Fluid__Vector__
#define __Fluid__Vector__

#include <iostream>
#include <math.h>

class Vector    {
    
private:
    
public:
    
    Vector(float a, float b, float c);
    
    Vector(float a, float b);
    
    Vector();
    
    float x, y, z;
    
    void operator=(Vector v)   {x = v.x; y = v.y; z = v.z;}
    
    void set(float a, float b, float c);
    
    inline float mag()  {return sqrtf(x*x + y*y + z*z);}
    
    static inline float mag(Vector v)   {return v.mag();}
    
    inline float magSqrd()  {return x*x + y*y + z*z;}
    
    static inline float magSqrd(Vector v)   {return v.magSqrd();}
    
    inline void normalize() {*this *= 1 / mag();}
    
    static Vector normalize(Vector v);
    
    void operator+=(float n);
    
    Vector operator+(float n);
    
    void operator+=(Vector v);
    
    Vector operator+(Vector v);
    
    void operator-=(float n);
    
    Vector operator-(float n);
    
    void operator-=(Vector v);
    
    Vector operator-(Vector v);
    
    void operator*=(float n);
    
    Vector operator*(float n);
    
    void operator*=(Vector v);
    
    Vector operator*(Vector v);
    
    float dotProduct(Vector v);
    
    static float dotProduct(Vector a, Vector b);
    
    Vector crossProduct(Vector v);
    
    static Vector crossProduct(Vector a, Vector b);
    
    void print();
};

#endif /* defined(__Fluid__Vector__) */
