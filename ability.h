#ifndef _ABILITY_H
#define _ABILITY_H

#include "enums.h"

class Ability {
    private:
        bool isUsed = false;
        AbilityType type; 
    public:
        void useAbility(); 
};

#endif
