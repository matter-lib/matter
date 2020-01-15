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

#include "view.h"

View::View() { }

/**
* Renders the view using the given renderer context.
* 
* @param context The SDL_Renderer context to render using
*/
void View::render(SDL_Renderer *context)
{
    // Setting the background color to render
    Color drawColor = this->getBackgroundColor();

    SDL_SetRenderDrawColor(context, 
        drawColor.r, drawColor.g, drawColor.b, drawColor.a);

    // Drawing the background
    SDL_Rect rect = this->getFrame().toSDLRect();
    SDL_RenderFillRect(context, &rect);

    if (m_invalidatedContent)
    {
        // Check whether we need to invalidate the content
        this->initialize(context);
        this->m_invalidatedContent = false;
    }
}

/**
* Get the frame of the view. The frame contains the position
* as well as the size of the view.
* 
* @return The frame of the view
*/
Rect View::getFrame()
{
    Size *inferredContentSize = this->contentSize();
    if (this->inferContentSize && inferredContentSize != NULL) {
        return Rect(this->m_position, *inferredContentSize);
    } else {
        return Rect(this->m_position, this->m_size);
    }
}

void View::setSize(Size size)
{
    Size *inferredContentSize = this->contentSize();
    if (this->inferContentSize && inferredContentSize != NULL)
    {
        return;
    }
    this->m_size = size;
}

void View::setPosition(Point position)
{
    this->m_position = position;
}

/**
* Get the background color of the view for the current state.
* 
* @return The background color of the view
*/
Color View::getBackgroundColor()
{
    return this->getBackgroundColor(m_state);
}

/**
* Get the background color of the view for the given state.
* @param state The state that the view is in
* 
* @return The background color of the view 
*/
Color View::getBackgroundColor(ViewState state)
{
    switch (state)
    {
        case ViewState::Active:
            return this->activeBackgroundColor; 
            break;
        case ViewState::Inactive:
            return this->inactiveBackgroundColor;
            break;
        case ViewState::Disabled:
            return this->disabledBackgroundColor;
            break;
        default: 
            // Handle default cases
            return this->inactiveBackgroundColor;
            break;
    }
}

Color View::getForegroundColor()
{
    return this->getForegroundColor(m_state);
}

Color View::getForegroundColor(ViewState state)
{
    switch (state)
    {
        case ViewState::Active:
            return this->activeForegroundColor; 
            break;
        case ViewState::Inactive:
            return this->inactiveForegroundColor;
            break;
        case ViewState::Disabled:
            return this->disabledForegroundColor;
            break;
        default: 
            // Handle default cases
            return this->inactiveForegroundColor;
            break;
    }
}

ViewState View::getState()
{
    return m_state;
}

void View::m_setState(ViewState state)
{
    m_state = state;
    this->invalidateContent();
    this->stateChanged();
}

/**
* Invalidate the content of the views. This specifies to the renderer
* that we need to recall the `initialize` method and update the view.
*/
void View::invalidateContent()
{
    this->m_invalidatedContent = true;
}

void View::initialize(SDL_Renderer *context) { }

Size *View::getInferredSize()
{
    Size *inferredContentSize = this->contentSize();
    if (this->inferContentSize && inferredContentSize != NULL) {
        return inferredContentSize;
    } else {
        return NULL;
    }
}

void View::processEvents(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        // Check for left mouse button
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            Rect viewFrame = this->getFrame();

            // Check whether the mouse position is inside the button
            bool isInsideBox = (mouseX > viewFrame.point.x && mouseX < viewFrame.point.x + viewFrame.size.w &&
                mouseY > viewFrame.point.y && mouseY < viewFrame.point.y + viewFrame.size.h);
            if (isInsideBox && allowsClick)
            {
                // Using `state` instead of `m_state` for setter to call delegates
                this->m_setState(ViewState::Active);
            }
        }
    }
    else if (event->type == SDL_MOUSEBUTTONUP)
    {
        // Reset the button state on mouse up, using `state` instead of `m_state` for setter to call delegates
        this->m_setState(ViewState::Inactive);
    }

}

Size *View::contentSize()
{
    return NULL;
}

void View::windowSizeChanged() { }
void View::stateChanged() { }
