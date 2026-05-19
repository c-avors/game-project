#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../include/menu.h"
#include "../include/option.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 720)), "Game");
    sf::Font mainFont("../fonts/Super Mindset.ttf");
    sf::Texture backgroundTxt("../sprites/forestBackdrop.jpg");
    sf::Sprite background(backgroundTxt);

    Menu mainMenu(30, 30, 500, 500, mainFont);
    mainMenu.addOption("Lorem",100, 0, 100);
    mainMenu.addOption("Ipsum",100, 100, 100);


    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        window.draw(background);
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            mainMenu.runMenu(window, *event);
        }

        
        mainMenu.update(window);
        mainMenu.draw(window);
        
        window.display();
    }

    return 0;
}