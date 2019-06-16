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

#include "../include/units.h"

// Point

Point::Point() { }

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

// Size

Size::Size() { }

Size::Size(int w, int h)
{
    this->w = w;
    this->h = h;
}

// Rect

Rect::Rect() { }

Rect::Rect(Point *point, Size *size)
{
    this->point = point;
    this->size = size;
}

/**
 * Convert from a Matter::Rect to an SDL_Rect.
 * 
 * @return An SDL_Rect
 */
SDL_Rect Rect::toSDLRect()
{

    SDL_Rect rect;
    rect.x = point->x;
    rect.y = point->y;
    rect.w = size->w;
    rect.h = size->h;

    return rect;
}