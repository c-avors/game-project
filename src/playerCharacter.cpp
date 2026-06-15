#include "../include/playerCharacter.h"

PlayerCharacter::PlayerCharacter(std::string name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence, std::array<MoveName, 4> baseMoveset, const std::string moveMade): Entity(name, texture, speed, hp, attack, defence, spAttack, spDefence, baseMoveset, moveMade){}
void PlayerCharacter::setInBattle(bool change){
    inBattle = change;
}
bool PlayerCharacter::getInBattle() {
    return inBattle;
}