#include "line.h"

Line::Line()
{

}

Line::Line(int size){
    lineSize_ = size;
    lastX = 0;
    lastY = 0;
}

void Line::drawLine(my::image &image, int x1, int y1, my::image::rgba_t brushColor_)
{
    // Bresenham's line algorithm
    // Draw a line from the last position clicked to the current position.
    const int dx = std::abs(lastX - x1);
    const int dy = std::abs(lastY - y1);

    const int ix = (x1 > lastX) ? -1 : 1;
    const int iy = (y1 > lastY) ? -1 : 1;

    int tempX = x1;
    int tempY = y1;


    if (dx >= dy) {
        int error = dy -(dx / 2);

        while (x1 != lastX) {
            if ((error >= 0) && (error || (ix > 0))) {
                error -= dx;
                y1 += iy;
            }

            error += dy;
            x1 += ix;

            image.set_pixel(x1, y1, brushColor_);
        }
    } else {
        int error = dx - (dy / 2);
         while (y1 != lastY) {
             if ((error >= 0) && (error || (iy < 0))) {
                 error -= dy;
                 x1 += ix;
             }

             error += dx;
             y1 += iy;

             image.set_pixel(x1, y1, brushColor_);
         }
    }

    lastX = tempX;
    lastY = tempY;
}
