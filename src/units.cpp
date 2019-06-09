#include "../include/units.h"

// Point

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

// Size

Size::Size(int w, int h)
{
    this->w = w;
    this->h = h;
}

// Rect

Rect::Rect(Point *point, Size *size)
{
    this->point = point;
    this->size = size;
}

SDL_Rect Rect::toSDL()
{
    SDL_Rect rect;
    rect.x = point->x;
    rect.y = point->y;
    rect.w = size->w;
    rect.h = size->h;

    return rect;
}