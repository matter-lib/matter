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

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <SDL2/SDL.h>

#include "../units.h"
#include "../color.h"

enum class ViewState
{
    Active,
    Inactive,
    Disabled,
};

/**
 * A view is the base class that all controls such as buttons, labels,
 * text-fields etc inherit from. It is at the top of the layout tree, and does
 * little on its own.
 */
class View
{
public:
    /// The background color of the view
    Color backgroundColor = Color(0, 0, 0, 255);

    /// Whether the view allows clicking or not
    bool allowsClick = false;

    /// Whether the view allows hovering or not
    bool allowsHover = false;

    /// Whether the view allows keyboard input or not
    bool allowsKeyboard = false;

    /// The background color to use when inactive
    Color inactiveBackgroundColor = Color(196, 196, 196, 255);

    /// The background color to use when active
    Color activeBackgroundColor = Color(249, 192, 0, 255);

    /// The background color to use when disabled
    Color disabledBackgroundColor = Color(150, 150, 150, 255);

    /// The foreground color to use when inactive
    Color inactiveForegroundColor = Color(0, 0, 0, 255);

    /// The foreground color to use when active
    Color activeForegroundColor = Color(255, 255, 255, 255);

    /// The foreground color to use when disabled
    Color disabledForegroundColor = Color(0, 0, 0, 255);

    /**
     * Size is strictly based on content, size will not changed by parent
     *
     * - contentSize virtual function should be overriden if true
     */
    bool inferContentSize = false;

    /**
     * Should return content size, only will be called when `inferContentSize` is true
     *
     * - Can return NULL and override inferContentSize, will cause the View's size to be changed
     * - Should not call `super`
     */
    virtual Size *contentSize();

    // Getter methods
    ViewState getState();
    Rect getFrame();

    void setSize(Size);
    void setPosition(Point);

    Size *getInferredSize();

    View();

    Color getBackgroundColor(ViewState state);
    Color getBackgroundColor();

    Color getForegroundColor(ViewState state);
    Color getForegroundColor();

    void invalidateContent();

    virtual void initialize(SDL_Renderer *context);
    virtual void render(SDL_Renderer *context);
    virtual void processEvents(SDL_Event* event);
    virtual void windowSizeChanged();
    virtual void stateChanged();
private:
    void m_setState(ViewState state);

    bool m_invalidatedContent = true;
    ViewState m_state = ViewState::Inactive;

    /// The position of the view
    Point m_position = Point(0, 0);

    /// The size of the view
    Size m_size = Size(0, 0);
};

#endif