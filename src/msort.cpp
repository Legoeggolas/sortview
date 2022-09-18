#include "../include/msort.hpp"

void merge(std::vector<int> &vec,
           size_t beginFirst,
           size_t endFirst,
           size_t beginSecond,
           size_t endSecond,
           SortViewer &viewer) {
    auto const begin = beginFirst;

    std::vector<int> temp(endSecond - beginFirst);
    auto it = temp.begin();

    while (beginFirst != endFirst && beginSecond != endSecond) {
        viewer.compare(beginFirst, beginSecond);

        if (vec[beginFirst] <= vec[beginSecond]) {
            *it = vec[beginFirst];
            viewer.read(beginFirst);
            beginFirst++;
        } else {
            *it = vec[beginSecond];
            viewer.read(beginSecond);
            beginSecond++;
        }

        it++;
    }

    while (beginFirst != endFirst) {
        *it = vec[beginFirst];
        viewer.read(beginFirst);
        it++;
        beginFirst++;
    }

    while (beginSecond != endSecond) {
        *it = vec[beginSecond];
        viewer.read(beginSecond);
        it++;
        beginSecond++;
    }

    it = temp.begin();
    beginFirst = begin;
    for (; beginFirst != endSecond; beginFirst++, it++) {
        vec[beginFirst] = *it;
        viewer.write(beginFirst, *it);
    }
}

void m_sort(std::vector<int> &vec, size_t begin, size_t end, SortViewer &viewer) {
    if (end - begin <= 1) {
        return;
    }

    auto mid = begin + (end - begin) / 2;

    m_sort(vec, begin, mid, viewer);
    m_sort(vec, mid, end, viewer);

    merge(vec, begin, mid, mid, end, viewer);
}
