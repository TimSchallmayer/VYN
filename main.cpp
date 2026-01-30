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
    
    Button button1;
    button1.height = 30;
    button1.width = 50;
    button1.hovered = false;
    button1.pressed = false;
    button1.x = HEIGHT / 2;
    button1.y = WIDTH / 2;
    button1.color = {0, 0, 255, 255};

    //SDL Eventschleife
    SDL_Event event;
    while ( true )
    {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        button1.hovered =  mx >= button1.x && mx <= button1.x + button1.width && my >= button1.y && my <= button1.y + button1.height;
        //draw(render);
        check_button(&button1, render);
        if ( SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) break;
            if (event.type == SDL_MOUSEBUTTONDOWN && button1.hovered)
            {
                //cout << "button pressed" << endl;
                if (button1.pressed)
                {
                    button1.pressed = false;
                    button1.color = {0, 0, 255, 255};
                }
                else {
                    button1.pressed = true;
                }
            }
            
        }
        
    }
    quit(render, window);
    return EXIT_SUCCESS;
}