#include "circle.h"

Circle::Circle()
{

}

void Circle::drawCircle(my::image &image, int x0, int y0, my::image::rgba_t brushColor_)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        image.set_pixel(x0 + x, y0 + y, brushColor_);
        image.set_pixel(x0 + y, y0 + x, brushColor_);
        image.set_pixel(x0 - y, y0 + x, brushColor_);
        image.set_pixel(x0 - x, y0 + y, brushColor_);
        image.set_pixel(x0 - x, y0 - y, brushColor_);
        image.set_pixel(x0 - y, y0 - x, brushColor_);
        image.set_pixel(x0 + y, y0 - x, brushColor_);
        image.set_pixel(x0 + x, y0 - y, brushColor_);

        y += 1;
        err += 1 + 2*y;
        if (2*(err-x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2*x;
        }
    }
}
