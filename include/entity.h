#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "enum.h"
#include "moves.h"
#include "moveDataBase.h"
#include <vector>

class Entity : public sf::Sprite {
protected:
    MoveDatabase moveDatabase;
    int speed;
    int hp, currentHp, attack, defence, spAttack, spDefence;
    bool playerControlled = 0, isDown = 0;
    std::string name;
    std::array<MoveInstance, 4> moveset;
    sf::RectangleShape hpBarBase;
    sf::RectangleShape hpBarReal;
public:
    Entity(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence, std::array<MoveName, 4> baseMoveset);
    void setHpBar();
    void draw(sf::RenderWindow& window);
    void takeDamage(Entity attacker, MoveInstance move);
    void setDefaultMoves();
    void setMoveInSlot(int slot, MoveName move) {
        if (slot < moveset.size()) {
            moveset[slot] = moveDatabase.createInstance(move);
        }
    }
    void attackAction(std::unique_ptr<Entity> &target, MoveInstance move);
    std::array<MoveInstance, 4> getMoveset();
    virtual ~Entity() = default;
};