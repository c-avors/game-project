#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "enum.h"
#include <vector>

class Entity : public sf::Sprite {
protected:
    int speed;
    int hp, attack, defence, spAttack, spDefence;
    bool playerControlled = 0;
    std::string name;
    std::vector<Moves> knownMoves;
    sf::RectangleShape hpBarBase;
    sf::RectangleShape hpBarReal;
public:
    Entity(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence);
    void setHpBar();
    void draw(sf::RenderWindow& window);
    void takeDamage();
    virtual ~Entity() = default;
};