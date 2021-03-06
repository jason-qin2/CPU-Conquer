#ifndef CELL_H
#define CELL_H
#include <vector>
#include <cstddef>
#include "enums.h"
#include "link.h"
#include "ability.h"
#include "subject.h"
#include "info.h"

class Cell : public Subject {
  bool hasServerPort; //whether the cell has a server port
  size_t row; //row of cell
  size_t col; //column of cell
  Link *link; //link on cell, if any
  std::vector<Ability*> abilities; //abilities of cell

public:
  Cell(size_t r, size_t c); //constructor
  bool hasLink(); //whether there is a link on the cell
  Link *getLink(); //returns link on the cell
  bool hasAbilities(); //whether the cell has abilities
  std::vector<Ability*> getAbilities(); //gets the abilities of the cell
  void setLink(Link *link); //places a link on the cell
  void removeLink(); //removes link on the cell
  void addAbility(Ability *ability); //adds an ability to the cell
  bool getServerPort(); //whether the cell has a server port
  int getFirewallOwner(); //returns 0 (no firewall), 1 or 2
  Info getInfo() override;
};

#endif
