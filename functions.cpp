#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "VYN.h"
#include <algorithm>
#include <string>
#include <vector>

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
void draw_text(SDL_Renderer *renderer, TTF_Font *font, int x, int y, vector<string> lines, string inhalt, long int indexer_index) {
    int spacing = TTF_FontLineSkip(font);
    SDL_Color white = {255, 255, 255, 255};

    if (lines.empty() && inhalt.empty()) {   
        draw_indexer(x, y, 1, TTF_FontHeight(font), renderer);
        return;
    }

    int i = 0;
    for (const string& line : lines) {
        if (!line.empty()) {
            SDL_Surface *surface = TTF_RenderUTF8_Blended(font, line.c_str(), white);
            if (surface) {
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_Rect text_rect = {x, y + spacing * i, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, NULL, &text_rect);
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);
            }
        }
        i++;
    }

    int indexer_x = 0;
    //cout << "drawing..." << endl;
    if (!inhalt.empty()) {
        SDL_Surface *surface = TTF_RenderUTF8_Blended(font, inhalt.c_str(), white);
        if (surface) {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect dst = {x, y + spacing * i, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &dst);
            cout << "drawing1:" << inhalt.length() + indexer_index << endl;
            if (inhalt.length() != indexer_index * -1)
            {
                SDL_Surface *indexer_surface = TTF_RenderUTF8_Blended(font, inhalt.substr(0, indexer_index == 0 ? inhalt.length() :  inhalt.length() + indexer_index).c_str(), white);
                indexer_x = indexer_surface->w;
                SDL_FreeSurface(indexer_surface); 
            }
            else indexer_x == 0;

            SDL_DestroyTexture(texture);
         //   cout << "drawing2..." << endl;
            SDL_FreeSurface(surface);
        }
    }
    draw_indexer(x + indexer_x, y + spacing * i, 1, TTF_FontHeight(font), renderer);
    return;
}
void draw_indexer(int x, int y, int width, int height, SDL_Renderer *renderer) {
    
    SDL_Rect indexer = {x , y, width, height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &indexer);
  //  cout << "drawing3..." << endl;
    return;
}