#include "../include/menu.h"
#include "../include/option.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Menu::Menu(int xPos, int yPos, int width, int heigth, sf::Font font, sf::Color backgroundColor, bool gridmode) : RectangleShape(sf::Vector2f(width, heigth)), gridMode(gridmode), font(font), position(sf::Vector2f(xPos, yPos)){
    setPosition(sf::Vector2f(xPos, yPos));
    setFillColor(backgroundColor);
    pos = 0;
    pos2 = 0;
    
}

void Menu::toGrid() {
    if(gridMode) {
            if(options.size() == 4) {
                optionsGrid.push_back({&options[0],&options[1]});
                optionsGrid.push_back({&options[2],&options[3]});
            }
            else std::cerr << "Wrong size";
        }
}

void Menu::addOption(std::string text, std::function<void()> callback, int xPos, int yPos, int textSize, bool isCentered, sf::Color textColor) {
    Option option(text, xPos, yPos, font, callback, textSize, textColor);
    float finalX = position.x + xPos; // Default: use the manually provided xPos

    // 2. If centerText is true, overwrite finalX with the centering math
    if (isCentered) {
        float textWidth = option.getGlobalBounds().size.x;
        finalX = position.x + ((getSize().x - textWidth) / 2.0f);
    }
    option.setTextPosition({finalX, position.y + yPos});
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
    if (gridMode) {
        optionsGrid[pos][pos2]->setHighlight(0);
        if (pos == 0) {
            pos = 1;
        }
        else {
            pos = 0;
        }
    }
    else {
        options[pos].setHighlight(0);
        if( pos < options.size()-1){
        ++pos;  
        }
        else pos = 0;
    }
      theselect = false;
}

void Menu::goUp() {
    if(gridMode) {
        optionsGrid[pos][pos2]->setHighlight(0);
        if (gridMode) {
            if (pos == 1) {
                pos = 0;
            }
            else {
                pos = 1;
            }
    }
    }
    else {
        options[pos].setHighlight(0);
        if( pos > 0){
        --pos;
        }
    else 
        pos = options.size() - 1;
    }
      theselect = false;
}

void Menu::goLeft() {
    if (gridMode) {
        optionsGrid[pos][pos2]->setHighlight(0);
         if (pos2 == 1) {
                pos2 = 0;
            }
            else {
                pos2 = 1;
            }
            theselect = false;
    }
}

void Menu::goRight() {
    if (gridMode) {
        optionsGrid[pos][pos2]->setHighlight(0);
         if (pos2 == 0) {
                pos2 = 1;
            }
            else {
                pos2 = 0;
            }
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
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
            goLeft();
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
            goRight();
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter && !theselect) {
            theselect = true;
            if (gridMode) optionsGrid[pos][pos2]->trigger();
            else options[pos].trigger();
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
    if (gridMode == 1) optionsGrid[pos][pos2]->setHighlight(1);
    else options[pos].setHighlight(1);
}

void Menu::runMenu(sf::RenderWindow& window, const sf::Event& event) {
    eventHandler(event);
    update(window);
    draw(window);
}
