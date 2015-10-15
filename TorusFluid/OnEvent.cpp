//
//  OnEvent.cpp
//  
//
//  Created by Ellis Sparky Hoag on 6/15/14.
//
//

#include "World.h"


void World::OnEvent()   {
    while (SDL_PollEvent(&Event)) {
        switch (Event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                SDLKeyDown(Event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                SDLKeyUp(Event.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDLMouseEvent(Event.button, x, y);
                break;
            default:
                break;
        }
    }
}

void World::SDLKeyDown(SDL_Keycode sym)   {
    
    switch (sym) {
        case SDLK_ESCAPE:
            running = false;
            break;
        default:
            break;
    }
}

void World::SDLKeyUp(SDL_Keycode sym) {
    
    switch (sym) {
        default:
            break;
    }
}

void World::SDLMouseEvent(SDL_MouseButtonEvent mouseButton, int x, int y) {

}