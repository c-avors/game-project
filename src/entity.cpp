#include "../include/entity.h"

Entity::Entity(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence) : sf::Sprite(texture), name(name), speed(speed), hp(hp), attack(attack), defence(defence), spAttack(spAttack),spDefence(spDefence) {
    this->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), {texture.getSize().x, texture.getSize().y}));
    hpBarBase.setSize({100,20});
    sf::Color color(94,94,94);
    hpBarBase.setFillColor(color);
    hpBarReal.setSize({100,20});
    hpBarReal.setFillColor(sf::Color::Red);
}

void Entity::setHpBar() {
    hpBarBase.setPosition({getPosition().x+(getGlobalBounds().size.x-hpBarBase.getGlobalBounds().size.x)/2,getPosition().y+getGlobalBounds().size.y+10});
    hpBarReal.setPosition({getPosition().x+(getGlobalBounds().size.x-hpBarReal.getGlobalBounds().size.x)/2,getPosition().y+getGlobalBounds().size.y+10});
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(*this);
    window.draw(hpBarBase);
    window.draw(hpBarReal);
}