/**
* MIT License
* Copyright (c) 2019 Matter Team
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

#include "../../include/ui/control.h"

Control::Control() { }

/**
* Renders the control using the given renderer context.
* 
* @param context The SDL_Renderer context to render using
*/
void Control::render(SDL_Renderer *context)
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
* Get the frame of the control. The frame contains the position
* as well as the size of the control.
* 
* @return The frame of the control
*/
Rect Control::getFrame()
{
    Size *inferredContentSize = this->contentSize();
    if (this->inferContentSize && inferredContentSize != NULL) {
        return Rect(this->m_position, *inferredContentSize);
    } else {
        return Rect(this->m_position, this->m_size);
    }
}

void Control::setSize(Size size)
{
    Size *inferredContentSize = this->contentSize();
    if (this->inferContentSize && inferredContentSize != NULL)
    {
        return;
    }
    this->m_size = size;
}

void Control::setPosition(Point position)
{
    this->m_position = position;
}

/**
* Get the background color of the control for the current state.
* 
* @return The background color of the control
*/
Color Control::getBackgroundColor()
{
    return this->getBackgroundColor(m_state);
}

/**
* Get the background color of the control for the given state.
* @param state The state that the control is in
* 
* @return The background color of the control 
*/
Color Control::getBackgroundColor(ControlState state)
{
    switch (state)
    {
        case ControlState::Active:
            return this->activeBackgroundColor; 
            break;
        case ControlState::Inactive:
            return this->inactiveBackgroundColor;
            break;
        case ControlState::Disabled:
            return this->disabledBackgroundColor;
            break;
        default: 
            // Handle default cases
            return this->inactiveBackgroundColor;
            break;
    }
}

Color Control::getForegroundColor()
{
    return this->getForegroundColor(m_state);
}

Color Control::getForegroundColor(ControlState state)
{
    switch (state)
    {
        case ControlState::Active:
            return this->activeForegroundColor; 
            break;
        case ControlState::Inactive:
            return this->inactiveForegroundColor;
            break;
        case ControlState::Disabled:
            return this->disabledForegroundColor;
            break;
        default: 
            // Handle default cases
            return this->inactiveForegroundColor;
            break;
    }
}

ControlState Control::getState()
{
    return m_state;
}

void Control::m_setState(ControlState state)
{
    m_state = state;
    this->invalidateContent();
    this->stateChanged();
}

/**
* Invalidate the content of the controls. This specifies to the renderer
* that we need to recall the `initialize` method and update the control.
*/
void Control::invalidateContent()
{
    this->m_invalidatedContent = true;
}

void Control::initialize(SDL_Renderer *context) { }

Size *Control::getInferredSize()
{
    Size *inferredContentSize = this->contentSize();
    if (this->inferContentSize && inferredContentSize != NULL) {
        return inferredContentSize;
    } else {
        return NULL;
    }
}

void Control::processEvents(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        // Check for left mouse button
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            Rect controlFrame = this->getFrame();

            // Check whether the mouse position is inside the button
            bool isInsideBox = (mouseX > controlFrame.point.x && mouseX < controlFrame.point.x + controlFrame.size.w &&
                mouseY > controlFrame.point.y && mouseY < controlFrame.point.y + controlFrame.size.h);
            if (isInsideBox && allowsClick)
            {
                // Using `state` instead of `m_state` for setter to call delegates
                this->m_setState(ControlState::Active);
            }
        }
    }
    else if (event->type == SDL_MOUSEBUTTONUP)
    {
        // Reset the button state on mouse up, using `state` instead of `m_state` for setter to call delegates
        this->m_setState(ControlState::Inactive);
    }

}

Size *Control::contentSize()
{
    return NULL;
}

void Control::windowSizeChanged() { }
void Control::stateChanged() { }
