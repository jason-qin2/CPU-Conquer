#include <iostream>
#include "player.h"
#include "grid.h"
#include "exceptions.h"

Player::Player(int playerNumber, std::vector<Ability*> abilities,
std::vector<Link*> links, Grid &theGrid) :
    playerNumber{playerNumber}, ownedLinks{links},
    abilities{abilities}, theGrid{theGrid} {}

void Player::downloadLink(Link *link) {
  char name = link->getName();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if(theGrid.getCell(i,j)->hasLink()) {
        if (theGrid.getCell(i,j)->getLink()->getName() == name) {
          theGrid.getCell(i,j)->removeLink();
        }
      }
    }
  }
  link->show();
    downloadedLinks.push_back(link);
    link->download();
}

void Player::linkBoost(Ability *ability) {
    char target;
    std::cin >> target;
    for(size_t i = 0; i < ownedLinks.size(); i++) {
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
        return;
    }
}

void Player::download(int opponentNumber, std::vector<Link *> opponentLinks, Player *curPlayer) {
    char linkID;
    std::cin >> linkID;
    for (size_t i = 0; i < opponentLinks.size(); i++) {
        if (opponentLinks[i]->getName() == linkID) {
            curPlayer->downloadLink(opponentLinks[i]);
            return;
        }
    }
    throw AbilityError();
}

void Player::polarize(int opponentNumber, std::vector<Link *> opponentLinks) {
    char linkID;
    std::cin >> linkID;
    for (size_t i = 0; i < ownedLinks.size(); i++) {
        if (ownedLinks[i]->getName() == linkID) {
            ownedLinks[i]->changeType();
            return;
        }
    }
    for (size_t i = 0; i < opponentLinks.size(); i++) {
        if (opponentLinks[i]->getName() == linkID) {
            opponentLinks[i]->changeType();
            return;
        }
    }
    throw AbilityError();
}

void Player::scan(std::vector <Link *> opponentLinks) {
    char linkID;
    std::cin >> linkID;
    for(size_t i = 0; i < ownedLinks.size(); i++) {
        if(ownedLinks[i]->getName() == linkID) {
            ownedLinks[i]->show();
            return;
        }
    }
    for(size_t i = 0; i < opponentLinks.size(); i++) {
        if(opponentLinks[i]->getName() == linkID) {
            opponentLinks[i]->show();
            return;
        }
    }
    throw AbilityError();
}

void Player::useAbility(int abilityNum){
    if (abilityNum < 1 || abilityNum > 5) {
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
    return;
}

int Player::getDlVirusCount() {
    int virusCount = 0;
    for (size_t i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == LinkType::Virus) {
            virusCount++;
        }
    }
    return virusCount;
}

int Player::getDlDataCount() {
    int dataCount = 0;
    for (size_t i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == LinkType::Data) {
            dataCount++;
        }
    }
    return dataCount;
}

int Player::getAbilityCount() {
    int abilityCount = 0;
    for (size_t i = 0; i < abilities.size(); i++) {
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
    for (size_t i = 0; i < abilities.size(); i++) {
        out << "Ability #" << i + 1 << ": ";
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

std::vector<Link*> &Player::getDownloadedLinks() {
  return downloadedLinks;
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
