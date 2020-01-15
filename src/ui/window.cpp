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

#include "window.h"

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

void Window::m_updateRootView() {
    this->m_rootView->setPosition(Point(0, 0));
    this->m_rootView->setSize(this->getSize());
}

void Window::setRootView(View *view)
{
    this->m_rootView = view;
    this->m_updateRootView();
}

void Window::render()
{
    this->m_updateRootView();
    this->m_rootView->render(this->m_renderer);
}

void Window::processEvents(SDL_Event *event)
{
    if (event->type == SDL_WINDOWEVENT)
    {
        if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            this->m_updateRootView();
            this->m_rootView->windowSizeChanged();
        }
    }

    this->m_rootView->processEvents(event);
}

