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
    int targeting;
    bool playerControlled = 0, isDown = 0;
    bool actionQueued = false;
    MoveName queuedMove;
    int queuedTargetIndex = -1;
    std::string name;
    std::string moveMade;
    std::array<MoveInstance, 4> moveset;
    sf::RectangleShape hpBarBase;
    sf::RectangleShape hpBarReal;
public:
    Entity(const Entity& other);
    Entity(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence, std::array<MoveName, 4> baseMoveset, const std::string& moveMade);
    void setHpBar();
    void draw(sf::RenderWindow& window);
    void takeDamage(Entity attacker, MoveInstance move);
    void setTargeting(const int &target);
    void setDefaultMoves();
    void setMoveInSlot(int slot, MoveName move);
    void setCurrentHp(const int &hp);

    void attackAction(Entity *target, MoveInstance move);
    const std::string& getName() const;
    std::array<MoveInstance, 4> getMoveset();
    void targetLeft(std::vector<std::unique_ptr<Entity>> &entities, int attackerIndex);
    void targetRight(std::vector<std::unique_ptr<Entity>> &entities, int attackerIndex);
    void targetHandler(const sf::Event& event, std::vector<std::unique_ptr<Entity>> &entities, bool &selected, int attackIndex);

    int getSpeed() const;
    int getTargeting() const;
    bool getIsDown() const;
    int getBaseHp() const;
    std::string getMoveMade() const;

    void queueAction(MoveName move, int targetIndex);
    bool hasQueuedAction() const;
    MoveInstance getQueuedMove() const;
    int getTargetIndex() const;
    void clearQueuedAction();
    bool isTargetValid(std::unique_ptr<Entity> &e);

    virtual ~Entity() = default;
};