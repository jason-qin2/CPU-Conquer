#include "cell.h"
#include <vector>

using namespace std;

Cell::Cell(size_t r, size_t c) : row{r}, col{c}, link{nullptr} {
  if (col == 3 || col == 4) {
    if (row == 0 || row == 7) {
      hasServerPort = true;
    }
  }
  else {
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
  for(int i = 0; i < abilities.size(); i++) {
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
} //places a link on the cell

void Cell:removeLink() {
  delete link;
} //removes link on the cell

void Cell::addAbility(Ability *ability) {
  abilities.push_back(ability);
} //adds an ability to the link on the cell
