#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include "VYN.h"
using namespace std;

const int HEIGHT = 600, WIDTH = 800;


int main(int argc, char* argv[]) {

    //Setup für SDL renderer und Fenster
    SDL_Window * window = init_SDL(WIDTH, HEIGHT);
    if (window == nullptr) return EXIT_FAILURE;

    SDL_Renderer *render = init_renderer(window);
    if (render == nullptr) return EXIT_FAILURE;
    
    //SDL Eventschleife
    SDL_Event event;
    while ( true )
    {
        if ( SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
            
        }
        
    }
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}