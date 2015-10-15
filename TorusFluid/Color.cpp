//
//  Color.cpp
//  Fluid
//
//  Created by Ellis Sparky Hoag on 7/12/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "Color.h"

Color::Color(const Color & source) {

    bits = source.bits;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b)   {
    
    setColor(r, g, b);

}

const Color & Color::operator=(const Color & source)  {
    
    if (this != &source) {
     
        bits = source.bits;
    
    }
    
    return source;
}

void Color::operator+=(const Color & source)   {
    
    setColor((getRed() + source.getRed()) / 2, (getGreen() + source.getGreen()) / 2, (getBlue() + source.getBlue()) / 2);
    
}

Color Color::operator+(const Color & source) const {
    
    return Color((getRed() + source.getRed()) / 2, (getGreen() + source.getGreen()) / 2, (getBlue() + source.getBlue()) / 2);

}

void Color::operator*=(float x)    {
    
    if (x > 1) {
        x = 1;
    }
    if (x < 0) {
        x = 0;
    }
    
    setColor(getRed() * x, getGreen() * x, getBlue() * x);
}

Color Color::operator*(float x) {
    
    if (x > 1) {
        x = 1;
    }
    
    if (x < 0) {
        x = 0;
    }
    
    return Color(getRed() * x, getGreen() * x, getBlue() * x);

}

void Color::getSpectrum(uint8_t *r, uint8_t *g, uint8_t *b) const {
    *r = (bits >> 16) & 0xFF;
    *g = (bits >> 8) & 0xFF;
    *b = bits & 0xFF;
}

void Color::setColor(uint8_t r, uint8_t g, uint8_t b)   {
    
    bits = (r << 16) | (g << 8) | b;
}

void Color::print() const {
    
    printf("{ %i, %i, %i }\n", getRed(), getGreen(), getBlue());
    
}