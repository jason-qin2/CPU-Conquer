#include <iostream>
#include "player.h"

Player::Player(int playerNumber, std::vector<Ability*> abilities, std::vector<Link*> links) {
    std::vector<Link *> downloadedLinks; 
    playerNumber = playerNumber;
    abilities = abilities; 
    ownedLinks = links;
    downloadedLinks = downloadedLinks;
}

void Player::downloadLink(Link *link) {
    downloadedLinks.push_back(link);
}

void linkBoost(Ability *ability, std::vector<Link *> ownedLinks) {
    char target; 
    std::cin >> target; 
    for(int i = 0; i < ownedLinks.size(); i++) {
        if(ownedLinks[i]->getName() = target) {
            ownedLinks[i]->addAbility(ability);
            return; 
            }
        }
    // Display Error Msg if Link DNE
}

void fireWall(int colNum, int rowNum, Grid *theGrid, Ability *ability) {
    Cell targetCell;
    std::cin >> colNum >> rowNum;
    targetCell = theGrid->getCell(colNum, rowNum);
    targetCell.addAbility(ability);
    return;
}

void download(int opponentNumber, std::vector<Link *> *opponentLinks) {
    char linkID;
    std::cin >> linkID;
    for (int i = 0; i < opponentLinks->size(); i++) {
        if ((*opponentLinks)[i]->getName() == linkID) {
            downloadLink(opponentLinks[i]);
            return;
        }
    }
    // Display Error msg if Link DNE
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

    //Display Error msg if Link DNE
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
    // Display Error msg if linkID DNE
}



void Player::useAbility(Ability *ability, Grid *theGrid){
    int abilityNum;
    int target; 
    int opponentNumber = (playerNumber == 1) ? 2 : 1;
    std::vector<Link *> *opponentLinks; 
    opponentLinks = theGrid->getPlayer(opponentNumber).getOwnedLinks();
    AbilityType currAbility = ability->getAbilityType();
    std::cin >> abilityNum; 

    if(ability->isUsed()) {
        // Display Error Msg
        return; 
    }

    if(currAbility == AbilityType::LinkBoost) {

        linkBoost(ability, ownedLinks);

    } else if(currAbility == AbilityType::FireWall) {
        int colNum;
        int rowNum;
        std::cin >> colNum >> rowNum; 
        fireWall(colNum, rowNum, theGrid, ability);
        
    } else if(currAbility == AbilityType::Download) {

        download(opponentNumber, opponentLinks);

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

std::vector<Link *> &Player::getOwnedLinks() {
    return &ownedLinks; 
}

Player::~Player() {
    delete ownedLinks;
    delete abilities; 
}
