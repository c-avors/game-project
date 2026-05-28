#pragma once

#include "entity.h"

class Enemy : public Entity {
private:
    float scaleFactor;
public:
    Enemy() : Entity("", sf::Texture(), 0, 0, 0, 0, 0, 0) {}

    Enemy(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence);
    void scaleUp();
};