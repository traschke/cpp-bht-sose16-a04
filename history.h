#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <image.h>

namespace my {

class history {
private:
    std::vector<image> imageHistory;
public:
    history(image img);
    image& current();

    void commit(image img);
    void Undo();
};

}
#endif // HISTORY_H
