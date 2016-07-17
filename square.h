#ifndef SQUARE_H
#define SQUARE_H

#include "image.h"

class Square
{
public:
    int a;
    Square();
    void drawSquare(my::image& image, int x, int y, my::image::rgba_t brushColor_);
};

#endif // SQUARE_H
