#include <random>

#include "../include/raylib-cpp.hpp"
#include "../include/raylib.h"
#include "msort.hpp"
#include "qsort.hpp"
#include "sortview.hpp"

int main() {
    int const screenWidth = 1920;
    int const screenHeight = 1080;

    // Define vector and some bound metadata
    std::vector<int> vec(500);
    int const elementLowerBound = 1;
    int const elementUpperBound = 100;

    // Fill the vector with random numbers
    std::random_device device;
    std::mt19937 engine{device()};
    std::uniform_int_distribution<int> dist{elementLowerBound, elementUpperBound};
    std::generate(
        std::begin(vec), std::end(vec), [&dist, &engine]() -> int {
            return dist(engine);
        });

    // Create a SortViewer
    SortViewer msv(vec, elementLowerBound, elementUpperBound);

    // Create a copy of the vector
    auto temp(vec);

    // Send the copy as a parameter to a sorting algorithm
    // q_sort(temp, 0, vec.size(), msv);
    m_sort(vec, 0, vec.size(), msv);

    // Initialize buffer iterator
    msv.setBufferItem();

    // Raylib window functions
    raylib::Window window(screenWidth, screenHeight, "msortview");

    SetTargetFPS(90);

    while (!window.ShouldClose()) {
        BeginDrawing();

        window.ClearBackground(raylib::Color(40, 44, 52));
        msv.display({screenWidth, screenHeight});

        EndDrawing();

        msv.removeBufferItem();  // go to the next buffer item
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
