#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#pragma once

// Prototypen der Funktionen:
SDL_Window* init_SDL(int w, int h);
// SDL starten

SDL_Renderer* init_renderer(SDL_Window *window);
// SDL renderer starten

bool quit(SDL_Renderer *renderer, SDL_Window *window);
// SDL schließen und alle instancen beenden

void draw(SDL_Renderer *renderer);
// malt ein rotes rechteck an die aktuelle maus position