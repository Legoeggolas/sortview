#include "../include/insort.hpp"

void in_sort(std::vector<int> &vec, size_t begin, size_t end, SortViewer &viewer) {
    for (size_t curr = begin + 1; curr < end; curr++) {
        int temp = vec[curr];
        viewer.read(curr);

        // find a position for the new element in the sorted section
        size_t pos = begin;
        for (; pos < curr; pos++) {
            viewer.compare(pos, curr);
            if (vec[pos] > temp) {
                break;
            }
        }

        // make a space for inserting the element
        for (size_t i = curr; i > pos; i--) {
            vec[i] = vec[i - 1];
            viewer.write(i, vec[i - 1]);
        }

        // insert the element
        vec[pos] = temp;
        viewer.write(pos, temp);
    }
}
