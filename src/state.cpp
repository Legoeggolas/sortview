#include "../include/state.hpp"

State::State(size_t _vec_size, int _lb, int _ub) {
    vec_size = _vec_size;
    elementLowerBound = _lb;
    elementUpperBound = _ub;
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

    auto msv = std::unique_ptr<SortViewer>{new SortViewer(vec, elementLowerBound, elementUpperBound)};
    return msv;
}
