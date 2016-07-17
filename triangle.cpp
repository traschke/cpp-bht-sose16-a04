#include "triangle.h"

Triangle::Triangle()
{

}

void Triangle::drawTriangle(my::image &image, int x, int y, my::image::rgba_t brushColor_)
{
    for (int i = 0; i < tileLength*2; ++i) {
        image.set_pixel((x-tileLength) + i, y-tileLength, brushColor_);
    }
    for (int i = 0; i < tileLength+1; ++i) {
        image.set_pixel((x-tileLength) + i, (y-tileLength) + i, brushColor_);
        image.set_pixel((x+tileLength) - i, (y-tileLength) + i, brushColor_);
    }
}
