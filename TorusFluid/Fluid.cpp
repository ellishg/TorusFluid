//
//  Fluid.cpp
//  Fluid
//
//  Created by Ellis Sparky Hoag on 7/12/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "Fluid.h"

Fluid::Fluid(unsigned int gWidth, unsigned int gHeight, float _outerRadius, float _innerRadius) : gridWidth(gWidth), gridHeight(gHeight), N(gWidth), alphaRadius(_outerRadius), betaRadius(_innerRadius)  {
    
    //Best N is about 120 as of 6/21/15 for 30 FPS
    
    /*
     *  If you want a screen other than a boring square you
     *  need to remember that I can only draw square points.
     *  So the dimensions need to be rational or something...
     *  Also check out the code in project() for width and height
     */
    
    size = (gridWidth + 2) * (gridHeight + 2);
    
    u = new double[size];
    v = new double[size];
    
    u_prev = new double[size];
    v_prev = new double[size];
    
    dens_r = new double[size];
    dens_prev_r = new double[size];
#ifdef COLOR
    dens_g = new double[size];
    dens_b = new double[size];
    dens_prev_g = new double[size];
    dens_prev_b = new double[size];
#endif
    
    for (int i = 0; i < size; i++) {
        dens_r[i] = 0;
        dens_prev_r[i] = 0;
#ifdef COLOR
        dens_g[i] = 0;
        dens_prev_g[i] = 0;
        dens_b[i] = 0;
        dens_prev_b[i] = 0;
#endif
        u[i] = 0;
        v[i] = 0;
        u_prev[i] = 0;
        v_prev[i] = 0;
    }
    
    colors = new Color[gridWidth * gridHeight];

    
    visc = 0.0001;  //viscosity
    
    diff = 0.00001;   //degree of diffusion of density over time
    
    dt = 0.1;   //rate of change
}

Fluid::Fluid(const Fluid & source) {
    copy(source);
}

Fluid::~Fluid() {
    clear();
}

const Fluid & Fluid::operator=(const Fluid & source) {
    
    if (this != &source) {
        
        clear();
        
        copy(source);
    
    }
    
    return source;
}

void Fluid::clear() {
    
    delete[] u;
    delete[] v;
    delete[] u_prev;
    delete[] v_prev;
    delete[] dens_r;
    delete[] dens_prev_r;
#ifdef COLOR
    delete[] dens_g;
    delete[] dens_b;
    delete[] dens_prev_g;
    delete[] dens_prev_b;
#endif
    
    delete[] colors;
}

void Fluid::copy(const Fluid & source) {
    
    N = source.N;
    
    gridWidth = source.gridWidth;
    
    gridHeight = source.gridHeight;
    
    size = source.size;
    
    u = new double[size];
    v = new double[size];
    
    u_prev = new double[size];
    v_prev = new double[size];
    
    dens_r = new double[size];
    dens_prev_r = new double[size];
#ifdef COLOR
    dens_g = new double[size];
    dens_b = new double[size];
    dens_prev_g = new double[size];
    dens_prev_b = new double[size];
#endif
    
    for (int i = 0; i < size; i++) {
        u[i] = source.u[i];
        v[i] = source.v[i];
        
        u_prev[i] = source.u_prev[i];
        v_prev[i] = source.v_prev[i];
        
        dens_r[i] = source.dens_r[i];
        dens_prev_r[i] = source.dens_prev_r[i];
        
#ifdef COLOR
        dens_g[i] = source.dens_g[i];
        dens_b[i] = source.dens_b[i];
        dens_prev_g[i] = source.dens_prev_g[i];
        dens_prev_b[i] = source.dens_prev_b[i];
#endif
        
    }
    
    colors = new Color[gridWidth * gridHeight];
    
    for (int i = 0; i < gridWidth * gridHeight; i++) {
        colors[i] = source.colors[i];
    }
    
    visc = source.visc;
    
    diff = source.diff;
    
    dt = source.dt;
    
    alphaRadius = source.alphaRadius;
    
    betaRadius = source.betaRadius;
}

void Fluid::OnLoop()    {
    
    /*
     *  dens_prev should have been modified by OnEvent and represents
     *  the source densities. Same for u_prev and v_prev
     */
    
    vel_step();
    
    dens_step(dens_r, dens_prev_r);
#ifdef COLOR
    dens_step(dens_g, dens_prev_g);
    dens_step(dens_b, dens_prev_b);
#endif
    
    for (int i = 0; i < size; i++) {
        dens_prev_r[i] = 0;
#ifdef COLOR
        dens_prev_g[i] = 0;
        dens_prev_b[i] = 0;
#endif
        u_prev[i] = 0;
        v_prev[i] = 0;
    }
    //zero these array so new sources can be added
}

void Fluid::prepareRender() {
    
    int i, j;
    
    float r;
#ifdef COLOR
    float g, b;
#endif
    
    for (i = 0; i < gridWidth; i++) {
        for (j = 0; j < gridHeight; j++) {
            
            r = dens_r[IX(i+1, j+1)] * 255 / MAX_DENSITY;
#ifdef COLOR
            g = dens_g[IX(i+1, j+1)] * 255 / MAX_DENSITY;
            b = dens_b[IX(i+1, j+1)] * 255 / MAX_DENSITY;
#endif

#ifdef COLOR
            colors[EX(i, j)] = Color(r, g, b);
#endif
            
#ifndef COLOR
            colors[EX(i, j)] = Color(r, r, r);
#endif
        }
    }
}

void Fluid::add_source(double * x, double * s, bool IsDensity)  {
    
    /*
     *  Copies source values onto the simulation array
     *  Also checks if fluid density is at a maximum value
     */
    
    for (int i = 0; i < size; i++) {
        x[i] += dt * s[i];
        
        if (IsDensity && x[i] > MAX_DENSITY) {
            x[i] = MAX_DENSITY;
        }
    }
}

void Fluid::diffuse(double * x, double * x0, double diff) {
    
    /*
     * Diffuse fluid in and out of a given cell
     * Diffusion goes to and from each of its four neighbors
     * Uses Guass-Seidel relaxation solver. Cool
     */
    
    /*
     * Ratio of diffusion of x to y is proportional to gridWidth to gridHeight
     * ....maybe
     * Note that gridHeight is a function of y
     */
    
    double a = dt * diff * gridWidth * gridHeight;
    
    int i, j, k;
    
    int mid, left, right, top, bottom;
    
    for (k = 0; k < 20; k++) {
        for (i = 1; i <= gridWidth; i++) {
            for (j = 1; j <= gridHeight; j++) {
                
                mid = IX(i, j);
                left = mid - 1; //IX(i - 1, j)
                right = mid + 1; //IX(i + 1, j)
                top = mid + gridWidth + 2; //IX(i, j + 1)
                bottom = mid - gridWidth - 2; //IX(i, j - 1)
                
                x[mid] = (x0[mid] + a * (x0[left] + x0[right] + x0[bottom] + x0[top])) / (1 + 4 * a);
            }
        }
    }
    
    set_bnd(x);
}


void Fluid::advect(double * d, double * d0, double * u0, double * v0)    {
    /*
     *  Calculate movement of fluid through vector field.
     *  Solves backwards by figuring out where fluid would have come from for each cell
     *  It uses Liner backtrace. Also cool
     */
        

    int i0, j0, i1, j1, i, j;
    
    double x, y, s0, s1, t0, t1;
    
    double dt0Width = gridWidth * dt;
    double dt0Height = gridHeight * dt;
    
    for (i = 1; i <= gridWidth; i++) {
        for (j = 1; j <= gridHeight; j++) {
            x = i - dt0Width * u0[IX(i, j)];
            
            y = j - dt0Height * v0[IX(i, j)];
            
            if (x < 0.5) {
                x = 0.5;
            }
            if (x > gridWidth + 0.5)    {
                x = gridWidth + 0.5;
            }
            
            i0 = (int)x;
            
            i1 = i0 + 1;
            
            if (y < 0.5) {
                y = 0.5;
            }
            if (y > gridHeight + 0.5)    {
                y = gridHeight + 0.5;
            }
            
            j0 = (int)y;
            
            j1 = j0 + 1;
            
            s1 = x - i0;
            
            s0 = 1 - s1;
            
            t1 = y - j0;
            
            t0 = 1 - t1;
            
            d[IX(i, j)] = s0 * (t0 * d0[IX(i0, j0)] + t1 * d0[IX(i0, j1)]) + s1 * (t0 * d0[IX(i1, j0)] + t1 * d0[IX(i1, j1)]);
            
        }
    }
    
    set_bnd(d);
}


void Fluid::dens_step(double * x, double * x0)    {
    
    /*
     *  We assume that all source densities are initially contained in x0
     */
    
    add_source(x, x0, true);
    
    //SWAP(x0, x);
    //We swap to conserve memory
    
    diffuse(x0, x, diff);
    
    //SWAP(x0, x);
    
    advect(x, x0, u, v);
}


void Fluid::vel_step()    {
    
    /*
     *  We assume that all source forces are initially contained in v0 and u0
     */
    
    add_source(u, u_prev, false);
    
    add_source(v, v_prev, false);
    
    //SWAP(u0, u);
    //We swap to conserve memory
    
    diffuse(u_prev, u, visc);
    
    //SWAP(v0, v);
    
    diffuse(v_prev, v, visc);
    
    project(u_prev, v_prev, u, v);
    
    //SWAP(u0, u);
    //SWAP(v0, v);
    
    advect(u, u_prev, u_prev, v_prev);
    advect(v, v_prev, u_prev, v_prev);
    
    project(u, v, u_prev, v_prev);
}


void Fluid::project(double * u, double * v, double * p, double * div)   {
    
    /*
     *  The purpose of this is to make the vector field mass conserving
     *  ...whatever that means...
     *  It makes the field nice and swirly
     *  It uses the Poisson Equation. Very cool
     */
    
    //this is the 'fluid world' width and height of each grid
    //square
    //double width = 1.f / gridWidth;
    //double height = 1.f / gridHeight;
    
    //torus!
    double width = getGridSizeWidth();
    //double height = DEPENDS ON Y
    
    
    int i, j, k;
    
    int mid, left, right, top, bottom;
    
    for (i = 1; i <= gridWidth; i++) {
        for (j = 1; j <= gridHeight; j++) {
            
            mid = IX(i, j);
            left = mid - 1; //IX(i - 1, j)
            right = mid + 1; //IX(i + 1, j)
            top = mid + gridWidth + 2; //IX(i, j + 1)
            bottom = mid - gridWidth - 2; //IX(i, j - 1)
            
            div[mid] = -0.5 * (width * (u[right] - u[left]) + getGridSizeHeight(j / (gridHeight - 2)) * (v[top] - v[bottom]));
            
            p[mid] = 0;
        }
    }
    
    set_bnd(div);
    set_bnd(p);
    
    for (k = 0; k < 20; k++) {
        for (i = 1; i <= gridWidth; i++) {
            for (j = 1; j <= gridHeight; j++) {
                
                mid = IX(i, j);
                left = mid - 1; //IX(i - 1, j)
                right = mid + 1; //IX(i + 1, j)
                top = mid + gridWidth + 2; //IX(i, j + 1)
                bottom = mid - gridWidth - 2; //IX(i, j - 1)
                
                p[mid] = (div[mid] + p[left] + p[right] + p[bottom] + p[top]) / 4.f;
            }
        }
        set_bnd(p);
    }
    
    for (i = 1; i <= gridWidth; i++) {
        for (j = 1; j <= gridHeight; j++) {
            
            mid = IX(i, j);
            left = mid - 1; //IX(i - 1, j)
            right = mid + 1; //IX(i + 1, j)
            top = mid + gridWidth + 2; //IX(i, j + 1)
            bottom = mid - gridWidth - 2; //IX(i, j - 1)

            
            u[mid] -= 0.5f * (p[right] - p[left]) / width;
            v[mid] -= 0.5f * (p[top] - p[bottom]) / getGridSizeHeight(j / (gridHeight - 2));
        }
    }
    
    set_bnd(u);
    set_bnd(v);
}

void Fluid::set_bnd(double * x)   {
    
    /*
     *  We set the boundary for the fluid.
     *  At the walls we copy non-boundary cells to the boundaries
     *  At courners we copy the average of the two neighboring cells
     *  
     *  I could add arbitrary boundries anywhere by modifying this code
     */
    
    int i;
    
    for (i = 1; i <= gridHeight; i++) {
        x[IX(0, i)] = x[IX(gridWidth, i)];
        x[IX(gridWidth+1, i)] = x[IX(1, i)];
    }
    for (i = 1; i <= gridWidth; i++) {
        x[IX(i, 0)] = x[IX(i, gridHeight)];
        x[IX(i, gridHeight+1)] = x[IX(i, 1)];
    }
    
    x[IX(0, 0)] = 0.5f * (x[IX(gridWidth+1, 0)] + x[IX(0, gridHeight+1)]);
    x[IX(0, gridHeight+1)] = 0.5f * (x[IX(gridWidth+1, gridHeight+1)] + x[IX(0, 0)]);
    x[IX(gridWidth+1, 0)] = 0.5f * (x[IX(0, 0)] + x[IX(gridWidth+1, gridHeight+1)]);
    x[IX(gridWidth+1, gridHeight+1)] = 0.5f * (x[IX(0, gridHeight+1)] + x[IX(gridWidth+1, 0)]);
}

void Fluid::setForceArea(double * x, int a, int b, double s, double r) {
    
    assert(a < N && b < N);
    
    /*
     *  This is to add values to an arbitrary location
     *  It computes a circle of radius r with heigher values
     *  at its center
     */
    
    int i, j, dx, dy;
    
    double f;
    
    int minX = (a - ceilf(r) > 0) ? a - ceilf(r) : 0;
    int maxX = (a + ceilf(r) < gridWidth) ? a + ceilf(r) : gridWidth;
    int minY = (b - ceilf(r) > 0) ? b - ceilf(r) : 0;
    int maxY = (b + ceilf(r) < gridHeight) ? b + ceilf(r) : gridHeight;
    
    for (i = minX; i <= maxX; i++) {
        dx = a - i;
        
        for (j = minY; j <= maxY; j++) {
            dy = b - j;
            
            f = 1 - sqrtf(dx*dx + dy*dy) / r;
            
            if (f < 0) {
                f = 0;
            }
            
            assert(f <= 1);
            //else if(f > 1)  {
            //    f = 1;
            //}
            
            x[IX(i, j)] += f * s;
        }
    }
}

void Fluid::addFluid(int x, int y, double strength, double radius, Color color)   {
    
    setForceArea(dens_prev_r, x, y, strength * color.getRed() / 255.f, radius);
#ifdef COLOR
    setForceArea(dens_prev_g, x, y, strength * color.getGreen() / 255.f, radius);
    setForceArea(dens_prev_b, x, y, strength * color.getBlue() / 255.f, radius);
#endif
}

void Fluid::addVelocity(int x, int y, Vector dir, double r)   {
        
    setForceArea(u_prev, x, y, dir.x, r);
    
    setForceArea(v_prev, x, y, dir.y, r);
}