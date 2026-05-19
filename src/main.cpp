#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../include/menu.h"
#include "../include/option.h"
#include "../include/enum.h"



int main() {

    GameStage currentStage = MainMenu;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 720)), "Game");
    sf::Font mainFont("../fonts/Super Mindset.ttf");
    sf::Texture backgroundTxt("../sprites/forestBackdrop.jpg");
    sf::Sprite background(backgroundTxt);

    Menu mainMenu(30, 30, 500, 500, mainFont);
    mainMenu.addOption("Start", [&currentStage]() {currentStage = Map;}, 100, 0, 100);
    mainMenu.addOption("Exit", [&window] {window.close();}, 100, 100, 100);


    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if(currentStage == MainMenu) {
                mainMenu.eventHandler(*event);
            }
        }

        if(currentStage == MainMenu) {
            window.draw(background);
            mainMenu.update(window);
            mainMenu.draw(window);
        }
        
        
        window.display();
    }

    return 0;
}