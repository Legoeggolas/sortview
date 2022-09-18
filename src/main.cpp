#include "../include/insort.hpp"
#include "../include/msort.hpp"
#include "../include/qsort.hpp"
#include "../include/raylib-cpp.hpp"
#include "../include/raylib.h"
#include "../include/selsort.hpp"
#include "../include/sortview.hpp"
#include "../include/state.hpp"

int main() {
    int const screenWidth = 1920;
    int const screenHeight = 1080;

    // Define vector and some bound metadata
    size_t const vec_size = 100;
    int const elementLowerBound = 1;
    int const elementUpperBound = 100;

    // Create State

    State state(vec_size, elementLowerBound, elementUpperBound);

    // Create a SortViewer
    auto msv = state.genSortViewer();

    // Run a sorting algorithm
    q_sort(state.vec, 0, state.vec.size(), *msv);
    // m_sort(state.vec, 0, state.vec.size(), *msv);
    // in_sort(state.vec, 0, state.vec.size(), (msv);
    // sel_sort(state.vec, 0, state.vec.size(), *msv);

    // Initialize buffer iterator
    msv->setBufferItem();

    // Raylib window functions
    raylib::Window window(screenWidth, screenHeight, "msortview");

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        BeginDrawing();

        window.ClearBackground(raylib::Color(40, 44, 52));
        msv->display({screenWidth, screenHeight});

        EndDrawing();

        msv->removeBufferItem();  // go to the next buffer item
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
