#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "VYN.h"
#include <algorithm>
#include <string>

using namespace std;

SDL_Window *init_SDL(int w, int h) {

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0)
    {
        cerr << "ERROR:" << SDL_GetError() << endl;
        return nullptr;
    }
    if (TTF_Init() == -1) 
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
    TTF_Quit();
    SDL_Quit();
    return true;
}
void draw(SDL_Renderer *renderer) {
    
    int x, y;
    
    SDL_GetMouseState(&x, &y);

    SDL_Rect rect;
    rect.h = 4;
    rect.w = 4;
    rect.y = y - 20;
    rect.x = x - 20;
    SDL_SetRenderDrawColor(renderer, 255, 0 , 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    return;
}

void check_button(Button *button, SDL_Renderer *renderer) {

    SDL_Rect button_rect;
    button_rect.h = button->height;
    button_rect.w = button->width;
    button_rect.x = button->x;
    button_rect.y = button->y;
    if (button->pressed && button->hovered)
    {
        button->color = {0, 255, 0, 255};
    }
    SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, button->color.a);
    SDL_RenderFillRect(renderer, &button_rect);
    return;
}
void draw_text(SDL_Renderer *renderer, string inhalt, TTF_Font *font, int x, int y) {
    
    if (inhalt.empty())
    {   
        SDL_Rect start_rect;
        start_rect.h = TTF_FontHeight(font);
        start_rect.w = 3;
        start_rect.y = y;
        start_rect.x = x;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &start_rect);
        return;
    }
    int lines = count(inhalt.begin(), inhalt.end(), '\n'), spacing = TTF_FontLineSkip(font);


    int width, height;
    int index = inhalt.rfind('\n');
    if (index != string::npos)
    {
        string last_linebreak = inhalt.substr(index + 1);
        TTF_SizeUTF8(font, last_linebreak.c_str(), &width, &height);
    }
    else {
        TTF_SizeUTF8(font, inhalt.c_str(), &width, &height);
    }
    
    SDL_Rect indexer;
    indexer.h = TTF_FontHeight(font);
    indexer.w = 3;
    indexer.y = y + spacing * lines;
    indexer.x = x + width;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &indexer);
    SDL_Surface *surface = TTF_RenderUTF8_Blended_Wrapped(font, inhalt.c_str(), {255, 255, 255, 255}, 5000);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect text_rect = {x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &text_rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}