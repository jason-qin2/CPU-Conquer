#include "ability.h"

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
