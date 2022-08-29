#ifndef SORT_VIEW_H
#define SORT_VIEW_H

#include <deque>
#include <iostream>
#include <vector>

#include "../include/raylib-cpp.hpp"

/**
 * @brief Identifes the kinds of operations that can be displayed by the SortViewer.
 * READ identifies a read operation.
 * WRITE identifies a write operation.
 */
enum OP { READ,
          WRITE };

/**
 * @brief A utility class that stores the data related to a single operation.
 *
 */
class QueueItem {
   public:
    OP type;
    size_t pos;
    int val;

    /**
     * @brief Construct a new Queue Item object.
     *
     * @param _type The type of the operation, supports the OP enumerator.
     * @param _pos The vector position this operation is performed on.
     * @param _val Optional. The updated value in this position. Defaults to 0.
     */
    QueueItem(OP _type, size_t _pos, int _val = 0) {
        type = _type;
        pos = _pos;
        val = _val;
    }
};

/**
 * @brief Visualizes a sorting algorithm.
 * Packages together multiple tools to generate a visualization.
 * All the operations performed on a copy of the vector an instance is associated with are
 * recorded in a deque.
 * Afterwards, all these operations are performed on the original vector and displayed.
 * @see QueueItem
 */
class SortViewer {
   private:
    std::vector<int> vec;            // the internal vector instance
    int elementUpperBound;           // the maximum possible value of an element
    int elementLowerBound;           // the minimum possible value of an element
    std::deque<QueueItem> opBuffer;  // a queue of operations performed by an algorithm

   public:
    std::deque<QueueItem>::iterator currOpBufferItem;  // public iterator to the operation buffer

    /**
     * @brief Construct a new Sort Viewer object
     *
     * @param _vec A reference to the original vector.
     * @param _lb Optional. The minimum possible value of an element. Defaults to 1.
     * @param _ub Optional. The maximum possible value of an element. Defaults tp 1024.
     */
    SortViewer(std::vector<int> &_vec, int _lb = 1, int _ub = 1024) {
        vec = _vec;
        elementUpperBound = _ub;
        elementLowerBound = _lb;
    }

    /**
     * @brief Set the Buffer Item iterator.
     *
     */
    void setBufferItem() {
        currOpBufferItem = opBuffer.begin();
    }

    /**
     * @brief Checks whether the operation buffer is empty or not.
     * If this returns true, currOpBufferItem goes out of bounds.
     * @return true if the buffer is empty.
     * @return false if the buffer is not empty.
     */
    bool checkBuffer() {
        return opBuffer.empty();
    }

    /**
     * @brief Removes the operation at the front of the operation buffer.
     * Resets the currOpBufferItem iterator.
     *
     */
    void removeBufferItem() {
        if (opBuffer.empty() == false) {
            if (currOpBufferItem->type == WRITE) {
                vec[currOpBufferItem->pos] = currOpBufferItem->val;
            }
            opBuffer.pop_front();

            currOpBufferItem = opBuffer.begin();
        }
    }

    /**
     * @brief Records a write operation.
     *
     * @param pos The position that gets written to.
     * @param value The value that gets written to this position.
     */
    void write(size_t pos, int value) {
        // vec[pos] = value;
        opBuffer.push_back(QueueItem(WRITE, pos, value));
    }

    /**
     * @brief Records a read operation.
     *
     * @param pos The position that gets read from.
     */
    void read(size_t pos) {
        opBuffer.push_back(QueueItem(READ, pos));
        // return vec[pos];
    }

    /**
     * @brief Displays the current state of the internal vector.
     * Elements that have operations being performed on them are highlighted
     * in different colors.
     * @param windowDims Dimensions of the display window.
     */
    void display(raylib::Vector2 windowDims);
};

#endif
