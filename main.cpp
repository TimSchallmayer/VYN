#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "VYN.h"
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

int HEIGHT = 700, WIDTH = 1000, FONT_SIZE = 24;


int main(int argc, char* argv[]) {

    //Setup für SDL renderer und Fenster
    SDL_Window * window = init_SDL(WIDTH, HEIGHT);
    SDL_Renderer *render = init_renderer(window);
    
    if (render == nullptr || window == nullptr)
    {
        quit(render, window);
        return EXIT_FAILURE; 
    }
    SDL_SetWindowResizable(window, SDL_TRUE);
    // Setup für die sachen die auf dem Bildschirm angezeigt werden
    TTF_Font *font = TTF_OpenFont("src/fonts/Lobster,Oleo_Script,Roboto/JetBrains_Mono/static/JetBrainsMono-Regular.ttf", FONT_SIZE);
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
    string empty_string = "";
    vector<string> text;
    long int indexer_index = 0;
    long int crnt_ln = 0;
    int breite_char, indexer_pos = 0;
    TTF_SizeUTF8(font, "A", &breite_char, nullptr);
    SDL_StartTextInput();
    while ( true )
    {   
        if (text.empty()) text.push_back(empty_string);    
        string &input = text[crnt_ln]; 
        SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);

        while ( SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) goto end_loop;

            else if (event.type == SDL_TEXTINPUT) {
                if (event.text.text[0] != '\0') {
                    input.insert(indexer_index, event.text.text);
                    string s = event.text.text;
                    indexer_index += s.length();
                    indexer_pos += breite_char;

                //    cout << input << endl;
                  //  cout << event.text.text << "input:" << input << endl;
                }
                
            }
            else if (event.type == SDL_KEYDOWN) {
                SDL_Keycode key = event.key.keysym.sym;
                SDL_Keymod mod = (SDL_Keymod)event.key.keysym.mod;

                if (key == SDLK_BACKSPACE && !text.empty())
                {
                    if (indexer_index != 0)
                    {
                        int start = indexer_index - 1;

                        while (start > 0 && (input[start] & 0xC0) == 0x80)
                            start--;

                        int len = indexer_index - start;

                        input.erase(start, len);
                        indexer_index = start;
                        indexer_pos -= breite_char; 
                    }
                    else if (crnt_ln > 0) {
                        crnt_ln -= 1;
                        indexer_index = text[crnt_ln].size();
                        indexer_pos = utf8_char_count(text[crnt_ln]) * breite_char;
                        text[crnt_ln].append(text[crnt_ln + 1]);
                        text.erase(text.begin() + crnt_ln +1);
                    }    
                }
                else if (key == SDLK_LEFT && !text.empty()) {
                    //cout << "left"<< endl;
                    if (indexer_index != 0)
                    {
                        int pos = indexer_index;

                        if (pos >= 0) {
                            int to_erase = 1;

                            while (pos - to_erase > 0 && (input[pos - to_erase] & 0xC0) == 0x80) {
                                to_erase++;
                            }
                            indexer_index -= to_erase;
                        }
                        indexer_pos -= breite_char;
                    }
                    else if (crnt_ln != 0) {
                        crnt_ln -= 1;
                        indexer_index = text[crnt_ln].size();
                        indexer_pos = utf8_char_count(text[crnt_ln]) * breite_char;
                    }
                }
                else if (key == SDLK_RIGHT) {
                    if (indexer_index < input.length())
                    {
                        int pos = indexer_index;

                        if (pos >= 0)
                        {

                            int to_move = 1;
                            while (pos + to_move < input.length() && 
                                (input[pos + to_move] & 0xC0) == 0x80) {
                                to_move++;
                            }
                            indexer_index += to_move;
                        }
                        indexer_pos += breite_char;
                    }
                    else if(crnt_ln < text.size() -1) {
                        crnt_ln += 1;
                        indexer_index = 0;
                        indexer_pos = 0;
                    }
                }
                else if (key == SDLK_RETURN) {
                    if (indexer_index != input.length())
                    {
                        string temp = input.substr(indexer_index, input.length() - indexer_index);
                        input.erase(indexer_index, input.length() - indexer_index);
                        crnt_ln += 1;
                        text[crnt_ln].insert(crnt_ln, temp);
                        indexer_index = 0;
                        indexer_pos = 0;
                    }
                    else {
                        crnt_ln += 1;
                        text.push_back("");
                        indexer_index = 0;
                        indexer_pos = 0;
                    }
                }
                else if ((mod & KMOD_CTRL) && key == SDLK_PLUS) {
                    cout << "pressed" << endl;
                    FONT_SIZE += 10;
                    int anzahl = indexer_pos / breite_char;
                    font = TTF_OpenFont("src/fonts/Lobster,Oleo_Script,Roboto/JetBrains_Mono/static/JetBrainsMono-Regular.ttf", FONT_SIZE);
                    TTF_SizeUTF8(font, "A", &breite_char, nullptr);
                   
                    indexer_pos = anzahl * breite_char;
                }
                else if ((mod & KMOD_CTRL) && key == SDLK_MINUS) {
                    cout << "pressed" << endl;
                    FONT_SIZE -= 10;
                    int anzahl = indexer_pos / breite_char;
                    font = TTF_OpenFont("src/fonts/Lobster,Oleo_Script,Roboto/JetBrains_Mono/static/JetBrainsMono-Regular.ttf", FONT_SIZE);
                    TTF_SizeUTF8(font, "A", &breite_char, nullptr);
                    indexer_pos = anzahl * breite_char;
                }
                else if (key == SDLK_DOWN && crnt_ln < text.size() -1) {
                    if (indexer_index > text[crnt_ln +1].length())
                    {
                        indexer_index = text[crnt_ln +1].length();
                        indexer_pos = utf8_char_count(text[crnt_ln +1]) * breite_char;
                    }
                    crnt_ln += 1;
                }
                else if (key == SDLK_UP && crnt_ln > 0) {
                    if (indexer_index > text[crnt_ln -1].length())
                    {
                        indexer_index = text[crnt_ln -1].length();
                        indexer_pos = utf8_char_count(text[crnt_ln -1]) * breite_char;
                    }
                    crnt_ln -= 1;
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
       // cout << text.size() << endl;
        check_button(&button1, render);
        draw_text(render, font, WIDTH / 10, HEIGHT / 20, text, crnt_ln, indexer_pos);
        SDL_RenderPresent(render);
    }
    end_loop:
    SDL_StopTextInput();
    quit(render, window);
    return EXIT_SUCCESS;
}
//Hällo
//miäör