#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <any>
#include "../include/option.h"

//Class responsible for 
class Menu : public sf::RectangleShape {
    int pos = 0, pos2 = 0;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
    sf::Vector2f position;
    sf::Color backgroundColor;
    sf::Font font;
    std::vector<Option> options;
    std::vector<std::vector<Option*>> optionsGrid;
    bool gridMode, pressed, theselect = false;
public:
    Menu(int xPos, int yPos, int width, int heigth, sf::Font font, sf::Color backgroundColor = sf::Color::Transparent,bool gridmode = 0);
    void addOption(std::string text, std::function<void()> callback, int xPos, int yPos, int textsize = 24, bool centered = 0, sf::Color textColor = sf::Color::White);
    void goDown();
    void goUp();
    void goLeft();
    void goRight();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void eventHandler(const sf::Event& event);
    void runMenu(sf::RenderWindow& window, const sf::Event& event);
    void toGrid();
    void clearOptions();
};