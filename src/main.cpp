#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../include/menu.h"
#include "../include/option.h"
#include "../include/enum.h"



int main() {
    //To be seperated into new Files
    GameStage currentStage = MainMenu;
    sf::Clock clock;
    int roundCount;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    float desktopWidth = desktop.size.x;
    float desktopHeight = desktop.size.y;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(desktopWidth, desktopHeight)), "Game", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    sf::Font mainFont("../fonts/Super Mindset.ttf");
    sf::Texture backgroundTxt("../sprites/forestBackdrop.jpg");
    sf::Sprite background(backgroundTxt);
    background.setScale({(desktopWidth)/background.getGlobalBounds().size.x, (desktopHeight)/background.getGlobalBounds().size.y});
    sf::Texture mapTexture("../sprites/Map.png");
    sf::Sprite map(mapTexture);
    map.setScale({0.5,0.5});
    auto mapsize = map.getGlobalBounds().size;
    map.setPosition({(desktopWidth-250)/2,(desktopHeight-mapsize.y)/2});
    // auto mapsize = map.getGlobalBounds().size;
    sf::Texture partyTexture("../sprites/Party.png");
    sf::Sprite party(partyTexture);
    party.setScale({0.1,0.1});
    party.setPosition({(desktopWidth-party.getGlobalBounds().size.x)/2,(desktopHeight-party.getGlobalBounds().size.y)/2});


    

    Menu mainMenu((desktopWidth-500)/2, 100, 500, 200, mainFont, sf::Color::Red);
    mainMenu.addOption("Start", [&currentStage]() {currentStage = Map;}, 100, -10, 100, true);
    mainMenu.addOption("Exit", [&window] {window.close();}, 100, mainMenu.getLocalBounds().size.y/2-20, 100, true);

    Menu battleMenu((desktopWidth-500)/2,desktopHeight-250,500,250,mainFont, sf::Color::Blue, true);
    battleMenu.addOption("1",[](){std::cout << "1" << std::endl;},0,0);
    battleMenu.addOption("2",[](){std::cout << "2" << std::endl;},300,0);
    battleMenu.addOption("3",[](){std::cout << "3" << std::endl;},0,125);
    battleMenu.addOption("4",[](){std::cout << "4" << std::endl;},300, 125);
    battleMenu.toGrid();
    float offset = map.getPosition().x;


    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        window.clear(sf::Color::Black);
        window.draw(background);
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if(currentStage == MainMenu) {
                mainMenu.eventHandler(*event);
            }
            else if(currentStage == Battle) {
                battleMenu.eventHandler(*event);
            }
            else {
                if(const auto* keyPressed = event->getIf<sf::Event::KeyReleased>()) {
                    offset -=750*map.getScale().x;
                }
            }
        }

        if(currentStage == MainMenu) {
            mainMenu.update(window);
            mainMenu.draw(window);
        }
        else if(currentStage == Map) {
            window.draw(map);
            window.draw(party);
        }
        else if(currentStage == Battle) {
            sf::Text Header(mainFont);
            Header.setString("Select Fighter");
            Header.setPosition({battleMenu.getPosition().x,0});
            Header.setCharacterSize(100);
            battleMenu.update(window);
            battleMenu.draw(window);
            window.draw(Header);
        }
        if(offset<map.getPosition().x){
            map.move({-elapsed.asSeconds()*240,0});
            
        }
        else if(offset>map.getPosition().x){
            map.setPosition({offset,map.getPosition().y});
            currentStage = Battle;
        }
        
        
        
        window.display();
    }

    return 0;
}