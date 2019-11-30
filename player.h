#ifndef _PLAYER_H
#define _PLAYER_H
#include <vector> 
#include "link.h"
#include "enums.h"
#include "ability.h"

class Player {
    private:
        int playerNumber;
        std::vector<Link*> ownedLinks; 
        std::vector<Link*> downloadedLinks; 
        std::vector<Ability*> abilities;
    public:
        void downloadLink(Link *link);
        void useAbility(Ability *ability);
        int getDlVirusCount();
        int getDlDataCount();
        int getAbilityCount();
};

#endif
