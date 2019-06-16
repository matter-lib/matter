#include <iostream>
#include <SDL2/SDL.h>

#include "../include/ui/window.h"

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SLD init error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("app", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));

  if (window == NULL) {
    printf("Could not create window: %s", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  Window win = Window(window, renderer);

  Control testControl = Control();
  testControl.allowsClick = true;
  win.setRootControl(&testControl);

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