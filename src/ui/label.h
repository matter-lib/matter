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

#ifndef UI_LABEL_H
#define UI_LABEL_H

#include <string>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "view.h"
#include "../color.h"

enum class LabelAlignment {
    Leading,
    Center,
    Trailing
};

class Label: public View
{
public:
    LabelAlignment getVerticalAlignment();
    LabelAlignment getHorizontalAlignment();

    void setVerticalAlignment(LabelAlignment alignment);
    void setHorizontalAlignment(LabelAlignment alignment);

    std::string getText();
    void setText(std::string text);

    int getTextSize();
    void setTextSize(int size);

    virtual void initialize(SDL_Renderer *context);
    virtual void render(SDL_Renderer *context);
private:
    typedef View super;

    LabelAlignment m_verticalAlignment = LabelAlignment::Center;
    LabelAlignment m_horizontalAlignment = LabelAlignment::Center;

    std::string m_text = "Label";
    int m_textSize = 16;

    SDL_Texture *m_textTexture;

    Rect m_calculateLabelRect(Size textureSize);
};

#endif