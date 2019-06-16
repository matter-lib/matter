#include "../../include/ui/window.h"

Window::Window(SDL_Window *window, SDL_Renderer *renderer)
{
    m_window = window;
    m_renderer = renderer;
}

Size Window::getSize()
{
    int w, h;

    SDL_GetWindowSize(m_window, &w, &h);

    return Size(w, h);
}

void Window::setRootControl(Control *control)
{
    control->setPosition(Point(0, 0));
    control->setSize(this->getSize());
    m_rootControl = control;
}

void Window::render()
{
    this->m_rootControl->render(this->m_renderer);
}

void Window::processEvents(SDL_Event *event)
{
    this->m_rootControl->processEvents(event);
}

