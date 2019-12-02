#include <vector>
#include <iostream>
#include "textDisplay.h"
#include "cell.h"
#include "ability.h"
#include "link.h"
#include "enums.h"
#include "subject.h"
#include "observer.h"

using namespace std;

TextDisplay::TextDisplay() {
  for (int i = 0; i < 8; i++) {
    vector<char> row;
    for (int j = 0; j < 8; j++) {
      row.push_back('.');
    }
    theDisplay.push_back(row);
  }
}

int getFirewallOwner(Cell cell) {
  std::vector<Ability*> abilities = cell.getAbilities();
  for (int i = 0; i < abilities.size(); i++) {
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

void TextDisplay::notify(Subject &whoFrom) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Cell curCell = whoFrom.getInfo().theGrid[i][j];
      if (curCell.hasLink()) {
        theDisplay[i][j] = curCell.getLink()->getName();
      }
      else if (curCell.getServerPort()) {
        theDisplay[i][j] = 'S';
      }
      else if (getFirewallOwner(curCell) == 1) {
        theDisplay[i][j] = 'm';
      }
      else if (getFirewallOwner(curCell) == 2) {
        theDisplay[i][j] = 'w';
      }
      else {
        theDisplay[i][j] = '.';
      }
    }
  }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  return out;
}
