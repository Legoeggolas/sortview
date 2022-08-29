#include "msort.hpp"

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
        // viewer.read(beginFirst);
        // viewer.read(beginSecond);
        if (vec[beginFirst] <= vec[beginSecond]) {
            *it = vec[beginFirst];
            beginFirst++;
        } else {
            *it = vec[beginSecond];
            beginSecond++;
        }

        it++;
    }

    while (beginFirst != endFirst) {
        *it = vec[beginFirst];
        it++;
        beginFirst++;
    }

    while (beginSecond != endSecond) {
        *it = vec[beginSecond];
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

/*
bool isSorted(vecIter begin, vecIter end) {
    for (auto hare = begin + 1; hare != end; hare++, begin++) {
        if (*hare < *begin) {
            return false;
        }
    }

    return true;
}


int main() {
    std::vector<int> vec(100000);

    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
    std::uniform_int_distribution<int> dist{1, 1024};

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    std::generate(std::begin(vec), std::end(vec), gen);
    assert(isSorted(vec.begin(), vec.end()) == false);

    msort(vec.begin(), vec.end());

    assert(isSorted(vec.begin(), vec.end()));

    std::cout << "Done";

    return 0;
}
*/
