#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "VYN.h"
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

int HEIGHT = 700, WIDTH = 1000;


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
    TTF_Font *font = TTF_OpenFont("src/fonts/Lobster,Oleo_Script,Roboto/JetBrains_Mono/static/JetBrainsMono-Regular.ttf", 24);
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
                    input.insert(input.length() + indexer_index, event.text.text);
                //    cout << input << endl;
                  //  cout << event.text.text << "input:" << input << endl;
                }
                
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && !text.empty())
                {
                    if ((input.empty() || (input.length() == indexer_index * -1)) && crnt_ln != 0)
                    {
                        if (input.empty()) indexer_index = 0;
                        crnt_ln -= 1;
                    }
                    else {
                        int pos = (int)input.length() + indexer_index;

                        if (pos > 0) {
                            int to_erase = 1;

                            while (pos - to_erase > 0 && (input[pos - to_erase] & 0xC0) == 0x80) {
                                to_erase++;
                            }
                            input.erase(pos - to_erase, to_erase);
                        }
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN && indexer_index == 0)
                {   
                    crnt_ln += 1;
                    string new_empty_line = "";
                    text.push_back(new_empty_line);
                }
                else if (event.key.keysym.sym == SDLK_RETURN && indexer_index != 0) 
                {
                    crnt_ln += 1;
                    string new_line = input.substr(input.length() + indexer_index, input.length());
                    input.erase(input.length() + indexer_index, input.length());
                    text.insert(text.begin() + crnt_ln, new_line);
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {

                    if (input.length() != indexer_index * -1) {

                        int pos = (int)input.length() + indexer_index;

                        if (pos >= 0) {
                            int to_erase = 1;

                            while (pos - to_erase > 0 && (input[pos - to_erase] & 0xC0) == 0x80) {
                                to_erase++;
                            }
                            indexer_index -= to_erase;
                        }
                    }
                    else if (crnt_ln != 0)  {
                        indexer_index = 0;
                        crnt_ln -= 1;
                    }
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)  {
                    if (indexer_index < 0) {
                        int pos = (int)input.length() + indexer_index;

                        if (pos >= 0)
                        {

                            int to_move = 1;
                            while (pos + to_move < input.length() && 
                                (input[pos + to_move] & 0xC0) == 0x80) {
                                to_move++;
                            }
                            indexer_index += to_move;
                        }
                    }
                    else if (crnt_ln + 1 < text.size()) {
                        crnt_ln += 1;
                        indexer_index = text[crnt_ln].length() * -1;        
                    }
                }
                else if (event.key.keysym.sym == SDLK_UP && crnt_ln > 0) {
                    crnt_ln -= 1;
                    string &neuer_input = text[crnt_ln];
                    int i = 0, best = 0, w, desired_x = indexer_index;
                    int new_laenge = distance(neuer_input.begin(), neuer_input.end());
                    int old_laenge = distance(input.begin(), input.end());
                    if (new_laenge > old_laenge) desired_x = indexer_index - (new_laenge - old_laenge);
                    else if (old_laenge > new_laenge) desired_x = indexer_index + (old_laenge - new_laenge);
                    while(i <= neuer_input.size())
                    {
                        TTF_SizeUTF8(font, neuer_input.substr(0, i).c_str(), &w, NULL);

                        if(w > desired_x)
                            break;

                        best = i;

                        // UTF8 skip
                        i++;
                        while(i < neuer_input.size() && (neuer_input[i] & 0xC0) == 0x80)
                            i++;
                    }

                    indexer_index = neuer_input.length() - best;
                }
                else if (event.key.keysym.sym == SDLK_DOWN && crnt_ln + 1 < text.size()) {
                    crnt_ln += 1;
                    string &neuer_input = text[crnt_ln];
                    int i = 0, best = 0, w, desired_x = indexer_index;
                    int new_laenge = distance(neuer_input.begin(), neuer_input.end());
                    int old_laenge = distance(input.begin(), input.end());
                    if (new_laenge > old_laenge) desired_x = indexer_index - (new_laenge - old_laenge);
                    else if (old_laenge > new_laenge) desired_x = indexer_index + (old_laenge - new_laenge);
                    while(i <= neuer_input.size())
                    {
                        TTF_SizeUTF8(font, neuer_input.substr(0, i).c_str(), &w, NULL);

                        if(w > desired_x)
                            break;

                        best = i;

                        // UTF8 skip
                        i++;
                        while(i < neuer_input.size() && (neuer_input[i] & 0xC0) == 0x80)
                            i++;
                    }

                    indexer_index = neuer_input.length() - best;
               // cout << "index:" << indexer_index;
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
        draw_text(render, font, WIDTH / 10, HEIGHT / 20, text, crnt_ln, indexer_index);
        SDL_RenderPresent(render);
    }
    end_loop:
    SDL_StopTextInput();
    quit(render, window);
    return EXIT_SUCCESS;
}
//Hällo
//miäör