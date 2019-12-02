#ifndef _PLAYER_H
#define _PLAYER_H
#include <vector> 
#include "link.h"
#include "enums.h"
#include "cell.h"
#include "ability.h"

class Grid;

class Player {
    private:
        int playerNumber;
        std::vector<Link*> ownedLinks; 
        std::vector<Link*> downloadedLinks; 
        std::vector<Ability*> abilities;
        Grid &theGrid;
    public:
        Player(int playerNumber, std::vector<Ability*> abilities, 
            std::vector<Link*> links, Grid &theGrid);
        void downloadLink(Link *link);
        void useAbility(int abilityNum);
        int getDlVirusCount();
        int getDlDataCount();
        int getAbilityCount();
        int getPlayerNumber();
        std::vector<Link*> &getOwnedLinks();
        void printAbilities(std::ostream &out);
        ~Player();
};

#endif
