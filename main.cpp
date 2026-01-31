#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "VYN.h"
#include <string>
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

    // Setup für die sachen die auf dem Bildschirm angezeigt werden
    TTF_Font *font = TTF_OpenFont("src/fonts/Lobster,Oleo_Script,Roboto/Roboto/static/Roboto_Condensed-ExtraLightItalic.ttf", 24);
    if (!font)
    {
        cout << TTF_GetError() << endl;
    }
    Button button1;
    button1.height = 30;
    button1.width = 50;
    button1.hovered = false;
    button1.pressed = false;
    button1.x = WIDTH / 2;
    button1.y = HEIGHT / 2;
    button1.color = {0, 0, 255, 255};

    //SDL Eventschleife
    SDL_Event event;
    string input = "";
    SDL_StartTextInput();
    while ( true )
    {   
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);

        while ( SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) goto end_loop;

            else if (event.type == SDL_TEXTINPUT) {
                if (event.text.text[0] != '\0') {
                    input.append(event.text.text);
                //    cout << input << endl;
                 //   cout << event.text.text << endl;
                }
                
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && !input.empty())
                {
                    input.pop_back();
                }
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    input.append("\n");
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && button1.hovered)
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
        //button zoom
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        button1.hovered =  (mx >= button1.x && mx <= button1.x + button1.width) && (my >= button1.y && my <= button1.y + button1.height);
        if (button1.hovered)
        {
            //cout << "hovered" << endl;
            button1.y  = HEIGHT / 2 -5;
            button1.height = 40;
            button1.x = WIDTH / 2 -5;
            button1.width = 60;
        }
        else {
            //cout << "not hovered" << endl;
            button1.x = WIDTH / 2;
            button1.y = HEIGHT / 2;
            button1.height = 30;
            button1.width = 50;
        }
        
        //draw(render);
        check_button(&button1, render);
        draw_text(render, input, font, WIDTH / 6, HEIGHT / 4);
        SDL_RenderPresent(render);
    }
    end_loop:
    SDL_StopTextInput();
    quit(render, window);
    return EXIT_SUCCESS;
}