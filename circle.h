#ifndef CIRCLE_H
#define CIRCLE_H

#include "image.h"

class Circle
{
public:
    int radius;
    Circle();
    void drawCircle(my::image& image, int x, int y, my::image::rgba_t brushColor_);
};

#endif // CIRCLE_H
