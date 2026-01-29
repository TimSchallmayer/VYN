#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#pragma once

// Prototypen der Funktionen:
SDL_Window* init_SDL(int w, int h);
SDL_Renderer* init_renderer(SDL_Window *window);
bool quit(SDL_Renderer *renderer, SDL_Window *window);
void draw(SDL_Renderer *renderer);