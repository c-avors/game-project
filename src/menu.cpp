#include "../include/menu.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Menu::Menu(int xPos, int yPos, int width, int heigth, sf::Font font, sf::Color backgroundColor, bool gridmode) : RectangleShape(sf::Vector2f(width, heigth)), gridMode(gridmode), font(font), position(sf::Vector2f(xPos, yPos)){
    setPosition(sf::Vector2f(xPos, yPos));
    setFillColor(backgroundColor);
    pos = 0;

}

void Menu::addOption(std::string text, int xPos, int yPos, int textSize, sf::Color textColor) {
    sf::Text option(font);
    if(yPos+option.getGlobalBounds().size.y < position.x+getGlobalBounds().size.x){
        option.setString(text);
        option.setPosition(sf::Vector2f(position.x+xPos, position.y+yPos));
        option.setCharacterSize(textSize);
        option.setFillColor(textColor);
        options.emplace_back(option);
    }
    else std::cout << "Out of bounds" << std::endl;
    
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(*this);
    for (auto& option : options) {
        window.draw(option);
    }
}

//Menu navigation

void Menu::goDown() {
    if( pos < static_cast<int>(options.size()) - 1){
        options[pos].setOutlineThickness(0);
        ++pos;
        theselect = false;
      }
}

void Menu::goUp() {
    if( pos > 0){
        options[pos].setOutlineThickness(0);
        --pos;
        theselect = false;
      }
}

void Menu::eventHandler(const sf::Event& event) {
    if (options.empty()) return;

    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
            goDown();
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
            goUp();
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && !theselect) {
            theselect = true;
            std::cout << "Selected option index: " << pos << std::endl;
        }
    }
}

void Menu::update(sf::RenderWindow& window) {
    if (options.empty()) return;

    pos_mouse = sf::Mouse::getPosition(window);
    mouse_coord = window.mapPixelToCoords(pos_mouse);

    // Apply active highlight styling
    options[pos].setOutlineColor(sf::Color::Yellow);
    options[pos].setOutlineThickness(3);
}

void Menu::runMenu(sf::RenderWindow& window, const sf::Event& event) {
    eventHandler(event);
    update(window);
    draw(window);
}
