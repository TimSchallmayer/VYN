#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#pragma once

// Prototypen der Funktionen:
SDL_Window* init_SDL(int w, int h);
SDL_Renderer* init_renderer(SDL_Window *window);