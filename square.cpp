#include "square.h"

Square::Square()
{

}

void Square::drawSquare(my::image &image, int x, int y, my::image::rgba_t brushColor_)
{
    for (int i = 0; i < a; ++i) {
        image.set_pixel((x-a/2) + i, (y-a/2), brushColor_);
        image.set_pixel((x-a/2) + i, (y+a/2), brushColor_);
        image.set_pixel((x-a/2), (y-a/2) + i, brushColor_);
        image.set_pixel((x+a/2), (y-a/2) + i, brushColor_);
    }
}
