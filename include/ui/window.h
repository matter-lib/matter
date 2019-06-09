#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <SDL2/SDL.h>
#include "../units.h"
#include "control.h"

class Window
{
    Control m_rootControl;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

public:

    Window(SDL_Window *, SDL_Renderer *);

    Size getSize();

    void setRootController(Control);
    void render();
    void processEvents(SDL_Event *);
};

#endif