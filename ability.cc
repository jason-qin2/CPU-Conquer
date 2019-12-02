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

std::string Ability::getTypeAsStr() {
    if (type == AbilityType::LinkBoost) {
        return "Link boost";
    } else if (type == AbilityType::FireWall) {
        return "Firewall";
    } else if (type == AbilityType::Download) {
        return "Download";
    } else if (type == AbilityType::Polarize) {
        return "Polarize";
    } else if (type == AbilityType::Scan) {
        return "Scan";
    }
}
