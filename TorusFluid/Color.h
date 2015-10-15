//
//  Color.h
//  Fluid
//
//  Created by Ellis Sparky Hoag on 7/12/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#ifndef __Fluid__Color__
#define __Fluid__Color__

#include <iostream>

class Color {
    
private:
    
    uint32_t bits;

public:
    
    Color() : bits(0) {}
    
    Color(const Color & source);
    
    Color(uint8_t r, uint8_t g, uint8_t b);
    
    uint32_t getBits() const  {return bits;}
    
    void setBits(uint32_t _b) {bits = _b;}
    
    const Color & operator=(const Color & source);
    
    void operator+=(const Color & source);
    
    Color operator+(const Color & source) const ;
    
    void operator*=(float x);
    
    Color operator*(float x);
    
    void getSpectrum(uint8_t *r, uint8_t *g, uint8_t *b) const;
    
    uint8_t getRed() const {return (bits >> 16) & 0xFF;}

    uint8_t getGreen() const {return (bits >> 8) & 0xFF;}
    
    uint8_t getBlue() const {return bits & 0xFF;}

    void setColor(uint8_t r, uint8_t g, uint8_t b);
    
    void print() const;
    
};


#endif /* defined(__Fluid__Color__) */
