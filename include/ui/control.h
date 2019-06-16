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

#ifndef UI_CONTROL_H
#define UI_CONTROL_H

#include <SDL2/SDL.h>

#include "../units.h"
#include "../color.h"

enum class ControlState
{
    Active,
    Inactive,
    Disabled,
};

/**
 * A control is the base class that all controls such as buttons, labels,
 * text-fields etc inherit from. It is at the top of the layout tree, and does
 * little on its own.
 */
class Control
{
public:
    /// The position of the control
    Point position;

    /// The size of the control
    Size size;

    /// The background color of the control
    Color backgroundColor = Color(0, 0, 0, 255);

    /// Whether the control allows clicking or not
    bool allowsClick = false;

    /// Whether the control allows hovering or not
    bool allowsHover = false;

    /// Whether the control allows keyboard input or not
    bool allowsKeyboard = false;

    /// Whether the control allows auto-sizing or not
    bool autoSize = false;

    /// The background color to use when inactive
    Color inactiveBackgroundColor = Color(0, 0, 0, 255);

    /// The background color to use when active
    Color activeBackgroundColor = Color(0, 0, 0, 255);

    /// The background color to use when disabled
    Color disabledBackgroundColor = Color(0, 0, 0, 255);

    /// The foreground color to use when inactive
    Color inactiveForegroundColor = Color(0, 0, 0, 255);

    /// The foreground color to use when active
    Color activeForegroundColor = Color(0, 0, 0, 255);

    /// The foreground color to use when disabled
    Color disabledForegroundColor = Color(0, 0, 0, 255);

    // Getter methods
    Rect getFrame();
    ControlState getControlState();

    Control();

    Color getBackgroundColor(ControlState state);
    Color getBackgroundColor();

    void invalidateContent();

    virtual void initialize(SDL_Renderer *context);
    virtual void render(SDL_Renderer *context);
    virtual void processEvents(SDL_Renderer *context);
private:
    bool m_invalidatedContent;
    ControlState m_state;
};

#endif