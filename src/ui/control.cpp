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

/**
 * Get the frame of the control. The frame contains the position
 * as well as the size of the control.
 * 
 * @return The frame of the control
 */
Rect Control::getFrame()
{
    Rect rect(&this->position, &this->size);
    return rect;
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

void Control::render(SDL_Renderer *context)
{
    // Render the background color
    Color drawingColor = this->getBackgroundColor();
}