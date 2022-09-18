#ifndef STATE_H
#define STATE_H

#include <algorithm>
#include <memory>
#include <random>
#include <vector>

#include "../include/sortview.hpp"

enum VectorSortStatus {
    RANDOM,
    SORTED,
    REVERSE
};
class State {
   public:
    std::vector<int> vec;
    int elementLowerBound;
    int elementUpperBound;
    size_t vec_size;
    int fps;
    VectorSortStatus status;

    State(size_t _vec_size = 10, int _lb = 1, int _ub = 1024, int _fps = 60);

    std::unique_ptr<SortViewer> genSortViewer();
};

#endif
