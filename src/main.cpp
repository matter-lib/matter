/**
* MIT License
* Copyright (c) 2020 Matter Team
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ui/window.h"
#include "ui/pushbutton.h"
#include "ui/layout/box.h"

int main(int argv, char** args)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "TTF init error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("matter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));

    if (window == NULL) {
        printf("Could not create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Window win = Window(window, renderer);

    PushButton btn1 = PushButton();
    btn1.setText("Long Text Button");

    PushButton btn2 = PushButton();
    btn2.setText("shrt txt btn");

    Box box = Box(BoxAxis::Vertical);
    box.addChildView(&btn1);
    box.addChildView(&btn2);

    box.useContentSizeOnAxis = true;

    win.setRootView(&box);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            win.processEvents(&event);

            if (event.type == SDL_QUIT) {
                quit = true;
            }

            // Render other stuff here
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            win.render();

            SDL_RenderPresent(renderer);
        }
    }


    SDL_Quit();

    return 0;
}