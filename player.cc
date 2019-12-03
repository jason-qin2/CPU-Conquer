#include <iostream>
#include "player.h"
#include "grid.h"
#include "exceptions.h"
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <ctime>

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

std::vector<Ability*> Player::getAbilities() {
  return abilities;
}

void Player::steal() {
  std::cout << "OOH HE STEALING!" << std::endl;
  int oppPlayerNum;
  if (playerNumber == 1) {
    oppPlayerNum = 2;
  } else {
    oppPlayerNum = 1;
  }
  int numOppAbilities = theGrid.getPlayer(oppPlayerNum)->getAbilityCount();
  if (numOppAbilities <= 0) {
    std::cout << "Opponent has no more abilities." << std::endl;
  }
  //srand (1);
  srand(time(NULL));
    int randNum;
    randNum = (rand()%numOppAbilities)+1;
    std::cout << randNum << std::endl;
  std::vector <Ability*> oppAbilities = theGrid.getPlayer(oppPlayerNum)->getAbilities();
  Ability *newAbility = new Ability(oppAbilities[randNum]->getAbilityType(), playerNumber);
  abilities.push_back(newAbility); //rand() % (numOppAbilities - 1)]);
  oppAbilities[randNum]->useAbility();
  //OppAbilities.erase(OppAbilities.begin() + 1);//+ (rand() % numOppAbilities - 1) - 1);
}

void Player::useAbility(int abilityNum){
    if (abilityNum < 1 || abilityNum > abilities.size()) {
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
    } else if (currAbility == AbilityType::Steal) {
      this->steal();
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
