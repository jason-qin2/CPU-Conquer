#include <vector>
#include <iostream>
#include "grid.h"
#include "cell.h"


using namespace std;

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
    if (cell.getLink()->getAbilities()[i].getAbilityType() == AbilityType::Firewall) {
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

bool isValidMove(size_t row, size_t col, Player *player) {
  int playerNum = player->getPLayerNumber();
  Cell newCell = theGrid[row][col];
  if (row < 8 && col < 8) {
    return true;
  } else if (newCell.hasLink()) {
    if (newCell.getLink()->getPlayerNum() == playerNum) {
      return false;
    }
  } else if (newCell.hasServerPort()) {
    return false;
  }
}

void moveOffGrid(size_t row, size_t col, Player *Player, Link *link) {
  int playerNum = player->getPLayerNumber();
  if (playerNum == 1) {
    if (row > 7 && col >= 0 && col <= 7) {
      player->downloadLink(link);
    }
  }
  if (playerNum == 2) {
    if (row < 0 && col >= 0 && col <= 7) {
      player->downloadLink(link);
    }
  }
}

bool willBattle(Cell cell) {
    if(cell.hasLink()) {
        return true; 
    } else {
        return false; 
    }
}

void battle(Link *ownLink, Link *opponentLink, Player *activePlayer, std::vector<Player*> players) {
    ownLink->show();
    opponentLink->show();
    int opponentID = (activePlayer->getPlayerNumber() == 1) ? 2 : 1; 
    if(ownLink->getStrength() >= opponentLink->getStrength()) {
        activePlayer->downloadLink(opponentLink);
    } else {
        players[opponentID - 1]->downloadLink(ownLink);
    }
}

void serverport(Link *link, size_t row, std::vector<Player*> players) {
    if(row == 0) {
        players[0]->downloadLink(link);
    } else {
        players[1]->downloadLink(link);
    }
}

void move(Cell cell, size_t row, size_t col, Player *activePlayer, Link *link, std::vector<Player*> players) {
  if (isValidMove(row, col, activePlayer)) {
    if (isFirewall(cell)) {
      firewall(cell);
    }
    if(cell.getServerPort()) {
        serverport(link, row, players);
    }
    if(willBattle(cell)) {
        Link *opponentLink = cell.getLink();
        battle(link, opponentLink, activePlayer, players );
    }
    cell.setLink(link);
  }
  else {
    moveOffGrid(row, col, activePlayer, link);
  }
}

void Grid::moveLink(Link *link, Direction dir) {
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
  if (dir == Direction::North) {
    if (isLinkBoost(cell)) {
      move(cell, row - 2, col, activePlayer, link, players);
    }
    else {
      move(cell, row - 1, col, activePlayer, link, players);
    }
  }
  else if (dir == Direction::East) {
    if (isLinkBoost(cell)) {
      move(cell, row, col + 2, activePlayer, link, players);
    }
    else {
      move(cell, row, col + 1, activePlayer, link, players);
    }
  }
  else if (dir == Direction::South) {
    if (isLinkBoost(cell)) {
      move(cell, row + 2, col, activePlayer, link, players);
    }
    else {
      move(cell, row + 1, col, activePlayer, link, players);
    }
  }
  else if (dir == Direction::West) {
    if (isLinkBoost(cell)) {
      move(cell, row, col - 2, activePlayer, link, players);
    }
    else {
      move(cell, row, col - 1, activePlayer, link, players);
    }
  }

} // moves a link a certain direction
// void addGraphicsDisplay(GraphicsDisplay graphicsDisplay) // adds GraphicsDisplay
void addTextDisplay(TextDisplay textDisplay); // adds TextDisplay

friend std::ostream &operator<<(std::ostream &out, const Grid &g);
