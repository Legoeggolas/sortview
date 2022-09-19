#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "../include/raylib-cpp.hpp"
#include "../include/state.hpp"

class UIElement {
    static size_t constructs;

   protected:
    size_t ID;

    raylib::Vector2 pos;
    raylib::Vector2 dim;

    raylib::Text text;

    bool selected;

   public:
    UIElement(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt);

    bool posInElement(raylib::Vector2 _pos);
    bool isSelected();
    size_t getID();

    virtual void display() = 0;
    virtual void onClick(raylib::Vector2 _pos = {}) = 0;
    virtual void onOtherClick() = 0;
    virtual float getCurr() = 0;
};

class Button : public UIElement {
   public:
    raylib::Color selectColor;

    Button(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt, raylib::Color _secol = {60, 64, 72});

    void display();
    void onClick(raylib::Vector2 _pos = {});
    void onOtherClick();
    float getCurr();
};

class Slider : public UIElement {
   private:
    raylib::Vector2 range;
    float curr;

   public:
    Slider(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt, raylib::Vector2 _range);

    void display();
    void onClick(raylib::Vector2 _pos);
    void onOtherClick();
    float getCurr();
};

enum SortingAlgorithm {
    MERGE,
    QUICK,
    INSERTION,
    SELECTION
};

using Element = std::pair<std::shared_ptr<UIElement>, size_t>;
class Menu {
   private:
    std::vector<Element> elements;
    State &state;

   public:
    SortingAlgorithm algo;

    Menu(State &_state);

    bool initiateStart;

    void addElement(Element ele);
    void display();
    void onClick(raylib::Vector2 pos);
};

#endif MENU_H
