#include "image.h"

namespace my {

image::image( size_t width, size_t height )
: width_   { width }
, height_  { height }
, data_    ( width * height, 0xff123456 )
{}

void image::ClearBackground(int color) {
    fill(data_.begin(), data_.end(), color);
}

void image::LoadData(QImage img)
{
    for (int i = 0; i <= data_.size(); i++) {
        data_[i] = img.pixel(i % width(), i / width());
    }
}

}
