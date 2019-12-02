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
    return false;
}

Player *Grid::whoWon() {
    Player *playerOne = players[0];
    Player *playerTwo = players[1];
    if ((playerOne->getDlDataCount() >= 4) || 
        (playerTwo->getDlVirusCount() >= 4)) {
        return playerOne;
    } else if ((playerTwo->getDlDataCount() >= 4) || 
        (playerOne->getDlVirusCount() >= 4)) {
        return playerTwo;
    }
    return nullptr;
}

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

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    Player *playerOne = g.players[0];
    Player *playerTwo = g.players[1];
    g.printPlayer(out, playerOne);
    out << "========" << std::endl;
    out << *g.textDisplay;
    out << "========" << std::endl;
    g.printPlayer(out, playerTwo);
}
