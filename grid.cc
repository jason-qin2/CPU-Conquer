#include "grid.h"

bool Grid::isFinished() {
    for (auto &player: players) {
        if (player->downloadedDataCount() >= 4) {
            return true;
        } else if (player->downloadedVirusCount() >= 4) {
            return true;
        }
    }
    return false;
}

Player *Grid::whoWon() {
    Player *playerOne = players[0];
    Player *playerTwo = players[1];
    if ((playerOne->downloadedDataCount() >= 4) ||
        (playerTwo->downloadedVirusCount() >= 4)) {
        return playerOne;
    } else if ((playerTwo->downloadedDataCount() >= 4) ||
        (playerOne->downloadedVirusCount() >= 4)) {
        return playerTwo;
    }
    return nullptr;
}

void Grid::init() {
    for (size_t i = 0; i < defaultGridSize; i++) {
        for (size_t j = 0; j < defaultGridSize; j++) {
            theGrid[i].push_back(Cell(i, j));
        }
    }
}

bool isFirewall(Cell cell) {
  for (int i = 0; i < cell.getAbilities().size(); i++) {
    if (cell.getAbilities()[i].getAbilityType() == AbilityType::Firewall) {
      return true;
    }
  }
  return false;
}

bool isLinkBoost(Cell cell) {
  for (int i = 0; i < cell.getAbilities().size(); i++) {
    if (cell.getAbilities()[i].getAbilityType() == AbilityType::LinkBoost) {
      return true;
    }
  }
  return false;
}

void firewall(Cell cell) {
  Link *link = cell.getLink();
  int playerNum;
  for (int i = 0; i < cell.getAbilities().size(); i++) {
    if (cell.getAbilities()[i].getAbilityType() == AbilityType::Firewall) {
      playerNum = cell.getAbilities()[i].getPlayerNum();
    }
  }
  if (activePlayer->getPlayerNumber() == playerNum) {
    return;
  }
  else {
    link->show();
    if (link->getLinkType() == LinkType::Virus) {
      activePlayer->downloadLink(link);
    }
  }
}

bool isValidMove(size_t row, size_t col) {
  if (activePlayer->getPlayerNumber() == 1) {
    
  }
  else {

  }
}

void moveLink(Link *link, Direction dir) {
  Cell cell;
  size_t row;
  size_t col;
  for (int i = 0; i < theGrid.size(); i++) {
    for (int j = 0; j < theGrid.size(); j++) {
      if (link == theGrid[i][j].getLink()) {
        row = i;
        col = j;
        theGrid[i][j].removeLink();
      }
    }
  }
  if (dir = Direction::North) {
    if (isLinkBoost(cell)) {
      cell = theGrid[row - 2][col];
    }
    else {
      cell = theGrid[row - 1][col];
    }
    if (isFirewall(cell)) {
      firewall(cell);
    }
    cell.setLink(link);
  }
  else if (dir = Direction::East) {
    if (isLinkBoost(cell)) {
      cell = theGrid[row][col + 2];
    }
    else {
      cell = theGrid[row][col + 1];
    }
    if (isFirewall(cell)) {
      firewall(cell);
    }
    cell.setLink(link);
  }
  else if (dir = Direction::South) {
    if (isLinkBoost(cell)) {
      cell = theGrid[row + 2][col];
    }
    else {
      cell = theGrid[row + 1][col];
    }
    if (isFirewall(cell)) {
      firewall(cell);
    }
    cell.setLink(link);
  }
  else if (dir = Direction::West) {
    if (isLinkBoost(cell)) {
      cell = theGrid[row][col - 2];
    }
    else {
      cell = theGrid[row][col - 1];
    }
    if (isFirewall(cell)) {
      firewall(cell);
    }
    cell.setLink(link);
  }
} // moves a link a certain direction
// void addGraphicsDisplay(GraphicsDisplay graphicsDisplay) // adds GraphicsDisplay
void addTextDisplay(TextDisplay textDisplay); // adds TextDisplay

friend std::ostream &operator<<(std::ostream &out, const Grid &g);
