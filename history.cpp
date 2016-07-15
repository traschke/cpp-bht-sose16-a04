#include "history.h"
#include <iostream>

namespace my {

history::history(image img) : imageHistory(0)
{
    commit(img);
}

image& history::current()
{
    return imageHistory.back();
}

void history::commit(image img)
{
    imageHistory.push_back(img);
    std::cout << "Image History Commit: #" << imageHistory.size() << std::endl;
}

void history::Undo()
{
    if(imageHistory.size() > 2) {
        imageHistory.pop_back();
    }

}

}
