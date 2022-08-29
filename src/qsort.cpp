#include "qsort.hpp"

// the partitioning co-routine
// uses pivot() function to decide the pivot's index
// then swaps the pivot element into a position where all elements to the right are strictly greater
// uses comp() to decide ordering
int _partition(std::vector<int> &arr, size_t lo, size_t hi, SortViewer &viewer) {
    int pvt = lo + (hi - lo) / 2;

    // assert(pvt >= lo && pvt < hi);

    // put the pivot element at the end of the array
    viewer.write(hi - 1, arr[pvt]);
    viewer.write(pvt, arr[hi - 1]);
    std::swap(arr.at(pvt), arr.at(hi - 1));
    //_swap(arr, pvt, hi - 1, size);

    int index = lo - 1;  // stores the pos after which all elements are larger than our pivot

    for (int seeker = lo; seeker < hi - 1; seeker++) {
        if (arr[seeker] < arr[hi - 1]) {
            viewer.write(seeker, arr[index + 1]);
            viewer.write(index + 1, arr[seeker]);
            std::swap(arr.at(seeker), arr.at(index + 1));
            //_swap(arr, index + 1, seeker, size);
            index++;
        }
    }
    // place the pivot in its proper position
    viewer.write(index + 1, arr[hi - 1]);
    viewer.write(hi - 1, arr[index + 1]);
    std::swap(arr.at(index + 1), arr.at(hi - 1));
    //_swap(arr, index + 1, hi - 1, size);

    return index + 1;
}

// stack space optimized implementation of quick sort
// takes log(n) auxiliary space on the stack
void _sort(std::vector<int> &arr, size_t lo, size_t hi, SortViewer &viewer) {
    while (lo < hi) {
        int pvt = _partition(arr, lo, hi, viewer);

        // make a recursive call for the smaller subarray
        if (pvt - lo < hi - pvt) {
            _sort(arr, lo, pvt, viewer);
            lo = pvt + 1;
        } else {
            _sort(arr, pvt + 1, hi, viewer);
            hi = pvt;
        }
    }
}

void q_sort(std::vector<int> &vec, size_t begin, size_t end, SortViewer &viewer) {
    if (end - begin <= 1) {
        return;
    }

    _sort(vec, 0, end, viewer);
}
