#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <random>
#include "../include/menu.h"
#include "../include/option.h"
#include "../include/enum.h"
#include "../include/playerCharacter.h"
#include "../include/assetsManager.h"
#include "../include/enemyFactory.h"
#include <memory>




int main() {
    srand(time(nullptr));
    //To be seperated into new Files
    GameStage currentStage = MainMenu;
    std::vector<std::unique_ptr<Entity>> entities;
    sf::Clock clock;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    AssetManager assetManager;
    bool battleTriggered = false;
    bool showBattleMenu = true;
    bool isOnMap = false;
    bool mapInitialized = false;
    bool enemiesRendered = false;
    int roundCount;
    float desktopWidth = desktop.size.x;
    float desktopHeight = desktop.size.y;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(desktopWidth, desktopHeight)), "Game", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    sf::Font mainFont("../fonts/Super Mindset.ttf");
    sf::Texture backgroundTxt("../sprites/forestBackdrop.jpg");
    sf::Sprite background(backgroundTxt);
    background.setScale({(desktopWidth)/background.getGlobalBounds().size.x, (desktopHeight)/background.getGlobalBounds().size.y});
    std::unique_ptr<sf::Sprite> map;
    std::unique_ptr<sf::Sprite> party;
    float offset = (desktopWidth-250)/2;
    

    

    std::unique_ptr<Menu> mainMenu = std::make_unique<Menu>((desktopWidth-500)/2, 100, 500, 200, mainFont, sf::Color::Red);
    mainMenu->addOption("Start", [&currentStage]() {currentStage = Map;}, 100, -10, 100, true);
    mainMenu->addOption("Exit", [&window] {window.close();}, 100, mainMenu->getLocalBounds().size.y/2-20, 100, true);

    Menu battleMenu((desktopWidth-500)/2,desktopHeight/2-250,500,250,mainFont, sf::Color::Blue, true);
    battleMenu.addOption("Billo",[&window, &entities, &showBattleMenu](){
        PlayerCharacter *billo = dynamic_cast<PlayerCharacter *>(entities[0].get());
        if(billo != nullptr) billo->setInBattle(1);
        showBattleMenu = false;

    },0,0);
    battleMenu.addOption("Fari",[](){std::cout << "2" << std::endl;},300,0);
    battleMenu.addOption("Izil",[](){std::cout << "3" << std::endl;},0,125);
    battleMenu.addOption("Liaoyuan",[](){std::cout << "4" << std::endl;},300, 125);
    battleMenu.toGrid();
    
    
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        window.clear(sf::Color::Black);
        window.draw(background);
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            if(currentStage == MainMenu) {
                mainMenu->eventHandler(*event);
            }
            else if(currentStage == Battle) {
                battleMenu.eventHandler(*event);
            }
            else {
                if(const auto* keyPressed = event->getIf<sf::Event::KeyReleased>()) {
                    offset -=750*map->getScale().x;
                }
            }
        }
        
        if(currentStage == MainMenu) {
            mainMenu->update(window);
            mainMenu->draw(window);
        }
        else if(currentStage == Map) {
            isOnMap = true;
           if (!mapInitialized) {
                assetManager.loadTexture("Map", "../sprites/Map.png");
                assetManager.loadTexture("Party", "../sprites/Party.png");
                
                map = std::make_unique<sf::Sprite>(assetManager.getTexture("Map"));
                party = std::make_unique<sf::Sprite>(assetManager.getTexture("Party"));
                
                map->setScale({0.5f, 0.5f});
                auto mapsize = map->getGlobalBounds().size;
                map->setPosition({(desktopWidth - 250) / 2, (desktopHeight - mapsize.y) / 2});
                
                party->setScale({0.1f, 0.1f});
                party->setPosition({(desktopWidth - party->getGlobalBounds().size.x) / 2, (desktopHeight - party->getGlobalBounds().size.y) / 2});
                
                mapInitialized = true;
            }
            window.draw(*map);
            window.draw(*party);
            
        }
        else if(currentStage == Battle) {
            sf::Texture testTexture("../sprites/Billo.png");
            assetManager.loadTexture("Alginnus", "../sprites/Alginnus.png");
            assetManager.loadTexture("Baheema","../sprites/Baheema.png");
            assetManager.loadTexture("Cavalier", "../sprites/Cavalier.png");
            assetManager.loadTexture("Cheerot", "../sprites/Cheerot.png");
            assetManager.loadTexture("Golorch", "../sprites/Golorch.png");
            assetManager.loadTexture("Khafiyn", "../sprites/Khafiyn.png");
            assetManager.loadTexture("LakeDowager", "../sprites/LakeDowager.png");
            assetManager.loadTexture("Luminant", "../sprites/Luminant.png");

            
            auto billo = std::make_unique<PlayerCharacter>("Billo", testTexture, 10, 100, 70 ,140, 20, 10);
            billo->setScale({0.25,0.25});
            billo->setPosition({desktopWidth/6-billo->getGlobalBounds().size.x, 7*desktopHeight/8-billo->getGlobalBounds().size.y});
            billo->setHpBar();
            entities.push_back(std::move(billo));
            EnemyFactory enemyFactory(assetManager);
            if(enemiesRendered == false) {
                enemyFactory.spawnPreset(entities,desktopWidth,desktopHeight);
                enemiesRendered = true;
            }
            sf::Text Header(mainFont);
            if(showBattleMenu){
                Header.setString("Select Fighter");
                Header.setPosition({battleMenu.getPosition().x,0});
                Header.setCharacterSize(100);
                battleMenu.update(window);
                battleMenu.draw(window);
                window.draw(Header);
            }
            for (auto &entity : entities) {
                PlayerCharacter *playable = dynamic_cast<PlayerCharacter *>(entity.get());
                if (playable != nullptr) {
                    if (playable->getInBattle()) {
                        playable->draw(window);
                    }
                }
                else {            
                    entity->draw(window);
                }
            }
            
        }
        if(isOnMap){
            if(offset<map->getPosition().x){
                map->move({-elapsed.asSeconds()*240,0});
                    
                }
                else if(offset>map->getPosition().x){
                    map->setPosition({offset,map->getPosition().y});
                    if (!battleTriggered) {
                        currentStage = Battle;
                        battleTriggered = true;
                        assetManager.clearUnusedAssets();
                    }
                }
        }
        
        
        
        window.display();
    }
    
    return 0;
}