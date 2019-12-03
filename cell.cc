#include "cell.h"
#include <vector>

using namespace std;

Cell::Cell(size_t r, size_t c) : row{r}, col{c}, link{nullptr} {
  if ((col == 3 || col == 4) && (row == 0 || row == 7)) {
      hasServerPort = true;
  } else {
    hasServerPort = false;
  }
} //constructor

bool Cell::hasLink() {
  if (link) {
    return true;
  }
  return false;
} //whether there is a link on the cell

Link *Cell::getLink() {
  return link;
} //returns link on the cell

bool Cell::hasAbilities() {
  for(size_t i = 0; i < abilities.size(); i++) {
    if (abilities[i]) {
      return true;
    }
  }
  return false;
} //whether the cell has abilities

std::vector<Ability*> Cell::getAbilities() {
  return abilities;
} //gets the abilities of the cell

void Cell::setLink(Link *link) {
  this->link = link;
  notifyObservers();
} //places a link on the cell

void Cell::removeLink() {
  link = nullptr;
  notifyObservers();
} //removes link on the cell

void Cell::addAbility(Ability *ability) {
  abilities.push_back(ability);
  notifyObservers();
} //adds an ability to the link on the cell

bool Cell::getServerPort() {
  return hasServerPort;
} //whether the cell has a server port

int Cell::getFirewallOwner() {
  for (size_t i = 0; i < abilities.size(); i++) {
    if (abilities[i]->getAbilityType() == AbilityType::FireWall) {
      if (abilities[i]->getPlayerNum() == 1) {
        return 1;
      }
      else if (abilities[i]->getPlayerNum() == 2) {
        return 2;
      }
    }
  }
  return 0;
}

Info Cell::getInfo() {
    char linkName = ' ';
    State state;
    if (hasLink()) {
      linkName = getLink()->getName();
      state = State::Link;
    } else if (getServerPort()) {
      state = State::ServerPort;
    } else if (getFirewallOwner() == 1) {
      state = State::PlayerOneFireWall;
    } else if (getFirewallOwner() == 2) {
      state = State::PlayerTwoFireWall;
    } else {
      state = State::Empty;
    }
    return Info{row, col, linkName, state};
}
