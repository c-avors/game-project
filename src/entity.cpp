#include "../include/entity.h"
#include "../include/playerCharacter.h"
#include <algorithm>


bool Entity::isTargetValid(std::unique_ptr<Entity> &e) {
    // If it's an enemy, it's valid.
    // If it's a PlayerCharacter, check getInBattle().
    PlayerCharacter* pc = dynamic_cast<PlayerCharacter*>(e.get());
    if (pc) return pc->getInBattle();
    return true; // Assume all enemies are valid targets
}

Entity::Entity(const std::string& name, const sf::Texture &texture, int speed, int hp, int attack, int defence, int spAttack, int spDefence, std::array<MoveName, 4> baseMoveset, const std::string& moveMade) : sf::Sprite(texture), name(name), speed(speed), hp(hp), currentHp(hp), attack(attack), defence(defence), spAttack(spAttack),spDefence(spDefence), moveMade(moveMade) {
    this->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), {texture.getSize().x, texture.getSize().y}));
    hpBarBase.setSize({100,20});
    sf::Color color(94,94,94);
    hpBarBase.setFillColor(color);
    hpBarReal.setSize({100,20});
    hpBarReal.setFillColor(sf::Color::Red);
    for(int i = 0; i < 4; ++i) {
        setMoveInSlot(i, baseMoveset[i]);
    }
}

Entity::Entity(const Entity& other) 
    : sf::Sprite(other), // Copy the sprite state
      name(other.name), 
      speed(other.speed), 
      hp(other.hp), 
      currentHp(other.currentHp), 
      attack(other.attack),
      defence(other.defence),
      spAttack(other.spAttack),
      spDefence(other.spDefence),
      moveset(other.moveset),
      moveMade(other.moveMade),
      queuedMove(other.queuedMove),
      queuedTargetIndex(other.queuedTargetIndex),
      actionQueued(other.actionQueued),
      isDown(other.isDown),
      hpBarBase(other.hpBarBase),
      hpBarReal(other.hpBarReal) {}

void Entity::setHpBar() {
    hpBarBase.setPosition({getPosition().x+(getGlobalBounds().size.x-hpBarBase.getGlobalBounds().size.x)/2,getPosition().y+getGlobalBounds().size.y+10});
    hpBarReal.setPosition({getPosition().x+(getGlobalBounds().size.x-hpBarReal.getGlobalBounds().size.x)/2,getPosition().y+getGlobalBounds().size.y+10});
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(*this);
    window.draw(hpBarBase);
    window.draw(hpBarReal);
}
void Entity::attackAction(Entity *target, MoveInstance move) {
        switch(move.blueprint->effect) {
            case Poison:
                std::cout << "poison" << std::endl;
                break;
            case AttackUp:
                std::cout << "attackUp" << std::endl;
                break;
            default:
                break;
        }
        target->takeDamage(*this, move);
        move.use();      
}

void Entity::takeDamage(Entity attacker, MoveInstance move) {
    if(move.blueprint->type == Physical) {
        float effectiveDefence = (defence <= 0.0f) ? 1.0f : defence;
        int damageTaken = (42.0f * move.blueprint->power * ((float)(attacker.attack) / effectiveDefence) / 50) + 2;
        if (damageTaken <= currentHp) {
            currentHp-=damageTaken;
        }
        else {
            currentHp = 0;
            isDown = 1;
        }
    }
    else {
        int damageTaken = (42.0f*move.blueprint->power*((float)(attacker.spAttack)/spDefence))/(float)50+2;
        if (damageTaken <= currentHp) currentHp-=damageTaken;
        else {
            currentHp = 0;
            isDown = 1;
        }
    }
    hpBarReal.setScale({(float)(currentHp)/hp, 1});
}

std::array<MoveInstance, 4> Entity::getMoveset() {
    return moveset;
}

const std::string& Entity::getName() const{
    return name;
}

int Entity::getSpeed() const {
    return speed;
}
int Entity::getTargeting() const {
    return targeting;
}

std::string Entity::getMoveMade() const {
    return moveMade;
}

void Entity::setTargeting(const int &target) {
    targeting = target;
}

void Entity::targetLeft(std::vector<std::unique_ptr<Entity>> &entities, int attackerIndex) {
    if (entities.empty()) return;

    int originalTarget = targeting;
    do {
        if(targeting == 0) targeting = entities.size() - 1;
        else targeting--;
        
        // Safety break: if we circled back to the start, stop searching
        if (targeting == originalTarget) break; 
    } while ((!this->isTargetValid(entities[targeting]) || targeting == attackerIndex));
}

void Entity::targetRight(std::vector<std::unique_ptr<Entity>> &entities, int attackerIndex) {
    if (entities.empty()) return;

    int originalTarget = targeting;
    do {
        if(targeting == entities.size() - 1) targeting = 0;
        else targeting++;
        
        // Safety break: if we circled back to the start, stop searching
        if (targeting == originalTarget) break; 
    } while ((!this->isTargetValid(entities[targeting]) || targeting == attackerIndex));
}

//Select target
void Entity::targetHandler(const sf::Event& event, std::vector<std::unique_ptr<Entity>> &entities, bool &selected, int attackIndex) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
            targetLeft(entities, attackIndex);
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
            targetRight(entities, attackIndex);
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
            selected = true;
        }
    }
}

void Entity::queueAction(MoveName move, int targetIndex) {
    this->queuedMove = move;
    this->queuedTargetIndex = targetIndex;
    this->actionQueued = true;
}

bool Entity::hasQueuedAction() const {
    return actionQueued;
}

MoveInstance Entity::getQueuedMove() const {
    return moveDatabase.createInstance(queuedMove);
}

int Entity::getTargetIndex() const {
    return queuedTargetIndex;
}

void Entity::clearQueuedAction() {
    this->actionQueued = false;
    this->queuedTargetIndex = -1;
}

bool Entity::getIsDown() const {
    return isDown;
}

void Entity::setCurrentHp(const int &hp) {
    currentHp = hp;
}

int Entity::getBaseHp() const {
    return hp;
}

void Entity::setMoveInSlot(int slot, MoveName move) {
        if (slot < moveset.size()) {
            moveset[slot] = moveDatabase.createInstance(move);
        }
}