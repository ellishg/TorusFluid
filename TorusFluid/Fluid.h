//
//  Fluid.h
//  Fluid
//
//  Created by Ellis Sparky Hoag on 7/12/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#ifndef __Fluid__Fluid__
#define __Fluid__Fluid__

#include <assert.h>

#include "Vector.h"
#include "Color.h"

#define TWO_PI 6.28318530718f

#define COLOR

#define IX(i, j) ((i) + (gridWidth + 2) * (j))
#define EX(i, j) ((i) + (gridWidth) * (j))
#define SWAP(x0, x) {double * tmp = x0; x0 = x; x = tmp;}

#define MAX_DENSITY 10

class Fluid {
    
public:
    
    Fluid(unsigned int gWidth, unsigned int gHeight, float _outerRadius, float _innerRadius);
    
    Fluid(const Fluid & source);
    
    ~Fluid();
    
    const Fluid & operator=(const Fluid & source);
        
    void OnLoop();
    
    void prepareRender();
    
    Color * getColors() {return colors;}
    
    void addFluid(int x, int y, double strength, double radius, Color color);
    
    void addVelocity(int x, int y, Vector dir, double r);
    
    int getGridWidth()  {return gridWidth;}
    
    int getGridHeight() {return gridHeight;}
    
    int getN()  {return N;}
    
    void increment_dt()  {dt += 0.01;}
    void decrement_dt() {dt -= 0.01; if(dt < 0) {dt = 0;}}
    
    void increment_diffusion()  {diff += 0.001;}
    void decrement_diffusion()  {diff -= 0.0001; if(diff < 0) {diff = 0;}}
    
    void increment_viscosity()  {visc += 0.0001;}
    void decrement_viscosity()  {visc -= 0.0001; if(visc < 0) {visc = 0;}}
    
    double get_dt() {return dt;}
    double get_diffusion()  {return diff;}
    double get_viscosity()  {return visc;}
    
private:
    
    void copy(const Fluid & source);
    
    void clear();
    
    unsigned int N;
    unsigned int gridWidth, gridHeight;
    
    unsigned int size;
    
    double *u, *v, *u_prev, *v_prev;
    
    
    double * dens_r, * dens_prev_r;
#ifdef COLOR
    double *dens_g, *dens_b, *dens_prev_g, *dens_prev_b;
#endif
    
    double visc, diff, dt;
    
    Color * colors;
        
    void add_source(double * x, double * s, bool IsDensity);
    
    void diffuse(double * x, double * x0, double diff);
    
    void advect(double * d, double * d0, double * u0, double * v0);
    
    void dens_step(double * x, double * x0);
    
    void vel_step();
    
    void project(double * u, double * v, double * p, double * div);
    
    void set_bnd(double * x);
    
    void setForceArea(double * u, int a, int b, double s, double r);
    
    float alphaRadius;
    
    float betaRadius;
    
    double getGridSizeWidth() {return 1.f/gridWidth;}//TWO_PI * betaRadius / gridHeight;}
    
    double getGridSizeHeight(int y) {return 1.f/gridHeight;}//TWO_PI / gridWidth * (alphaRadius - betaRadius * cosf(TWO_PI * y));}
    /* y must be between 0 and 1 */

};

#endif /* defined(__Fluid__Fluid__) */
