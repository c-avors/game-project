#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "enum.h"

struct Move {
    std::string name;
    MoveName id;
    int power;
    int priority;
    int uses;
    MoveType type;
    Effect effect;
};

struct MoveInstance {
    const Move* blueprint; 
    int currentUses; 
    
    std::string getName() const;
    int getPower() const;
    void use();
};