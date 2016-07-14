#ifndef LINE_H
#define LINE_H

#include "image.h"

class Line {
public:
    int lineSize_;
    int lastX;
    int lastY;
    Line();
    Line(int size);
    void drawLine(my::image& image, int x1, int x2, int y1, int y2, my::image::rgba_t brushColor_);
};

#endif // LINE_H
