#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <image.h>

namespace my {

class history {
private:
    std::vector<image> imageHistory;
public:
    history();

    void commit(image img);
    image Undo();
};

}
#endif // HISTORY_H
