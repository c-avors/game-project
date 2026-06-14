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

bool speedCompare(const std::unique_ptr<Entity> &e1, const std::unique_ptr<Entity> &e2) {
    return (e1->getSpeed() > e2->getSpeed());
}

int main() {
    srand(time(nullptr));
    //To be seperated into new Files
    GameStage currentStage = MainMenu;
    std::vector<std::unique_ptr<Entity>> entities;
    sf::Clock clock;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    AssetManager assetManager;
    bool battleTriggered = false;
    bool showSelectMenu = true;
    bool isOnMap = false;
    bool mapInitialized = false;
    bool battleTexturesLoaded = false;
    bool enemiesRendered = false;
    int roundCount = 1;
    float desktopWidth = desktop.size.x;
    float desktopHeight = desktop.size.y;
    bool showMoveMenu = false;
    bool moveMenuBuilt = false;
    bool activeFound = false;
    bool playersExistnt = true;

    BattleState battleState = PlayerSelectMove; 
    int currentCharacter = 0;
    int chosenMoveSlot = -1; 
    bool selectedTarget = false;
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

    Menu selectMenu((desktopWidth-500)/2,desktopHeight/2-250,500,250,mainFont, sf::Color::Blue, true);
    selectMenu.addOption("Billo", [&entities, &showSelectMenu, &battleState]() {
    for (const auto& entity : entities) {
        PlayerCharacter* character = dynamic_cast<PlayerCharacter*>(entity.get());
        if (character != nullptr && character->getName() == "Billo") {
            character->setInBattle(true);
            showSelectMenu = false;
            battleState = PlayerSelectMove;
            break; 
        }
    }
    }, 0, 0);

    selectMenu.addOption("Fari", [&entities, &showSelectMenu, &battleState]() {
    for (const auto& entity : entities) {
        PlayerCharacter* character = dynamic_cast<PlayerCharacter*>(entity.get());
        if (character != nullptr && character->getName() == "Fari") {
            character->setInBattle(true);
            showSelectMenu = false;
            battleState = PlayerSelectMove;
            break;
        }
    }
    }, 300, 0);

    selectMenu.addOption("Izil", [&entities, &showSelectMenu, &battleState]() {
    for (const auto& entity : entities) {
        PlayerCharacter* character = dynamic_cast<PlayerCharacter*>(entity.get());
        if (character != nullptr && character->getName() == "Izil") {
            character->setInBattle(true);
            showSelectMenu = false;
            battleState = PlayerSelectMove;
            break;
        }
    }
    }, 0, 125);

    selectMenu.addOption("Liaoyuan", [&entities, &showSelectMenu, &battleState]() {
    for (const auto& entity : entities) {
        PlayerCharacter* character = dynamic_cast<PlayerCharacter*>(entity.get());
        if (character != nullptr && character->getName() == "Liaoyuan") {
            character->setInBattle(true);
            showSelectMenu = false;
            battleState = PlayerSelectMove;
            break;
        }
    }
    }, 300, 125);
    selectMenu.toGrid();
    Menu moveMenu((desktopWidth-500)/2, 250, 500, 250, mainFont, sf::Color::Blue, true);

    


    
    
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
                if(showSelectMenu) {
                    selectMenu.eventHandler(*event);
                }
                if(showMoveMenu) {
                    moveMenu.eventHandler(*event);
                }
                if (selectedTarget == false && currentCharacter < entities.size()) {
                    entities[currentCharacter]->targetHandler(*event, entities, selectedTarget, currentCharacter);
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
                map->setPosition({(desktopWidth - 250 ) / 2 - 750*(roundCount-1)*(map->getScale().x), (desktopHeight - mapsize.y) / 2});
                offset=(desktopWidth - 250 ) / 2 - 750*roundCount*(map->getScale().x);
                
                party->setScale({0.1f, 0.1f});
                party->setPosition({(desktopWidth - party->getGlobalBounds().size.x) / 2, (desktopHeight - party->getGlobalBounds().size.y) / 2});
                
                mapInitialized = true;
            }
            window.draw(*map);
            window.draw(*party);
            
        }
        else if(currentStage == Battle) {
            if (!battleTexturesLoaded) {
                assetManager.loadTexture("Billo", "../sprites/Billo.png");
                assetManager.loadTexture("Fari", "../sprites/Fari.png");
                assetManager.loadTexture("Izil", "../sprites/Izil.png");
                assetManager.loadTexture("Liaoyuan", "../sprites/Liaoyuan.png");
                assetManager.loadTexture("Alginnus", "../sprites/Alginnus.png");
                assetManager.loadTexture("Baheema","../sprites/Baheema.png");
                assetManager.loadTexture("Cavalier", "../sprites/Cavalier.png");
                assetManager.loadTexture("Cheerot", "../sprites/Cheerot.png");
                assetManager.loadTexture("Golorch", "../sprites/Golorch.png");
                assetManager.loadTexture("Khafiyn", "../sprites/Khafiyn.png");
                assetManager.loadTexture("LakeDowager", "../sprites/LakeDowager.png");
                assetManager.loadTexture("Luminant", "../sprites/Luminant.png");
                if(playersExistnt) {
                    auto billo = std::make_unique<PlayerCharacter>("Billo", assetManager.getTexture("Billo"), 106, 404, 236 ,297, 113, 306, std::array<MoveName, 4>{Tackle, Tackle, Tackle, Tackle});
                    auto fari = std::make_unique<PlayerCharacter>("Fari", assetManager.getTexture("Fari"), 106, 404, 236 ,297, 113, 306, std::array<MoveName, 4>{Tackle, Tackle, Tackle, Tackle});
                    auto izil = std::make_unique<PlayerCharacter>("Izil", assetManager.getTexture("Izil"), 106, 404, 236 ,297, 113, 306, std::array<MoveName, 4>{Tackle, Tackle, Tackle, Tackle});
                    auto liao = std::make_unique<PlayerCharacter>("Liaoyuan", assetManager.getTexture("Liaoyuan"), 106, 404, 236 ,297, 113, 306, std::array<MoveName, 4>{Tackle, Tackle, Tackle, Tackle});
                    billo->setScale({0.25,0.25});
                    billo->setPosition({desktopWidth/6-billo->getGlobalBounds().size.x, 7*desktopHeight/8-billo->getGlobalBounds().size.y});
                    billo->setHpBar();
                    entities.push_back(std::move(billo));

                    fari->setScale({0.25,0.25});
                    fari->setPosition({desktopWidth/6-fari->getGlobalBounds().size.x, 7*desktopHeight/8-fari->getGlobalBounds().size.y});
                    fari->setHpBar();
                    entities.push_back(std::move(fari));

                    izil->setScale({0.25,0.25});
                    izil->setPosition({desktopWidth/6-izil->getGlobalBounds().size.x, 7*desktopHeight/8-izil->getGlobalBounds().size.y});
                    izil->setHpBar();
                    entities.push_back(std::move(izil));

                    liao->setScale({0.25,0.25});
                    liao->setPosition({desktopWidth/6-liao->getGlobalBounds().size.x, 7*desktopHeight/8-liao->getGlobalBounds().size.y});
                    liao->setHpBar();
                    entities.push_back(std::move(liao));
                    playersExistnt = false;
                }
                

                battleTexturesLoaded = 1;
            }
            
            
            
            static EnemyFactory enemyFactory(assetManager);
            if(enemiesRendered == false) {
                enemyFactory.spawnPreset(entities,desktopWidth,desktopHeight);
                enemiesRendered = true;
            }
            if (battleState == PlayerSelectMove) {
                if (currentCharacter < entities.size()) {
                    PlayerCharacter *playable = dynamic_cast<PlayerCharacter *>(entities[currentCharacter].get());
                    if (playable != nullptr && playable->getInBattle()) {
                        showMoveMenu = true;
                        
                        if (!moveMenuBuilt) {
                            moveMenu.clearOptions();
                            moveMenu.addOption(playable->getMoveset()[0].getName(), [&chosenMoveSlot]() {
                                chosenMoveSlot = 0;
                            }, 50, 50); 

                            moveMenu.addOption(playable->getMoveset()[1].getName(), [&chosenMoveSlot]() {
                                chosenMoveSlot = 1;
                            }, 300, 50);
                            
                            moveMenu.addOption(playable->getMoveset()[2].getName(), [&chosenMoveSlot]() {
                                chosenMoveSlot = 2;
                            }, 50, 150);
                            
                            moveMenu.addOption(playable->getMoveset()[3].getName(), [&chosenMoveSlot]() {
                                chosenMoveSlot = 3;
                            }, 300, 150);
                            
                            moveMenu.toGrid();
                            moveMenuBuilt = true; 
                        }

                        moveMenu.update(window);

                        if (chosenMoveSlot != -1) {
                            showMoveMenu = false;
                            moveMenuBuilt = false; 
                            selectedTarget = false; 
                            battleState = Targeting;
                        }   
                    }
                    else if(!showSelectMenu){
                        showMoveMenu = false;
                        moveMenuBuilt = false;
                        currentCharacter++;
                    }
                }
                else {
                    showMoveMenu = false;
                    moveMenuBuilt = false;
                    battleState = EnemySelectMove;
                    currentCharacter = 0;
                }
            }

            if(battleState == Targeting) {
                //Setting first valid target
                Entity* attacker = entities[currentCharacter].get();
                auto targetIndex = attacker->getTargeting();
                if (!attacker->isTargetValid(entities[targetIndex]) || targetIndex == currentCharacter) {
                    attacker->targetRight(entities, currentCharacter);
                }

                // Reset all entities to white first
                for (auto& e : entities) {
                    e->setColor(sf::Color::White);
                }

                // Apply red only to the current target
                if (targetIndex >= 0 && targetIndex < entities.size()) {
                    entities[targetIndex]->setColor(sf::Color(255, 120, 120));
                }

                // Queuing attack
                if (selectedTarget) {
                    MoveInstance confirmedMove = attacker->getMoveset()[chosenMoveSlot];
                    attacker->queueAction(confirmedMove.blueprint->id, attacker->getTargeting());
                    chosenMoveSlot = -1;
                    selectedTarget = false;
                    currentCharacter++;
                    moveMenuBuilt = false; 
                    battleState = PlayerSelectMove;
                }
            }

            if(battleState == EnemySelectMove) {
                //Select Random Playable Character to target
                static std::vector<int> activePlayerIndices;
                activePlayerIndices.clear();
                activeFound = false;
                if(!activeFound) {
                    for (int i = 0; i < entities.size(); ++i) {
                        PlayerCharacter *pc = dynamic_cast<PlayerCharacter *>(entities[i].get());
                        if (pc && pc->getInBattle()) {
                            activePlayerIndices.push_back(i);
                        }
                    }
                    activeFound = true;
                }
                
                if (currentCharacter < entities.size()) {
                    Enemy *enemy = dynamic_cast<Enemy *>(entities[currentCharacter].get());
                    //Checks if entity is enemy and can attack
                    if(enemy != nullptr && !enemy->getIsDown()) {
                        //Basic AI attacks at random
                        if(enemy->getAI() == Basic) {
                            for (int i = 0 ; i < 4; i++) {
                                // std::cout << enemy->getMoveset()[i].getName();
                            }
                            auto randMove = rand()%4;
                            MoveInstance confirmedMove = enemy->getMoveset()[randMove];
                            enemy->queueAction(confirmedMove.blueprint->id, activePlayerIndices[rand()%activePlayerIndices.size()]);
                            std::cout << "::: " << confirmedMove.getName() <<std::endl;
                        }
                        currentCharacter++;

                    }
                    else {
                        currentCharacter++;
                    }
                }
                //Next battle phase
                else {
                    battleState = PlayingActions;
                    currentCharacter = 0; 
                }
            }

            //Playing actions
            if(battleState == PlayingActions) {
                std::sort(entities.begin(), entities.end(), speedCompare);
                for(auto &entity : entities) {
                    if(entity->hasQueuedAction()) {
                        entity->attackAction(entities[entity->getTargetIndex()].get(),entity->getQueuedMove());
                        std::cout << entity->getName() << " used " << entity->getQueuedMove().getName() << std::endl;
                        entity->clearQueuedAction();
                    }

                }
                battleState = PlayerSelectMove;
                currentCharacter = 0;
                //removing fainted entities
                entities.erase(
                    std::remove_if(entities.begin(), entities.end(), [](const std::unique_ptr<Entity>& entity) {
                        return entity->getIsDown(); 
                    }), 
                    entities.end()
                );
                bool enemiesLeft = false;
                bool activePlayerLeft = false;
                for (const auto& entity : entities) {
                    if (dynamic_cast<Enemy*>(entity.get()) != nullptr) {
                        enemiesLeft = true;
                        break;
                    } else if (auto* pc = dynamic_cast<PlayerCharacter*>(entity.get())) {
                        // Check if player is in battle AND still standing
                        if (pc->getInBattle() && !pc->getIsDown()) {
                            activePlayerLeft = true;
                        }
                    }
                }

                //Battle Won
                if (!enemiesLeft) {
                    //Reseting Flags
                    battleState = PlayerSelectMove;
                    enemiesRendered = false;
                    currentStage = Map; 
                    isOnMap = true;
                    mapInitialized = false;
                    showSelectMenu = false;
                    showMoveMenu = false;
                    moveMenuBuilt = false;
                    battleTriggered = false;
                    roundCount++;
                    currentCharacter = 0;
                    for(auto &entity : entities) {
                        PlayerCharacter *playable = dynamic_cast<PlayerCharacter *>(entity.get());
                        if(playable != nullptr && playable->getInBattle()) {
                            playable->setInBattle(false);
                        }
                        //Heal On Round 5
                        if(playable != nullptr && roundCount == 5) {
                            playable->setCurrentHp(playable->getBaseHp());
                        }
                    }
                }

                //Game Over
                if (!activePlayerLeft) {
                    //Reseting Flags
                    currentStage = MainMenu;
                    entities.clear();
                    battleTriggered = false;
                    showSelectMenu = true;
                    isOnMap = false;
                    mapInitialized = false;
                    battleTexturesLoaded = false;
                    enemiesRendered = false;
                    showMoveMenu = false;
                    moveMenuBuilt = false;
                    activeFound = false;
                    playersExistnt = true;
                    currentCharacter = 0;
                    chosenMoveSlot = -1; 
                    roundCount = 1;
                    selectedTarget = false;
                }
            }

            sf::Text Header(mainFont);
            if(showSelectMenu){
                Header.setString("Select Fighter");
                Header.setPosition({selectMenu.getPosition().x, 0});
                Header.setCharacterSize(100);
                selectMenu.update(window);
                selectMenu.draw(window);
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

            if (showMoveMenu && !showSelectMenu) {
                moveMenu.update(window);
                moveMenu.draw(window);
            }
        }

        //Party Movement
        if(isOnMap){
            if(offset < map->getPosition().x){
                map->move({-elapsed.asSeconds()*240, 0});
            }
            else if(offset > map->getPosition().x){
                map->setPosition({offset, map->getPosition().y});
                    if (!battleTriggered) {
                    currentStage = Battle;
                    battleState = PlayerSelectMove;
                    showSelectMenu = true;
                    currentCharacter = 0;
                    battleTriggered = true;
                    // assetManager.clearUnusedAssets();
                }
            }
        }
        
        window.display();
    }

    map.reset();
    party.reset();
    entities.clear();
    assetManager.clearUnusedAssets();
    return 0;
}