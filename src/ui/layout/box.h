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

#ifndef UI_BOX_H
#define UI_BOX_H

#include "../control.h"
#include "../../units.h"
#include <math.h>
#include <vector>

enum class BoxAxis {
    Horizontal,
    Vertical
};

class Box: public Control
{
public:
    Box(BoxAxis axis);

    BoxAxis getAxis();
    void setAxis(BoxAxis axis);

    void addChildControl(Control *child);

    virtual void render(SDL_Renderer *context);
    virtual void processEvents(SDL_Event* event);
    virtual void windowSizeChanged();
    virtual void stateChanged();

private:
    typedef Control super;

    std::vector<Control*> m_childControls;

    int m_childSpacing = 0;
    BoxAxis m_axis = BoxAxis::Horizontal;

    void m_updateChildrenFrame();
};

#endif