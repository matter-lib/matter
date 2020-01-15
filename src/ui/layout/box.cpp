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

#include "box.h"

Box::Box(BoxAxis axis) {
    this->m_axis = axis;
}

BoxAxis Box::getAxis()
{
    return this->m_axis;
}

void Box::setAxis(BoxAxis axis)
{
    this->m_axis = axis;
}

void Box::addChildControl(Control *child)
{
    this->m_childControls.push_back(child);
}

void Box::m_updateChildrenFrame()
{
    int inferredSizeTotal = 0;
    int inferredSizeItems = 0;
    int *largestInverseSize = NULL;
    for (auto const& child: this->m_childControls)
    {
        Size *inferredSize = child->getInferredSize();
        if (inferredSize != NULL)
        {
            int inverseSize = 0;
            if (this->getAxis() == BoxAxis::Horizontal) { inferredSizeTotal += inferredSize->w; inverseSize = inferredSize->h; }
            else { inferredSizeTotal += inferredSize->h; inverseSize = inferredSize->w; }

            if (largestInverseSize == NULL) {
                largestInverseSize = &inverseSize;
            } else if (inverseSize > *largestInverseSize) {
                largestInverseSize = &inverseSize;
            }
            inferredSizeItems += 1;
        }
    }

    int boxUnit = 0;
    if (this->getAxis() == BoxAxis::Horizontal) { boxUnit = this->getFrame().size.w; }
    else { boxUnit = this->getFrame().size.h; }

    int resizeableItems = this->m_childControls.size() - inferredSizeItems;
    int freeSpace = boxUnit - inferredSizeTotal;

    int unitsPerChild = 0;
    if (resizeableItems > 0 || freeSpace > 0) {
        unitsPerChild = freeSpace / resizeableItems;
    }
    
    int positionUnits = 0;
    for (auto const& child: this->m_childControls)
    {
        Size *inferredSize = child->getInferredSize();
        if (inferredSize != NULL)
        {
            child->setSize(*inferredSize);

            if (this->getAxis() == BoxAxis::Horizontal) { child->setPosition(Point(this->getFrame().point.x + positionUnits, this->getFrame().point.y)); positionUnits += inferredSize->h; }
            else { child->setPosition(Point(this->getFrame().point.x, this->getFrame().point.y + positionUnits)); positionUnits += inferredSize->w; }
        }
        else {
            if (this->getAxis() == BoxAxis::Horizontal)
            {
                child->setSize(Size(unitsPerChild, this->getFrame().size.h));
                child->setPosition(Point(this->getFrame().point.x + positionUnits, this->getFrame().point.y));
            }
            else {
                child->setSize(Size(this->getFrame().size.w, unitsPerChild));
                child->setPosition(Point(this->getFrame().point.x, this->getFrame().point.y + positionUnits));
            }
            positionUnits += unitsPerChild;
        }
    }
}

void Box::render(SDL_Renderer *context)
{
    super::render(context);

    this->m_updateChildrenFrame();

    for (auto const& child: this->m_childControls) {
        child->render(context);
    }
}

void Box::processEvents(SDL_Event* event)
{
    super::processEvents(event);

    for (auto const& child: this->m_childControls) {
        child->processEvents(event);
    }
}

void Box::windowSizeChanged()
{
    super::windowSizeChanged();

    for (auto const& child: this->m_childControls) {
        child->windowSizeChanged();
    }
}

void Box::stateChanged()
{
    super::stateChanged();

    for (auto const& child: this->m_childControls) {
        child->stateChanged();
    }
}