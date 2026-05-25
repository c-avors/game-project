#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "enum.h"
#include <vector>

class Entity : public sf::Sprite {
protected:
    int speed;
    int hp, attack, defence, spAtack, spDefence;
    bool playerControlled;
    std::string name;
    std::vector<Moves> knownMoves;
};