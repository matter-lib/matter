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

#include "label.h"

Label::Label() {
    this->inferContentSize = true;
}

Size *Label::contentSize()
{
    if (m_textTexture != NULL) {
        int textTextureWidth, textTextureHeight;
        SDL_QueryTexture(m_textTexture, NULL, NULL, &textTextureWidth, &textTextureHeight);

        Size* size = new Size(textTextureWidth, textTextureHeight);
        return size;
    }

    return NULL;
}

LabelAlignment Label::getVerticalAlignment()
{
    return this->m_verticalAlignment;
}
LabelAlignment Label::getHorizontalAlignment()
{
    return this->m_horizontalAlignment;
}

void Label::setVerticalAlignment(LabelAlignment alignment)
{
    this->m_verticalAlignment = alignment;
}
void Label::setHorizontalAlignment(LabelAlignment alignment)
{
    this->m_horizontalAlignment = alignment;
}

std::string Label::getText()
{
    return this->m_text;
}
void Label::setText(std::string text)
{
    this->m_text = text;
    this->invalidateContent();
}

int Label::getTextSize()
{
    return m_textSize;
}
void Label::setTextSize(int size)
{
    this->m_textSize = size;
    this->invalidateContent();
}

void Label::initialize(SDL_Renderer *context) {
    super::initialize(context);

    TTF_Font *textFont = TTF_OpenFont("assets/fonts/lato/Lato-Regular.ttf", m_textSize);
    if (textFont == NULL) {
        printf("TTF error: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface *textSurface;
    textSurface = TTF_RenderText_Blended(textFont, this->m_text.c_str(), this->getForegroundColor().toSDLColor());
    if (textSurface == NULL) {
        printf("TTF error: %s\n", TTF_GetError());
        return;
    }

    m_textTexture = SDL_CreateTextureFromSurface(context, textSurface);
    if (m_textTexture == NULL) {
        printf("TTF error: %s\n", TTF_GetError());
        return;
    }

    SDL_FreeSurface(textSurface);
    TTF_CloseFont(textFont);
}

Rect Label::m_calculateLabelRect(Size textureSize) {
    int x = 0;
    int y = 0;
    Rect viewFrame = this->getFrame();

    switch (this->getHorizontalAlignment()) {
    case LabelAlignment::Leading:
        x = 0;
        break;
    case LabelAlignment::Center:
        x = (int)round((viewFrame.size.w / 2) - (textureSize.w / 2));
        break;
    case LabelAlignment::Trailing:
        x = viewFrame.size.w - textureSize.w;
        break;
    }

    switch (this->getVerticalAlignment()) {
    case LabelAlignment::Leading:
        y = 0;
        break;
    case LabelAlignment::Center:
        y = (int)round((viewFrame.size.h / 2) - (textureSize.h / 2));
        break;
    case LabelAlignment::Trailing:
        y = viewFrame.size.h - textureSize.h;
        break;
    }

    return Rect(Point(this->getFrame().point.x + x, this->getFrame().point.y + y), textureSize);
}

void Label::render(SDL_Renderer *context) {
    super::render(context);

    int textTextureWidth, textTextureHeight;
    SDL_QueryTexture(m_textTexture, NULL, NULL, &textTextureWidth, &textTextureHeight);

    SDL_Rect textRect = this->m_calculateLabelRect(Size(textTextureWidth, textTextureHeight)).toSDLRect();
    SDL_RenderCopy(context, m_textTexture, NULL, &textRect);
}