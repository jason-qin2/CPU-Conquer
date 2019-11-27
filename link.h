#ifndef _LINK_H
#define _LINK_H

#include <vector>
#include "enums.h"
#include "player.h"

class Link { 
    private:
        std::vector<Ability*> Abilities;
        int strength;
        LinkType linkType;
        char name; 
        bool hidden = true;
        Player ownedBy; 
    public:
        void changeType();
        LinkType getLinkType();
        int getStrength();
        void show();
        void addAbility(Ability *ability);
}

#endif
