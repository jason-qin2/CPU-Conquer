#include "cell.h"
#include <vector>

using namespace std;

Cell(size_t r, size_t c) : hasServerPort{false}, row{r}, col{c}, link{nullptr} {} //constructor

bool hasLink() {
  if (link) {
    return true;
  }
  return false;
} //whether there is a link on the cell

Link *getLink() {
  return link;
} //returns link on the cell

bool hasAbilities() {
  for(auto a: abilities) {
    if (a) {
      return true;
    }
  }
  return false;
} //whether the cell has abilities

std::vector<Ability*> getAbilities() {
  return abilities;
} //gets the abilities of the cell

void setLink(Link *link) {
  this->link = link;
} //places a link on the cell

void addAbility(Ability *ability) {
  abilities.push_back(ability);
} //adds an ability to the link on the cell
