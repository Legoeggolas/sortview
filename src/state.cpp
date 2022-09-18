#include "../include/state.hpp"

State::State(size_t _vec_size, int _lb, int _ub, int _fps) {
    vec_size = _vec_size;
    elementLowerBound = _lb;
    elementUpperBound = _ub;
    fps = _fps;
}

std::unique_ptr<SortViewer> State::genSortViewer() {
    vec = std::vector<int>(vec_size);

    std::random_device device;
    std::mt19937 engine{device()};
    std::uniform_int_distribution<int> dist{elementLowerBound, elementUpperBound};
    std::generate(
        std::begin(vec), std::end(vec), [&dist, &engine]() -> int {
            return dist(engine);
        });

    if (status == SORTED) {
        std::sort(vec.begin(), vec.end());
    } else if (status == REVERSE) {
        std::sort(vec.begin(), vec.end(), std::greater<int>());
    }

    auto msv = std::unique_ptr<SortViewer>{new SortViewer(vec, elementLowerBound, elementUpperBound)};
    return msv;
}
