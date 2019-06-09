#ifndef UNITS_H
#define UNITS_H

#include <SDL2/SDL.h>

class Point {
public:
    int x, y;

    Point(int, int);
};

class Size {
public:
    int w, h;

    Size(int, int);
};

class Rect {
public:
    Point *point;
    Size *size;

    Rect(Point *, Size *);

    SDL_Rect toSDL();
};

#endif