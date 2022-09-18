#ifndef MENU_H
#define MENU_H

#include <memory>
#include <string>
#include <utility>

#include "../include/raylib-cpp.hpp"

class UIElement {
   protected:
    raylib::Vector2 pos;
    raylib::Vector2 dim;

    raylib::Text text;

   public:
    UIElement(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt);

    virtual void display() = 0;
    virtual void onClick() = 0;
};

class Button : public UIElement {
   public:
    bool selected;
    Button(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt);

    void display();
    void onClick();
};

class Slider : public UIElement {
   private:
    raylib::Vector2 range;
    float curr;

   public:
    Slider(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt, raylib::Vector2 _range);

    void display();
    void onClick();
};

using Element = std::shared_ptr<UIElement>;
class Menu {
   private:
    std::vector<Element> elements;

   public:
    Menu();

    void addElement(Element ele);
    void display();
};

#endif MENU_H
