#pragma once

#include "entity.h"

class Enemy : public Entity {
private:
    float scaleFactor;
    AIType ai;
public:
    Enemy() : Entity("", sf::Texture(), 0, 0, 0, 0, 0, 0,{Tackle,Tackle,Tackle,Tackle}) {}

    Enemy(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence, std::array<MoveName, 4> baseMoveset, const AIType &ai);
    void scaleUp();
    AIType getAI() const;
};