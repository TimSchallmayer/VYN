#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>
#pragma once

//structs:
struct Button
{
    bool hovered;
    bool pressed;
    int height;
    int width;
    int x;
    int y;
    SDL_Color color;
};


// Prototypen der Funktionen:
SDL_Window* init_SDL(int w, int h);
// SDL starten

SDL_Renderer* init_renderer(SDL_Window *window);
// SDL renderer starten

bool quit(SDL_Renderer *renderer, SDL_Window *window);
// SDL schließen und alle instancen beenden

void draw(SDL_Renderer *renderer);
// malt ein rotes rechteck an die aktuelle maus position
void check_button(Button *button, SDL_Renderer *renderer);
// mal einen button, der rnazoomt und die farbe ändert wernn man klickt
void draw_text(SDL_Renderer *renderer, std::string inhalt, TTF_Font *font, int x, int y);