#include <iostream>
#include "player.h"
#include "exceptions.h"

Player::Player(int playerNumber, std::vector<Ability*> abilities, std::vector<Link*> links) :
    playerNumber{playerNumber}, abilities{abilities}, ownedLinks{links} {}

void Player::downloadLink(Link *link) {
    downloadedLinks.push_back(link);
}

void linkBoost(Ability *ability, std::vector<Link *> ownedLinks) {
    char target; 
    std::cin >> target; 
    for(int i = 0; i < ownedLinks.size(); i++) {
        if(ownedLinks[i]->getName() == target) {
            ownedLinks[i]->addAbility(ability);
            return; 
            }
        }
    throw AbilityError();
}

void fireWall(Grid *theGrid, Ability *ability) {
    Cell *targetCell;
    int colNum;
    int rowNum; 
    std::cin >> colNum >> rowNum;
    try {
        targetCell = theGrid->getCell(colNum, rowNum);
    } catch (std::out_of_range) {
        throw AbilityError();
    }
    targetCell->addAbility(ability);
    theGrid->notifyObservers();
    return;
}

void download(int opponentNumber, std::vector<Link *> *opponentLinks, Player *curPlayer) {
    char linkID;
    std::cin >> linkID;
    for (int i = 0; i < opponentLinks->size(); i++) {
        if ((*opponentLinks)[i]->getName() == linkID) {
            curPlayer->downloadLink((*opponentLinks)[i]);
            return;
        }
    }
    throw AbilityError();
}

void polarize(int opponentNumber, std::vector<Link *> *opponentLinks, std::vector<Link *> ownedLinks) {
    char linkID;
    std::cin >> linkID;
    for (int i = 0; i < ownedLinks.size(); i++) {
        if (ownedLinks[i]->getName() == linkID) {
            ownedLinks[i]->changeType();
            return;
        }
    }
    for (int i = 0; i < opponentLinks->size(); i++) {
        if ((*opponentLinks)[i]->getName() == linkID) {
            (*opponentLinks)[i]->changeType();
            return;
        }
    }

    throw AbilityError();
}

void scan(std::vector <Link *> *opponentLinks, std::vector<Link *> ownedLinks ) {
    char linkID;
    std::cin >> linkID;
    for(int i = 0; i < ownedLinks.size(); i++) {
        if(ownedLinks[i]->getName() == linkID) {
            ownedLinks[i]->show();
            return; 
        }
    }

    for(int i = 0; i < opponentLinks->size(); i++) {
        if((*opponentLinks)[i]->getName() == linkID) {
            (*opponentLinks)[i]->show(); 
            return; 
        }
    }
    throw AbilityError();
}



void Player::useAbility(Ability *ability, Grid *theGrid){
    int abilityNum;
    int target; 
    int opponentNumber = (playerNumber == 1) ? 2 : 1;
    std::vector<Link *> *opponentLinks = theGrid->getPlayer(opponentNumber)->getOwnedLinks(); 
    AbilityType currAbility = ability->getAbilityType();
    std::cin >> abilityNum; 

    if(ability->getUsed()) {
        throw AbilityError();
    }
    if(currAbility == AbilityType::LinkBoost) {
        linkBoost(ability, ownedLinks);
    } else if(currAbility == AbilityType::FireWall) {
        fireWall(theGrid, ability);
    } else if(currAbility == AbilityType::Download) {
        download(opponentNumber, opponentLinks, *this);
    } else if(currAbility == AbilityType::Polarize) {
        polarize(opponentNumber, opponentLinks, ownedLinks);
    } else if(currAbility == AbilityType::Scan) { 
        scan(opponentLinks, ownedLinks);
    }
    ability->useAbility();
    return; 
}

int Player::getDlVirusCount() {
    int virusCount;
    for (int i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == LinkType::Virus) {
            virusCount++; 
        }
    }
    return virusCount; 
}

int Player::getDlDataCount() {
    int dataCount; 
    for (int i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == LinkType::Data) {
            dataCount++; 
        }
    }
    return dataCount; 
}

int Player::getAbilityCount() {
    int abilityCount = 0;
    for (int i = 0; i < abilities.size(); i++) {
        abilityCount++;
    }
    return abilityCount;
}

int Player::getPlayerNumber() {
    return playerNumber; 
}

std::vector<Link *> &Player::getOwnedLinks() {
    return &ownedLinks; 
}

Player::~Player() {
    for(auto links : ownedLinks) {
        delete links; 
    }
    for(auto ability : abilities) {
        delete ability; 
    }
    ownedLinks.clear();
    abilities.clear();
}
