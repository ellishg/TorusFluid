//
//  Vector.cpp
//  Fluid
//
//  Created by Ellis Sparky Hoag on 7/12/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "Vector.h"

Vector::Vector(float a, float b, float c)    {
    
    x = a;
    y = b;
    z = c;
}

Vector::Vector(float a, float b)    {
    x = a;
    y = b;
    z = 0;
}

Vector::Vector()    {
    
    x = 0;
    y = 0;
    z = 0;
}

void Vector::set(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}


void Vector::operator+=(float n)   {
    x += n;
    y += n;
    z += n;
}

Vector Vector::operator+(float n)   {
    return Vector(x+n, y+n, z+n);
}

void Vector::operator+=(Vector v)  {
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector Vector::operator+(Vector v)  {
    return Vector(x + v.x, y + v.y, z + v.z);
}

void Vector::operator-=(float n)    {
    x -= n;
    y -= n;
    z -= n;
}

Vector Vector::operator-(float n)   {
    return Vector(x - n, y - n, z - n);
}

void Vector::operator-=(Vector v)  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

Vector Vector::operator-(Vector v)  {
    return Vector(x - v.x, y - v.y, z - v.z);
}

void Vector::operator*=(float n)  {
    x *= n;
    y *= n;
    z *= n;
}

Vector Vector::operator*(float n)   {
    return Vector(x * n, y * n, z * n);
}

void Vector::operator*=(Vector v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

Vector Vector::operator*(Vector v)  {
    return Vector(x * v.x, y * v.y, z * v.z);
}

float Vector::dotProduct(Vector v)  {
    
    return x * v.x + y * v.y + z * v.z;
}

float Vector::dotProduct(Vector a, Vector b)   {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector Vector::crossProduct(Vector v)  {
    return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector Vector::crossProduct(Vector a, Vector b)  {
    return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Vector Vector::normalize(Vector v)  {
    
    v.normalize();
    return v;
}

void Vector::print()    {
    printf("\n{%f, %f, %f}", x, y, z);
}