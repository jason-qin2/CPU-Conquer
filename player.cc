#include <iostream>
#include "player.h"
#include "grid.h"
#include "exceptions.h"

Player::Player(int playerNumber, std::vector<Ability*> abilities,
std::vector<Link*> links, Grid &theGrid) :
    playerNumber{playerNumber}, ownedLinks{links},
    abilities{abilities}, theGrid{theGrid} {}

void Player::downloadLink(Link *link) {
    downloadedLinks.push_back(link);
}

void Player::linkBoost(Ability *ability) {
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

void Player::fireWall(Ability *ability) {
    Cell *targetCell;
    int colNum;
    int rowNum;
    std::cin >> colNum >> rowNum;
    try {
        targetCell = theGrid.getCell(colNum - 1, rowNum - 1);
    } catch (std::out_of_range) {
        throw AbilityError();
    }
    if(targetCell->getServerPort()) {
        throw AbilityError();
    } else {
        targetCell->addAbility(ability);
        theGrid.notifyObservers();
        return;
    }
}

void Player::download(int opponentNumber, std::vector<Link *> opponentLinks, Player *curPlayer) {
    char linkID;
    std::cin >> linkID;
    for (int i = 0; i < opponentLinks.size(); i++) {
        if (opponentLinks[i]->getName() == linkID) {
            curPlayer->downloadLink(opponentLinks[i]);
            theGrid.notifyObservers();
            return;
        }
    }
    throw AbilityError();
}

void Player::polarize(int opponentNumber, std::vector<Link *> opponentLinks) {
    char linkID;
    std::cin >> linkID;
    for (int i = 0; i < ownedLinks.size(); i++) {
        if (ownedLinks[i]->getName() == linkID) {
            ownedLinks[i]->changeType();
            theGrid.notifyObservers();
            return;
        }
    }
    for (int i = 0; i < opponentLinks.size(); i++) {
        if (opponentLinks[i]->getName() == linkID) {
            opponentLinks[i]->changeType();
            theGrid.notifyObservers();
            return;
        }
    }
    throw AbilityError();
}

void Player::scan(std::vector <Link *> opponentLinks) {
    char linkID;
    std::cin >> linkID;
    for(int i = 0; i < ownedLinks.size(); i++) {
        if(ownedLinks[i]->getName() == linkID) {
            ownedLinks[i]->show();
            theGrid.notifyObservers();
            return; 
        }
    }
    for(int i = 0; i < opponentLinks.size(); i++) {
        if(opponentLinks[i]->getName() == linkID) {
            opponentLinks[i]->show(); 
            theGrid.notifyObservers();
            return; 
        }
    }
    throw AbilityError();
}

void Player::useAbility(int abilityNum){
    if (abilityNum < 1) {
        throw AbilityError();
    }
    Ability *ability = abilities[abilityNum - 1];
    int opponentNumber = (playerNumber == 1) ? 2 : 1;
    std::vector<Link *> opponentLinks = theGrid.getPlayer(opponentNumber)->getOwnedLinks();
    AbilityType currAbility = ability->getAbilityType();

    if(ability->getUsed()) {
        throw AbilityError();
    }
    if(currAbility == AbilityType::LinkBoost) {
        linkBoost(ability);
    } else if(currAbility == AbilityType::FireWall) {
        fireWall(ability);
    } else if(currAbility == AbilityType::Download) {
        download(opponentNumber, opponentLinks, this);
    } else if(currAbility == AbilityType::Polarize) {
        polarize(opponentNumber, opponentLinks);
    } else if(currAbility == AbilityType::Scan) {
        scan(opponentLinks);
    }
    ability->useAbility();
    theGrid.notifyObservers();
    return;
}

int Player::getDlVirusCount() {
    int virusCount = 0;
    for (int i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == LinkType::Virus) {
            virusCount++;
        }
    }
    return virusCount;
}

int Player::getDlDataCount() {
    int dataCount = 0;
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
        if(!abilities[i]->getUsed()) {
            abilityCount++; 
        }
    }
    return abilityCount;
}

int Player::getPlayerNumber() {
    return playerNumber;
}

std::vector<Link *> &Player::getOwnedLinks() {
    return ownedLinks;
}

void Player::printAbilities(std::ostream &out) {
    for (int i = 0; i < abilities.size(); i++) {
        out << "Ability #" << i + 1; ": ";
        out << abilities[i]->getTypeAsStr() << " ";
        out << "Used: ";
        if (abilities[i]->getUsed() == true) {
            out << "Yes";
        } else {
            out << "No";
        }
        out << std::endl;
    }
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
