#include "../include/menu.hpp"

UIElement::UIElement(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt) {
    pos = _pos;
    dim = _dim;
    text = _txt;
}

bool UIElement::posInElement(raylib::Vector2 _pos) {
    _pos.x -= pos.x;
    _pos.y -= pos.y;

    if (_pos.x >= 0 && _pos.y >= 0) {
        if (_pos.x <= dim.x && _pos.y <= dim.y) {
            return true;
        }
    }

    return false;
}

Button::Button(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt) : UIElement(_pos, _dim, _txt) {
    selected = false;
}

void Button::display() {
    raylib::Rectangle body{pos, dim};
    body.DrawRoundedLines(0.25, 1000, 3, BLACK);
    if (selected) {
        body.DrawRounded(0.25, 1000, raylib::Color(60, 64, 72));
    }

    raylib::Vector2 textPos{};
    textPos.y = pos.y + (dim.y - text.GetFontSize()) / 2;
    textPos.x = pos.x + (dim.x - (float)text.Measure()) / 2;

    raylib::Text::Draw(text.GetText(), textPos, text.GetFontSize(), text.GetColor());
}

void Button::onClick() {
    selected = !selected;
}

void Button::onOtherClick() {
    selected = false;
}

Slider::Slider(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt, raylib::Vector2 _range) : UIElement(_pos, _dim, _txt) {
    range = _range;
    curr = 0;
}

void Slider::display() {
}

void Slider::onClick() {
}

void Slider::onOtherClick() {
}

Menu::Menu() {
}

void Menu::addElement(Element ele) {
    elements.push_back(ele);
}

void Menu::display() {
    for (auto const &ele : elements) {
        ele.first->display();
    }
}

void Menu::onClick(raylib::Vector2 pos) {
    size_t group = 0;
    auto elePtr = std::shared_ptr<UIElement>{};
    for (auto const &ele : elements) {
        auto const &[ptr, grp] = ele;
        if (ptr->posInElement(pos)) {
            ptr->onClick();
            group = grp;
            elePtr = ptr;
            break;
        }
    }

    if (!group) {
        return;
    }

    for (auto const &ele : elements) {
        auto const &[ptr, grp] = ele;
        if (grp != group) {
            continue;
        }

        if (ptr == elePtr) {
            continue;
        }

        ptr->onOtherClick();
    }
}
