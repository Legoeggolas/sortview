#include "../include/insort.hpp"
#include "../include/menu.hpp"
#include "../include/msort.hpp"
#include "../include/qsort.hpp"
#include "../include/raylib-cpp.hpp"
#include "../include/raylib.h"
#include "../include/selsort.hpp"
#include "../include/sortview.hpp"
#include "../include/state.hpp"

#ifndef CON
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
    int const screenWidth = 1920;
    int const screenHeight = 1080;

    // Define vector and some bound metadata
    size_t const vec_size = 10;
    int const elementLowerBound = 1;
    int const elementUpperBound = 100;

    // Create State

    State state(vec_size, elementLowerBound, elementUpperBound);

    // Create a SortViewer
    auto msv = state.genSortViewer();

    // Run a sorting algorithm
    // q_sort(state.vec, 0, state.vec.size(), *msv);
    //
    // in_sort(state.vec, 0, state.vec.size(), (msv);
    // sel_sort(state.vec, 0, state.vec.size(), *msv);

    // Raylib window functions
    raylib::Window window(screenWidth, screenHeight, "msortview");

    SetTargetFPS(state.fps);

    Menu menu{state};
    menu.addElement({std::unique_ptr<UIElement>{new Button({screenWidth / 20, screenHeight / 10}, {300, 200}, raylib::Text("Merge Sort", 30, BLACK))}, 2});
    menu.addElement({std::unique_ptr<UIElement>{new Button({300 + 2 * screenWidth / 20, screenHeight / 10}, {300, 200}, raylib::Text("Quick Sort", 30, BLACK))}, 2});
    menu.addElement({std::unique_ptr<UIElement>{new Button({600 + 3 * screenWidth / 20, screenHeight / 10}, {300, 200}, raylib::Text("Insertion Sort", 30, BLACK))}, 2});
    menu.addElement({std::unique_ptr<UIElement>{new Button({900 + 4 * screenWidth / 20, screenHeight / 10}, {300, 200}, raylib::Text("Selection Sort", 30, BLACK))}, 2});

    menu.addElement({std::unique_ptr<UIElement>{new Button({screenWidth / 20, 4 * screenHeight / 10}, {300, 200}, raylib::Text("Random", 30, BLACK))}, 3});
    menu.addElement({std::unique_ptr<UIElement>{new Button({300 + 2 * screenWidth / 20, 4 * screenHeight / 10}, {300, 200}, raylib::Text("Sorted", 30, BLACK))}, 3});
    menu.addElement({std::unique_ptr<UIElement>{new Button({600 + 3 * screenWidth / 20, 4 * screenHeight / 10}, {300, 200}, raylib::Text("Reverse Sorted", 30, BLACK))}, 3});

    menu.addElement({std::unique_ptr<UIElement>{new Button({1200 + 4 * screenWidth / 20, 4 * screenHeight / 10}, {300, 200}, raylib::Text("START", 30, BLACK), GREEN)}, 1});

    menu.addElement({std::unique_ptr<UIElement>{new Slider({screenWidth / 20, 7 * screenHeight / 10}, {750, 200}, raylib::Text("Size of the Vector", 35, BLACK), {1, 500})}, 0});
    menu.addElement({std::unique_ptr<UIElement>{new Slider({750 + 2 * screenWidth / 20, 7 * screenHeight / 10}, {750, 200}, raylib::Text("Frame Rate (Speed)", 35, BLACK), {15, 300})}, 0});

    bool initiated = false;
    while (!window.ShouldClose()) {
        BeginDrawing();

        window.ClearBackground(raylib::Color(40, 44, 52));

        if (menu.initiateStart) {
            if (!initiated) {
                msv = state.genSortViewer();
                switch (menu.algo) {
                    case MERGE:
                        m_sort(state.vec, 0, state.vec.size(), *msv);
                        std::cout << "Ran msort"
                                  << "\n";
                        break;
                    case QUICK:
                        q_sort(state.vec, 0, state.vec.size(), *msv);
                        std::cout << "Ran qsort"
                                  << "\n";
                        break;
                    case INSERTION:
                        in_sort(state.vec, 0, state.vec.size(), *msv);
                        std::cout << "Ran insort"
                                  << "\n";
                        break;
                    case SELECTION:
                        sel_sort(state.vec, 0, state.vec.size(), *msv);
                        std::cout << "Ran selsort"
                                  << "\n";
                        break;
                    default:
                        m_sort(state.vec, 0, state.vec.size(), *msv);
                        std::cout << "Ran msort (def)"
                                  << "\n";
                        break;
                }

                // Initialize buffer iterator
                msv->setBufferItem();
                initiated = true;
            }

            msv->display({screenWidth, screenHeight});
        } else {
            menu.display();
        }

        EndDrawing();

        if (raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT)) {
            menu.onClick(raylib::Mouse::GetPosition());
        }

        msv->removeBufferItem();  // go to the next buffer item
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
