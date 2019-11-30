#ifndef _LINK_H
#define _LINK_H
#include <vector>
#include "enums.h"
#include "ability.h"


class Link {
    private:
        std::vector<Ability*> Abilities;
        int strength;
        LinkType linkType;
        char name;
        bool hidden = true;
    public:
        Link(int s, LinkType l, char n);
        void changeType();
        LinkType getLinkType();
        int getStrength();
        void show();
        void addAbility(Ability *ability);
        char getName();
        bool isHidden();
}

#endif
