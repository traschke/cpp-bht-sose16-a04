#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "image.h"

class Triangle
{
public:
    int tileLength;
    Triangle();
    void drawTriangle(my::image& image, int x, int y, my::image::rgba_t brushColor_);
};

#endif // TRIANGLE_H
