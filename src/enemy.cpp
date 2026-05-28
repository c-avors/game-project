#include "../include/enemy.h"

Enemy::Enemy(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence) : Entity(name, texture, speed, hp, attack, defence, spAttack, spDefence) {

}