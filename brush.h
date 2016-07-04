#ifndef BRUSH_H
#define BRUSH_H

#include "image.h"

class Brush {
    int brushSize_;
    my::image::rgba_t brushColor_;
public:
    Brush(int brushSize, my::image::rgba_t brushColor);
    void drawBrush();
};

#endif // BRUSH_H
