#include "line.h"

Line::Line()
{

}

Line::Line(int size){
    lineSize_ = size;
    lastX = 0;
    lastY = 0;
}

void Line::drawLine(my::image &image, int x1, int y1, int x2, int y2, my::image::rgba_t brushColor_)
{
    // Bresenham's line algorithm
    // Draw a line from the last position clicked to the current position.
    const bool steep = (std::abs(y2 - y1) > std::abs(x2 - x1));
    if(steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const int dx = std::abs(x2 - x1);
    const int dy = std::abs(y2 - y1);

    int error = dx / 2;
    const int ystep = (y1 - y2) ? 1 : -1;
    int y = y1;

    const int maxX = x2;

    for(int x = x1; x < maxX; x++) {
        if(steep) {
            image.set_pixel(y, x, brushColor_);
        } else {
            image.set_pixel(x, y, brushColor_);
        }

        error -= dy;
        if(error < 0) {
            y += ystep;
            error += dx;
        }
    }
}
