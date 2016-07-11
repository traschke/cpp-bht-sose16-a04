#ifndef BRUSH_H
#define BRUSH_H

#include "image.h"

class Brush {
    int                 brushType_;
    int                 brushSize_;
    my::image::rgba_t   brushColor_;
public:
    Brush();
    Brush(int brushSize):brushSize_(brushSize)
    {
    }
    void drawBrush(my::image& image, int x, int y, my::image::rgba_t brushColor_);
    void SetSize(int brushSize_);
    void SetBrush(int brushType_);
    int GetSize();
};

#endif // BRUSH_H
