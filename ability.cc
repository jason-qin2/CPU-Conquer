#include "ability.h"

Ability::Ability(AbilityType type, int playerNum) :
    type{type}, playerNum{playerNum} {}

void Ability::useAbility() {
    isUsed = true; 
}

AbilityType Ability::getAbilityType() {
    return type; 
}

bool Ability::getUsed() {
    if(isUsed == false) {
        return false; 
    } else {
        return true; 
    }
}

int Ability::getPlayerNum() {
    return playerNum;
}
