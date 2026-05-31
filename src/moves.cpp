#include "../include/moves.h"
#include "../include/entity.h"

void MoveInstance::use() {
        if (currentUses > 0) currentUses--;
}

int MoveInstance::getPower() const {
    return blueprint->power;
}
std::string MoveInstance::getName() const {
    return blueprint->name;
}