#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>
#include <vector>
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
void draw_text(SDL_Renderer *renderer, TTF_Font *font, int x, int y, std::vector<std::string> lines, long int current_line_index, long int indexer_index);
//malt den neuen text jedesmal auf basis des inhalts (aktuelle zeile) und des line vector, welche alle anderen zeilen enthählt
void draw_indexer(int x, int y, int width, int height, SDL_Renderer *renderer);
// malt den textcursor
int render_aktuelle_zeile(std::string inhalt, TTF_Font *font, SDL_Renderer *renderer, int x, int y, int spacing, SDL_Color white, long int indexer_index, int i);
//rendert die aktuelle zeile zwischen den bestehenden lines