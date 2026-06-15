#include "entity.h"
#pragma once

class PlayerCharacter : public Entity {
private:
    bool inBattle = 0;
    bool inFocus = 0;
public:
    PlayerCharacter(std::string name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence, std::array<MoveName, 4> baseMoveset, const std::string moveMade);
    void setInBattle(bool change);
    bool getInBattle();
};