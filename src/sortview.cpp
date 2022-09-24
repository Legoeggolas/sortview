#include "../include/sortview.hpp"

/*----------------------------------------------------------
-------------------------QUEUE ITEM-------------------------
------------------------------------------------------------*/

/*-----------------------CONSTRUCTORS------------------------*/

QueueItem::QueueItem(OP _type, size_t _pos, int _val) {
    type = _type;
    pos.first = _pos;
    pos.second = _pos;

    val = _val;
}

QueueItem::QueueItem(OP _type, std::pair<size_t, size_t> _pos, int _val) {
    type = _type;
    pos = _pos;
    val = _val;
}

/*-------------------------METHODS-------------------------*/

bool QueueItem::validPos(size_t _pos) {
    return (_pos == pos.first || _pos == pos.second);
}

/*----------------------------------------------------------
------------------------SORT VIEWER-------------------------
------------------------------------------------------------*/

/*-----------------------MEMBERS-------------------------*/
raylib::Color const SortViewer::readColor = raylib::Color(WHITE);
raylib::Color const SortViewer::writeColor = raylib::Color(GREEN);
raylib::Color const SortViewer::swapColor = raylib::Color(GREEN);
raylib::Color const SortViewer::compColor = raylib::Color(WHITE);
raylib::Color const SortViewer::elementColor = raylib::Color(RED);

/*---------------------CONSTRUCTORS-------------------------*/
SortViewer::SortViewer(std::vector<int> &_vec, int _lb, int _ub) {
    vec = _vec;
    elementUpperBound = _ub;
    elementLowerBound = _lb;

    reads = 0;
    aux_reads = 0;
    writes = 0;
    aux_writes = 0;
}

/*-------------------------METHODS-------------------------*/

void SortViewer::setBufferItem() {
    currOpBufferItem = opBuffer.begin();
}

bool SortViewer::checkBuffer() {
    return opBuffer.empty();
}

void SortViewer::removeBufferItem() {
    if (opBuffer.empty() == false) {
        auto &item = currOpBufferItem;

        if (item->type == WRITE) {
            vec[item->pos.first] = item->val;
            ++writes;
        } else if (currOpBufferItem->type == SWAP) {
            auto const &[first, second] = item->pos;
            std::swap(vec[first], vec[second]);
            writes += 2;
        } else if (currOpBufferItem->type == COMPARE) {
            ++reads;
        } else if (currOpBufferItem->type == AUXCOMPARE) {
            ++aux_reads;
        } else if (currOpBufferItem->type == AUXSWAP) {
            aux_writes += 2;
        } else if (currOpBufferItem->type == AUXWRITE) {
            ++aux_writes;
        }

        opBuffer.pop_front();

        currOpBufferItem = opBuffer.begin();
    }
}

void SortViewer::write(size_t pos, int value, bool aux) {
    if (aux) {
        opBuffer.push_back(QueueItem(AUXWRITE, pos, value));
        return;
    }
    opBuffer.push_back(QueueItem(WRITE, pos, value));
}

void SortViewer::read(size_t pos, bool aux) {
    if (aux) {
        opBuffer.push_back(QueueItem(AUXREAD, pos));
        return;
    }
    opBuffer.push_back(QueueItem(READ, pos));
}

void SortViewer::compare(size_t pos, size_t other, bool aux) {
    if (aux) {
        opBuffer.push_back(QueueItem(AUXCOMPARE, {pos, other}));
        return;
    }
    opBuffer.push_back(QueueItem(COMPARE, {pos, other}));
}

void SortViewer::swap(size_t pos, size_t other, bool aux) {
    if (aux) {
        opBuffer.push_back(QueueItem(AUXSWAP, {pos, other}));
    }
    opBuffer.push_back(QueueItem(SWAP, {pos, other}));
}

void SortViewer::display(raylib::Vector2 windowDims) {
    // centre of the line on which the visualizaton will be drawn
    raylib::Vector2 centre(windowDims.x / 2, (8 * windowDims.y) / 10);
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
            } else if (itemType == SWAP) {
                currColor = swapColor;
            } else {
                currColor = elementColor;
            }
        } else {
            currColor = elementColor;
        }

        auto const currElement = vec[pos];

        raylib::Vector2 element(begin, centre.y - (currElement)*unitElementHeight);
        element.DrawRectangle({elementWidth, currElement * unitElementHeight}, currColor);
    }

    // draw stats below the graph
    raylib::Vector2 statBox{
        windowDims.GetX() / 2 - (lineLen / 1.5f),
        (81 * windowDims.GetY()) / 100};

    // statBox.DrawRectangle({lineLen * 2, 100}, GREEN);

    float const boxBuffX = (lineLen * 2) / 9;
    float const boxBuffY = (windowDims.GetY() - centre.GetY()) / 7;
    raylib::Vector2 const boxDims{
        4 * boxBuffX,
        2.25f * boxBuffY};

    raylib::Vector2 readBox{
        statBox.GetX(),
        statBox.GetY()};
    raylib::Vector2 auxreadBox{
        statBox.GetX(),
        statBox.GetY() + boxDims.GetY() + boxBuffY};
    raylib::Vector2 writeBox{
        statBox.GetX() + boxDims.GetX() + boxBuffX,
        statBox.GetY()};
    raylib::Vector2 auxwriteBox{
        statBox.GetX() + boxDims.GetX() + boxBuffX,
        statBox.GetY() + boxDims.GetY() + boxBuffY};

    // readBox.DrawRectangle(boxDims, GREEN);
    // writeBox.DrawRectangle(boxDims, GREEN);
    // auxreadBox.DrawRectangle(boxDims, GREEN);
    // auxwriteBox.DrawRectangle(boxDims, GREEN);

    raylib::Text readText("Comparisons: " + std::to_string(reads), 30, BLACK);
    readText.spacing = 3;
    readText.Draw(readBox);

    raylib::Text auxreadText("Aux Comparisons: " + std::to_string(aux_reads), 30, BLACK);
    auxreadText.spacing = 3;
    auxreadText.Draw(auxreadBox);

    raylib::Text writeText("Writes: " + std::to_string(writes), 30, BLACK);
    writeText.spacing = 3;
    writeText.Draw(writeBox);

    raylib::Text auxwriteText("Aux Writes: " + std::to_string(aux_writes), 30, BLACK);
    auxwriteText.spacing = 3;
    auxwriteText.Draw(auxwriteBox);
}
