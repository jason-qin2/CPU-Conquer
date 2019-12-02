#include <vector>
#include <iostream>
#include "grid.h"
#include "exceptions.h"

bool Grid::isFinished() {
    for (auto &player: players) {
        if (player->getDlDataCount() >= 4) {
            return true;
        } else if (player->getDlVirusCount() >= 4) {
            return true;
        }
    }
}

Player *Grid::whoWon() {
  Player *playerOne = players[0];
  Player *playerTwo = players[1];
  if ((playerOne->getDlDataCount() >= 4) ||
  (playerTwo->getDlDataCount() >= 4)) {
    return playerOne;
  } else if ((playerTwo->getDlDataCount() >= 4) ||
  (playerOne->getDlDataCount() >= 4)) {
    return playerTwo;
  }
  return nullptr;
}


bool isFirewall(Cell cell) {
  for (int i = 0; i < cell.getAbilities().size(); i++) {
    if (cell.getAbilities()[i]->getAbilityType() == AbilityType::FireWall) {
      return true;
    }
  }
  return false;
}

bool isLinkBoost(Link *link) {
  for (int i = 0; i < link->getAbilities().size(); i++) {
    if (link->getAbilities()[i]->getAbilityType() == AbilityType::LinkBoost) {
      return true;
    }
  }
  return false;
}

void firewall(Cell cell, Player *activePlayer) {
  Link *link = cell.getLink();
  int playerNum;
  for (int i = 0; i < cell.getAbilities().size(); i++) {
    if (cell.getLink()->getAbilities()[i]->getAbilityType() == AbilityType::FireWall) {
      playerNum = cell.getAbilities()[i]->getPlayerNum();
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

bool Grid::isValidMove(size_t row, size_t col) {
  int playerNum = activePlayer->getPlayerNumber();
  Cell newCell = theGrid[row][col];
  if (row < 8 && col < 8) {
    return true;
  } else if (newCell.hasLink()) {
    if (newCell.getLink()->getPlayerNum() == playerNum) {
      return false;
    } else {
        return true;
    }
  } else if (newCell.getServerPort()) {
      if(row == 0 && playerNum == 1) {
          return false;
      } else if(row == 7 && playerNum == 2) {
          return false;
      } else {
          return true;
      }
  }
}

void moveOffGrid(size_t row, size_t col, Player *activePlayer, Link *link) {
  int playerNum = activePlayer->getPlayerNumber();
  if (playerNum == 1) {
    if (row > 7 && col >= 0 && col <= 7) {
      activePlayer->downloadLink(link);
    }
  }
  if (playerNum == 2) {
    if (row < 0 && col >= 0 && col <= 7) {
      activePlayer->downloadLink(link);
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

void Grid::serverport(size_t row, Link *link) {
    if(row == 0) {
        players[0]->downloadLink(link);
    } else {
        players[1]->downloadLink(link);
    }
}

void Grid::move(size_t row, size_t col, Link *link) {
  if (isValidMove(row, col)) {
      Cell cell = theGrid[row][col];
    if (isFirewall(cell)) {
      firewall(cell, activePlayer);
    }
    if(cell.getServerPort()) {
        serverport(row, link);
    }
    if(willBattle(cell)) {
        Link *opponentLink = cell.getLink();
        battle(link, opponentLink, activePlayer, players );
    }
    theGrid[row][col].setLink(link);
  }
  else {
    moveOffGrid(row, col, activePlayer, link);
  }
}

void Grid::moveLink(Link *link, Direction dir) {
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
    if (isLinkBoost(link)) {
      move(row - 2, col, link);
    }
    else {
      move(row - 1, col, link);
    }
  }
  else if (dir == Direction::East) {
    if (isLinkBoost(link)) {
      move(row, col + 2, link);
    }
    else {
      move(row, col + 1, link);
    }
  }
  else if (dir == Direction::South) {
    if (isLinkBoost(link)) {
      move(row + 2, col, link);
    }
    else {
      move(row + 1, col, link);
    }
  }
  else if (dir == Direction::West) {
    if (isLinkBoost(link)) {
      move(row, col - 2, link);
    }
    else {
      move(row, col - 1, link);
    }
  }
  notifyObservers();
} // moves a link a certain direction

std::vector<Ability*> Grid::initAbilities(std::string abilitiesStr, int playerNum) {
    std::vector<Ability*> abilitiesArr;
    int LBCount = 0, FWCount = 0, DLCount = 0;
    int PLCount = 0, SCCount = 0;
    for (char const &c: abilitiesStr) {
        if (c == 'L') {
            abilitiesArr.push_back(new Ability(AbilityType::LinkBoost, playerNum));
            LBCount++;
        } else if (c == 'F') {
            abilitiesArr.push_back(new Ability(AbilityType::FireWall, playerNum));
            FWCount++;
        } else if (c == 'D') {
            abilitiesArr.push_back(new Ability(AbilityType::Download, playerNum));
            DLCount++;
        } else if (c == 'P') {
            abilitiesArr.push_back(new Ability(AbilityType::Polarize, playerNum));
            PLCount++;
        } else if (c == 'S') {
            abilitiesArr.push_back(new Ability(AbilityType::Scan, playerNum));
            SCCount++;
        }
    }
    if (LBCount > 2 || FWCount > 2 || DLCount > 2 || PLCount > 2 || SCCount > 2) {
        throw InvalidArguments();
    }
    return abilitiesArr;
}

std::vector<Link*> Grid::initLinks(std::string linksStr, int playerNum) {
    std::vector<Link*> linksArr;
    std::string linkNames;
    if (linksStr.size() != 16) {
        throw InvalidArguments();
    }
    if (playerNum == 1) {
        linkNames = "abcdefgh";
    } else if (playerNum == 2) {
        linkNames = "ABCDEFGH";
    }
    for (int i = 0; i < linksStr.size(); i++) {
        LinkType linkType;
        if (linksStr[i] == 'V') {
            linkType = LinkType::Virus;
        } else if (linksStr[i] == 'D') {
            linkType = LinkType::Data;
        } else {
            throw InvalidArguments();
        }
        int linkStrength = linksStr[i + 1] - '0';
        if (linkStrength > 4 || linkStrength < 1) {
            throw InvalidArguments();
        }
        linksArr.push_back(new Link(linkStrength, linkType, linkNames[0], playerNum));
        linkNames.erase(0, 1);
        i++;
    }
    return linksArr;
}

void Grid::init(std::string pOneAbil, std::string pTwoAbil,
std::string pOneLinks, std::string pTwoLinks,
bool hasGraphics) {
    if (hasGraphics) {
        // initialize Graphics
    } else {
        textDisplay = new TextDisplay();
        attach(textDisplay);
    }

    std::vector<Ability*> playerOneAbilities = initAbilities(pOneAbil, 1);
    std::vector<Ability*> playerTwoAbilities = initAbilities(pTwoAbil, 2);
    std::vector<Link*> playerOneLinks = initLinks(pOneLinks, 1);
    std::vector<Link*> playerTwoLinks = initLinks(pTwoLinks, 2);
    Player *playerOne = new Player(1, playerOneAbilities, playerOneLinks, *this);
    Player *playerTwo = new Player(2, playerTwoAbilities, playerTwoLinks, *this);
    players.push_back(playerOne);
    players.push_back(playerTwo);
    activePlayer = playerOne;
    const int defaultGridSize = 8;
    for (size_t i = 0; i < defaultGridSize; i++) {
        std::vector<Cell> cellRow;
        for (size_t j = 0; j < defaultGridSize; j++) {
            Cell *newCell = new Cell(i, j);
            cellRow.push_back(*newCell);
        }
        theGrid.push_back(cellRow);
    }
    for (int i = 0; i < defaultGridSize; i++) {
        if (i == 3 | i == 4) {
            theGrid[1][i].setLink(playerOneLinks[i]);
            theGrid[6][i].setLink(playerTwoLinks[i]);
        } else {
            theGrid[0][i].setLink(playerOneLinks[i]);
            theGrid[7][i].setLink(playerTwoLinks[i]);
        }
    }
    notifyObservers();
}

void Grid::printPlayer(std::ostream &out, Player *player) const {
    using namespace std;
    out << "Player " << player->getPlayerNumber() << ':' << endl;
    out << "Downloaded: " << player->getDlDataCount() << "D, ";
    out << player->getDlVirusCount() << 'V' << endl;
    out << "Abilities: " << player->getAbilityCount() << endl;
    std::vector<Link*> links = player->getOwnedLinks();
    for (int i = 0; i < links.size(); i++) {
        out << links[i]->getName() << ": ";
        if (links[i]->isHidden() && player != activePlayer) {
            out << '?';
        } else {
            if (links[i]->getLinkType() == LinkType::Virus) {
                out << 'V';
            } else if (links[i]->getLinkType() == LinkType::Data) {
                out << 'D';
            }
            out << links[i]->getStrength();
        }
        if (i == 3 || i == 7) {
            out << endl;
        } else {
            out << ' ';
        }
    }
}

Cell *Grid::getCell(int row, int col) {
    return &theGrid[row][col];
}

Player *Grid::getPlayer(int playerNum) {
    for (auto player: players) {
        if (player->getPlayerNumber() == playerNum) {
            return player;
        }
    }
}

Info Grid::getInfo() {
    return Info{theGrid};
}

Player *Grid::getActivePlayer() {
    return activePlayer;
}

void Grid::changeActivePlayer() {
    for (auto player: players) {
        if (player->getPlayerNumber() != activePlayer->getPlayerNumber()) {
            activePlayer = player;
            return;
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    Player *playerOne = g.players[0];
    Player *playerTwo = g.players[1];
    g.printPlayer(out, playerOne);
    out << "========" << std::endl;
    out << *g.textDisplay;
    out << "========" << std::endl;
    g.printPlayer(out, playerTwo);
    return out;
}
