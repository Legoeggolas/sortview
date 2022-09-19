#include "../include/menu.hpp"

size_t UIElement::constructs = 0;

UIElement::UIElement(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt) {
    pos = _pos;
    dim = _dim;
    text = _txt;

    ID = constructs;

    std::cout << "Created UIElement called " << text.GetText() << " with ID " << ID << "\n";

    constructs++;
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

bool UIElement::isSelected() {
    return selected;
}

size_t UIElement::getID() {
    return ID;
}

Button::Button(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt, raylib::Color _secol) : UIElement(_pos, _dim, _txt) {
    selected = false;
    selectColor = _secol;
}

void Button::display() {
    raylib::Rectangle body{pos, dim};
    body.DrawRoundedLines(0.25, 1000, 3, BLACK);
    if (selected) {
        body.DrawRounded(0.25, 1000, selectColor);
    }

    raylib::Vector2 textPos{
        pos.x + (dim.x - (float)text.Measure()) / 2,
        pos.y + (dim.y - text.GetFontSize()) / 2};

    text.spacing = 3;
    text.Draw(textPos);
}

void Button::onClick(raylib::Vector2 _pos) {
    selected = !selected;
}

void Button::onOtherClick() {
    selected = false;
}

float Button::getCurr() {
    return 0.0;
}

Slider::Slider(raylib::Vector2 _pos, raylib::Vector2 _dim, raylib::Text _txt, raylib::Vector2 _range) : UIElement(_pos, _dim, _txt) {
    range = _range;
    curr = 0;
    selected = true;
}

void Slider::display() {
    raylib::Rectangle body{pos, dim};
    body.DrawRoundedLines(0.25, 1000, 3, BLACK);

    raylib::Rectangle scale{
        {pos.x + dim.x / 9, pos.y + dim.y / 2},
        {5 * dim.x / 9, dim.y / 15}};

    scale.DrawRounded(0.75, 20, GRAY);

    float const circleRadius = scale.GetHeight();
    raylib::Vector2 circleCentre{
        scale.GetPosition().x + circleRadius + (scale.GetWidth() - 2 * circleRadius) * curr,
        scale.GetPosition().y + scale.GetHeight() / 2};

    circleCentre.DrawCircle(circleRadius, DARKGRAY);
    DrawCircleLines(circleCentre.x, circleCentre.y, circleRadius, BLACK);

    raylib::Rectangle counter{
        {pos.x + 7 * dim.x / 9, pos.y + dim.y / 4},
        {3 * dim.x / 18, dim.y / 2}};

    counter.Draw(GRAY);

    raylib::Text counterText(std::to_string((int)(range.x + (range.y - range.x) * curr)), counter.GetHeight() / 3, BLACK);
    raylib::Vector2 counterTextPos{
        counter.GetPosition().x + (counter.GetWidth() - counterText.Measure()) / 2,
        counter.GetPosition().y + (counter.GetHeight() - counterText.fontSize) / 2};

    counterText.spacing = 3;
    counterText.Draw(counterTextPos);

    raylib::Vector2 textPos{
        pos.x + (dim.x - (float)text.Measure()) / 2,
        pos.y + dim.y / 3 + (dim.y - text.GetFontSize()) / 2};

    text.spacing = 3;
    text.Draw(textPos);
}

void Slider::onClick(raylib::Vector2 _pos) {
    _pos.x -= pos.x;
    _pos.y -= pos.y;

    raylib::Vector2 scaleDims{
        dim.x / 9,
        6 * dim.x / 9};

    if (_pos.x <= scaleDims.GetX()) {
        curr = 0.0;
        return;
    }

    if (_pos.x >= scaleDims.GetY()) {
        curr = 1.0;
        return;
    }

    _pos.x -= scaleDims.GetX();

    curr = _pos.x / (5 * dim.x / 9 - dim.y / 15);

    if ((int)curr >= 1) {
        curr = 1.0;
    }
}

void Slider::onOtherClick() {
}

float Slider::getCurr() {
    return range.GetX() + curr * (range.GetY() - range.GetX());
}

Menu::Menu(State &_state) : state(_state) {
    initiateStart = false;
}

void Menu::addElement(Element ele) {
    elements.push_back(ele);
    std::cout << "Added element with ID " << ele.first->getID() << " in group " << ele.second << "\n";
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
            ptr->onClick(pos);
            group = grp;
            elePtr = ptr;
            break;
        }
    }

    if (!group) {
        return;
    }

    if (group == 1) {
        for (auto const &ele : elements) {
            auto const &[ptr, grp] = ele;

            if (ptr->isSelected() == false) {
                continue;
            }

            if (grp == 2) {
                switch (ptr->getID()) {
                    case 0:
                        algo = MERGE;
                        std::cout << "Registered MERGE SORT\n";
                        break;
                    case 1:
                        algo = QUICK;
                        std::cout << "Registered QUICK SORT\n";
                        break;
                    case 2:
                        algo = INSERTION;
                        std::cout << "Registered INSERTION SORT\n";
                        break;
                    case 3:
                        algo = SELECTION;
                        std::cout << "Registered SELECTION SORT\n";
                        break;
                    default:
                        algo = MERGE;
                        std::cout << "Registered MERGE SORT (DEF)\n";
                        break;
                }
            } else if (grp == 3) {
                switch (ptr->getID()) {
                    case 4:
                        state.status = RANDOM;
                        std::cout << "Registered RANDOM\n";
                        break;
                    case 5:
                        state.status = SORTED;
                        std::cout << "Registered SORTED\n";
                        break;
                    case 6:
                        state.status = REVERSE;
                        std::cout << "Registered REVERSE\n";
                        break;
                    default:
                        state.status = RANDOM;
                        std::cout << "Registered RANDOM (DEF)\n";
                        break;
                }
            } else if (grp == 0) {
                switch (ptr->getID()) {
                    case 8:
                        state.vec_size = ptr->getCurr();
                        std::cout << "Registered VEC SIZE as: " << state.vec_size << "\n";
                        break;
                    case 9:
                        state.fps = ptr->getCurr();
                        std::cout << "Registered FPS as: " << state.fps << "\n";
                        break;
                    default:
                        state.vec_size = 5;
                        state.fps = 60;
                        std::cout << "Registered VEC SIZE (def) as: " << state.vec_size;
                        std::cout << "\nRegistered FPS (def) as: " << state.fps << "\n";
                        break;
                }
            }
        }

        initiateStart = true;
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
