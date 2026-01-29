#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include "VYN.h"
using namespace std;

const int HEIGHT = 600, WIDTH = 800;


int main(int argc, char* argv[]) {

    //Setup für SDL renderer und Fenster
    SDL_Window * window = init_SDL(WIDTH, HEIGHT);
    SDL_Renderer *render = init_renderer(window);
    
    if (render == nullptr || window == nullptr)
    {
        quit(render, window);
        return EXIT_FAILURE; 
    }
    

    //SDL Eventschleife
    SDL_Event event;
    while ( true )
    {
        draw(render);
        if ( SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
            
        }
        
    }
    quit(render, window);
    return EXIT_SUCCESS;
}