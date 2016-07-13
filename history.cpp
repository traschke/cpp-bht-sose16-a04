#include "history.h"
#include <iostream>

namespace my {

history::history() : imageHistory(0)
{

}

void history::commit(image img)
{
    imageHistory.push_back(img);
    std::cout << "Image History Commit: #" << imageHistory.size() << std::endl;
}

image history::Undo()
{
    if(imageHistory.size() > 1) {
        image tempImage = imageHistory[imageHistory.size() - 1];
        imageHistory.pop_back();
        std::cout << "Image History Undo: #" << imageHistory.size() << std::endl;
        return tempImage;
    }
}


}
