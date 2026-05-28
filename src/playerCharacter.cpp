#include "../include/playerCharacter.h"

PlayerCharacter::PlayerCharacter(std::string name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence): Entity(name, texture, speed, hp, attack, defence, spAttack, spDefence){}
void PlayerCharacter::setInBattle(bool change){
    inBattle = change;
}
bool PlayerCharacter::getInBattle() {
    return inBattle;
}