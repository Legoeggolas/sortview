#include "../include/menu.hpp"

UIElement::UIElement(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt) {
    pos = _pos;
    dim = _dim;
    text = _txt;
}

Button::Button(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt) : UIElement(_pos, _dim, _txt) {
    selected = false;
}

void Button::display() {
    raylib::Rectangle body{pos, dim};
    body.DrawRoundedLines(0.25, 1000, 3, BLACK);

    raylib::Vector2 textPos{};
    textPos.y = pos.y + (dim.y - text.GetFontSize()) / 2;
    textPos.x = pos.x + (dim.x - (float)text.Measure()) / 2;
    raylib::Text::Draw(text.GetText(), textPos, text.GetFontSize(), text.GetColor());
}

void Button::onClick() {
    selected = !selected;
}

Slider::Slider(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt, raylib::Vector2 _range) : UIElement(_pos, _dim, _txt) {
    range = _range;
    curr = 0;
}

void Slider::display() {
}

void Slider::onClick() {
}

Menu::Menu() {
}

void Menu::addElement(Element ele) {
    elements.push_back(ele);
}

void Menu::display() {
    for (auto const &ele : elements) {
        ele->display();
    }
}
