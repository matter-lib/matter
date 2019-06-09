#include "../../include/ui/window.h"

Window::Window(SDL_Window *window, SDL_Renderer *renderer)
{
    m_window = window;
    m_renderer = renderer;
}

Size Window::getSize() {
    // TODO: Get SDL2 window size

    return Size(100, 100);
}