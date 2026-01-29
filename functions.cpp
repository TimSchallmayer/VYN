#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include "VYN.h"
using namespace std;

SDL_Window *init_SDL(int w, int h) {

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0)
    {
        cerr << "ERROR:" << SDL_GetError() << endl;
        return nullptr;
    }
    
    SDL_Window *window = SDL_CreateWindow("VYN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL)
    {
        cerr << "ERROR:" << SDL_GetError() << endl;
        return nullptr;
    }
    return window;
}

SDL_Renderer *init_renderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (renderer == nullptr)
    {
        return nullptr;
    }
    return renderer;
}
bool quit(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return true;
}
void draw(SDL_Renderer *renderer) {
    
    int x, y;
    
    SDL_GetMouseState(&x, &y);

    SDL_Rect rect;
    rect.h = 40;
    rect.w = 40;
    rect.y = y - 20;
    rect.x = x - 20;
    
    SDL_SetRenderDrawColor(renderer, 0, 0 , 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0 , 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    return;
}