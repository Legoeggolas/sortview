#ifndef STATE_H
#define STATE_H

#include <memory>
#include <random>
#include <vector>

#include "../include/sortview.hpp"

class State {
   public:
    std::vector<int> vec;
    int elementLowerBound;
    int elementUpperBound;
    size_t vec_size;
    int fps;

    State(size_t _vec_size, int _lb = 1, int _ub = 1024, int _fps = 60);

    std::unique_ptr<SortViewer> genSortViewer();
};

#endif
