#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//Class responsible for 
class Menu : public sf::RectangleShape {
    int pos = 0;
    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;
    sf::Vector2f position;
    sf::Color backgroundColor;
    sf::Font font;
    std::vector<sf::Text> options;
    bool gridMode, pressed, theselect;
public:
    Menu(int xPos, int yPos, int width, int heigth, sf::Font font, sf::Color backgroundColor = sf::Color::Transparent,bool gridmode = 0);
    void addOption(std::string text, int xPos, int yPos, int textsize = 24, sf::Color textColor = sf::Color::White);
    void goDown();
    void goUp();
    void goLeft();
    void goRight();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void eventHandler(const sf::Event& event);
    void runMenu(sf::RenderWindow& window, const sf::Event& event);
};