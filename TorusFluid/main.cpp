#include "World.h"

int main()  {
        
    World world;
    
    //srand((unsigned int)time(NULL));
    
    
    if (!world.OnInit()) {
        std::cout << "Error OnInit!\n";
        return 0;
    }
    
    while (world.isRunning()) {
        
        long prevTime = SDL_GetTicks();
      
        world.OnLoop();
        
        world.OnRender();
        
        do {
            world.OnEvent();
            
        } while ((SDL_GetTicks() - prevTime) * FRAMES_PER_SECOND < 1000);
        
        
        char titleStr[20];  //this should be long enough for my title
        
        sprintf(titleStr, "Torus Fluid | FPS: %lu", 1000 / (SDL_GetTicks() - prevTime));
        
        world.setWindowTitle(titleStr);
        
        //std::cout << 1000 / (GET_TICKS - prevTime) << ", ";
    }
    
    if (!world.OnCleanup()) {
        std::cout << "Error OnCleanup!\n";
        return 0;
    }
    
    return 0;
}