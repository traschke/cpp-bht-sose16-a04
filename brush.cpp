#include "brush.h"
#include <iostream>

Brush::Brush()
{

}

void Brush::SetSize(int size) {
    brushSize_ = size;
}

void Brush::SetBrush(int brushType) {
    brushType_ = brushType;
}

int Brush::GetBrushType()
{
    return brushType_;
}

void Brush::drawBrush(my::image &image, int x, int y, my::image::rgba_t brushColor_) {
    if( brushSize_ >= 2 && brushType_ == 1) {
               std::cout << "Draw pencil..." << std::endl;
               for (int i = 0; i < brushSize_; ++i) {
                    for (int j = 0; j < brushSize_; ++j) {
                        image.set_pixel( x+j, y+i, brushColor_ );
                    }
               }
           } else if( brushSize_ >= 2 && brushType_ == 2 ) {
               std::cout << "Draw brush..." << std::endl;
               for (int i = 0; i < brushSize_; ++i) {
                    image.set_pixel( x-i, y-i, brushColor_ );
                    image.set_pixel( x, y-i, brushColor_ );
                    image.set_pixel( x+i, y-i, brushColor_ );

                    image.set_pixel( x-i, y, brushColor_ );
                    image.set_pixel( x, y, brushColor_ );
                    image.set_pixel( x+i, y, brushColor_ );

                    image.set_pixel( x-i, y+i, brushColor_ );
                    image.set_pixel( x, y+i, brushColor_ );
                    image.set_pixel( x+i, y+i, brushColor_ );
               }
           } else if( brushSize_ >= 2 && brushType_ == 3 ) {
               std::cout << "Draw Ink Pen..." << std::endl;
               for (int i = 0; i < brushSize_; ++i) {
                    image.set_pixel( x+i, y+i, brushColor_ );
                    image.set_pixel( x-i, y-i, brushColor_ );
               }
           } else {
               std::cout << "Set a small pixel..." << std::endl;
               image.set_pixel( x, y, brushColor_ );
           }
}
