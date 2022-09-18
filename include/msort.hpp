#ifndef M_SORT_H
#define M_SORT_H

#include "sortview.hpp"

/**
 * @brief A SortView compatible implementation of merge sort.
 *
 * @param vec A copy of the vector that is to be visualized while being sorted.
 * @param begin The position of the first element to be sorted.
 * @param end The position of the last element to be sorted.
 * @param viewer A reference to a SortViewer object to record operations.
 */
void m_sort(std::vector<int> &vec, size_t begin, size_t end, SortViewer &viewer);

#endif
