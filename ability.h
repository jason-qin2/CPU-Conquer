#ifndef _ABILITY_H
#define _ABILITY_H

#include "enums.h"

class Ability {
    private:
        bool isUsed = false;
        AbilityType type; 
        int playerNum;
    public:
        Ability(AbilityType type, int playerNum);
        void useAbility(); 
        AbilityType getAbilityType();
        bool getUsed();
        int getPlayerNum();
};

#endif
