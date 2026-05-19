#include "../include/menu.h"
#include "../include/option.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Menu::Menu(int xPos, int yPos, int width, int heigth, sf::Font font, sf::Color backgroundColor, bool gridmode) : RectangleShape(sf::Vector2f(width, heigth)), gridMode(gridmode), font(font), position(sf::Vector2f(xPos, yPos)){
    setPosition(sf::Vector2f(xPos, yPos));
    setFillColor(backgroundColor);
    pos = 0;

}

void Menu::addOption(std::string text, std::function<void()> callback, int xPos, int yPos, int textSize, sf::Color textColor) {
    Option option(text, xPos, yPos, font, callback, textSize, textColor);
    options.push_back(option);
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
        options[pos].setHighlight(0);
        ++pos;
        theselect = false;
      }
}

void Menu::goUp() {
    if( pos > 0){
        options[pos].setHighlight(0);
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
            options[pos].trigger();
        }
    }

    if (const auto* keyReleased = event.getIf<sf::Event::KeyReleased>()) {
        if (keyReleased->scancode == sf::Keyboard::Scancode::Enter) {
            theselect = false; 
        }
    }

}

void Menu::update(sf::RenderWindow& window) {
    if (options.empty()) return;

    pos_mouse = sf::Mouse::getPosition(window);
    mouse_coord = window.mapPixelToCoords(pos_mouse);

    //Highlight selected option
    options[pos].setHighlight(1);
}

void Menu::runMenu(sf::RenderWindow& window, const sf::Event& event) {
    eventHandler(event);
    update(window);
    draw(window);
}
