#include "selsort.hpp"

void sel_sort(std::vector<int> &vec, size_t begin, size_t end, SortViewer &viewer) {
    for (size_t curr = begin; curr < end; curr++) {
        // find the position of the smallest element
        size_t pos = curr;
        for (size_t i = curr + 1; i < end; i++) {
            viewer.compare(pos, i);
            if (vec[pos] > vec[i]) {
                pos = i;
            }
        }

        // swap the element into the sorted array
        std::swap(vec[pos], vec[curr]);
        viewer.swap(pos, curr);
    }
}
