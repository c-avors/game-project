#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Option : public sf::Text {
    bool focused;
public:
    void unfocus();
    void focus();
};