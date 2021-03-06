#ifndef _LINK_H
#define _LINK_H
#include <vector>
#include "enums.h"
#include "ability.h"


class Link {
    private:
        std::vector<Ability*> abilities;
        int strength;
        LinkType linkType;
        char name;
        bool hidden = true;
        int playerNum;
        bool downloaded = false;
    public:
        Link(int strength, LinkType type, char name, int playerNum);
        void changeType();
        LinkType getLinkType();
        int getStrength();
        void show();
        void addAbility(Ability *ability);
        char getName();
        bool isHidden();
        int getPlayerNum();
        std::vector<Ability*> getAbilities();
        bool isDownloaded();
        void download();
        void changeStrength(int newStrength);
};

#endif
