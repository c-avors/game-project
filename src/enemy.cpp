#include "../include/enemy.h"

Enemy::Enemy(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence, std::array<MoveName, 4> baseMoveset, const std::string moveMade, const AIType &ai) : Entity(name, texture, speed, hp, attack, defence, spAttack, spDefence, baseMoveset, moveMade), ai(ai) {

}

Enemy::Enemy(const Enemy& other) : Entity(other), ai(other.ai) {}

AIType Enemy::getAI() const {
    return ai;
}