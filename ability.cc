#include "ability.h"

void Ability::useAbility() {
    isUsed = true; 
}

AbilityType Ability::getAbilityType() {
    return type; 
}
