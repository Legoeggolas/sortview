#include "sortview.hpp"

raylib::Color const SortViewer::readColor = raylib::Color(WHITE);
raylib::Color const SortViewer::writeColor = raylib::Color(GREEN);
raylib::Color const SortViewer::swapColor = raylib::Color(GREEN);
raylib::Color const SortViewer::compColor = raylib::Color(WHITE);
raylib::Color const SortViewer::elementColor = raylib::Color(RED);

void SortViewer::display(raylib::Vector2 windowDims) {
    // centre of the line on which the visualizaton will be drawn
    raylib::Vector2 centre(windowDims.x / 2, (9 * windowDims.y) / 10);
    float const lineLen = (97 * centre.x) / 100;
    float const lineThickness = 3;
    centre.DrawLine({centre.x + lineLen, centre.y}, lineThickness, BLACK);
    centre.DrawLine({centre.x - lineLen, centre.y}, lineThickness, BLACK);

    size_t const n_elements = vec.size();
    float elementWidth = (2 * lineLen) / n_elements;
    if ((int)elementWidth == 0) {
        std::cerr << "elementWidth is 0!\n";
    }

    float const maxElementHeight = (4 * centre.y) / 5;
    float const unitElementHeight = maxElementHeight / (elementUpperBound - elementLowerBound);

    size_t pos = 0;
    for (float begin = centre.x - lineLen; begin <= centre.x + lineLen;
         begin += elementWidth, pos++) {
        if (pos == n_elements) {
            break;
        }

        // highlight elements being operated on
        raylib::Color currColor;
        if (!checkBuffer() && currOpBufferItem->validPos(pos)) {
            auto itemType = currOpBufferItem->type;
            if (itemType == READ) {
                currColor = readColor;
            } else if (itemType == WRITE) {
                currColor = writeColor;
            } else if (itemType == COMPARE) {
                currColor = compColor;
            } else {
                currColor = swapColor;
            }
        } else {
            currColor = elementColor;
        }

        auto const currElement = vec[pos];

        raylib::Vector2 element(begin, centre.y - (currElement)*unitElementHeight);
        element.DrawRectangle({elementWidth, currElement * unitElementHeight}, currColor);
    }
}
