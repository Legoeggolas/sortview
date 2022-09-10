#ifndef SORT_VIEW_H
#define SORT_VIEW_H

#include <deque>
#include <iostream>
#include <utility>
#include <vector>

#include "../include/raylib-cpp.hpp"

/**
 * @brief Identifes the kinds of operations that can be displayed by the SortViewer.
 * READ identifies a read operation.
 * WRITE identifies a write operation.
 */
enum OP { READ,
          WRITE,
          SWAP,
          COMPARE };

/**
 * @brief A utility class that stores the data related to a single operation.
 *
 */
class QueueItem {
   public:
    OP type;
    std::pair<size_t, size_t> pos;
    int val;

    /**
     * @brief Construct a new Queue Item object.
     *
     * @param _type The type of the operation, supports the OP enumerator.
     * @param _pos The vector position this operation was performed on.
     * @param _val Optional. The updated value in this position. Defaults to 0.
     */
    QueueItem(OP _type, size_t _pos, int _val = 0) {
        type = _type;
        pos.first = _pos;
        pos.second = _pos;
        val = _val;
    }

    /**
     * @brief Construct a new Queue Item object.
     *
     * @param _type The type of the operation, supports the OP enumerator.
     * @param _pos A pair of vector positions this operation was performed on.
     */
    QueueItem(OP _type, std::pair<size_t, size_t> _pos) {
        type = _type;
        pos = _pos;
    }

    bool validPos(size_t _pos) {
        return (_pos == pos.first || _pos == pos.second);
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

    static raylib::Color const readColor;
    static raylib::Color const writeColor;
    static raylib::Color const swapColor;
    static raylib::Color const compColor;
    static raylib::Color const elementColor;

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
            auto &item = currOpBufferItem;
            if (item->type == WRITE) {
                vec[item->pos.first] = item->val;
            } else if (currOpBufferItem->type == SWAP) {
                auto const &[first, second] = item->pos;
                std::swap(vec[first], vec[second]);
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
     * @brief Records a comparison operation
     *
     * @param pos One of the positions being compared.
     * @param other The other position being compared.
     */
    void compare(size_t pos, size_t other) {
        opBuffer.push_back(QueueItem(COMPARE, {pos, other}));
    }

    /**
     * @brief Records a swap operation.
     *
     * @param pos One of the positions having their values swapped.
     * @param other The other position having its value swapped.
     */
    void swap(size_t pos, size_t other) {
        opBuffer.push_back(QueueItem(SWAP, {pos, other}));
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
