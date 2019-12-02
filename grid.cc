#include "grid.h"

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
    for (char const &c: abilitiesStr) {
        if (c == 'L') {
            abilitiesArr.push_back(new Ability(AbilityType::LinkBoost, playerNum));
        } else if (c == 'F') {
            abilitiesArr.push_back(new Ability(AbilityType::FireWall, playerNum));
        } else if (c == 'D') {
            abilitiesArr.push_back(new Ability(AbilityType::Download, playerNum));
        } else if (c == 'P') {
            abilitiesArr.push_back(new Ability(AbilityType::Polarize, playerNum));
        } else if (c == 'S') {
            abilitiesArr.push_back(new Ability(AbilityType::Scan, playerNum));
        }
    }
}

std::vector<Link*> Grid::initLinks(std::string linksStr, int playerNum) {
    std::vector<Link*> linksArr;
    std::string linkNames;
    if (linksStr.size() != 16) {
        throw; //ERROR
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
            throw; //ERROR
        }
        int linkStrength = linksStr[i + 1] - '0';
        if (linkStrength > 4 || linkStrength < 1) {
            throw; //ERROR
        }
        linksArr.push_back(new Link(linkStrength, linkType, linkNames[0]));
        linkNames.erase(linkNames[0]);
        i++;
    }
    return linksArr;
}

void Grid::init(std::string pOneAbil = "LFDSP", std::string pTwoAbil = "LFDSP", 
std::string pOneLinks = "V1V2V3V4D1D2D3D4", std::string pTwoLinks = "V1V2V3V4D1D2D3D4", 
bool hasGraphics) {
    if (hasGraphics) {
        // initialize Graphics
    } else {
        textDisplay = new TextDisplay();
    }
    std::vector<Ability*> playerOneAbilities = initAbilities(pOneAbil, 1);
    std::vector<Ability*> playerTwoAbilities = initAbilities(pTwoAbil, 2);
    std::vector<Link*> playerOneLinks = initLinks(pOneLinks, 1);
    std::vector<Link*> playerTwoLinks = initLinks(pTwoLinks, 2);
    Player *playerOne = new Player(1, playerOneAbilities, playerOneLinks);
    Player *playerTwo = new Player(2, playerTwoAbilities, playerTwoLinks);
    const int defaultGridSize = 8;
    for (size_t i = 0; i < defaultGridSize; i++) {
        for (size_t j = 0; j < defaultGridSize; j++) {
            theGrid[i].push_back(Cell(i, j));
        }
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
}

void Grid::printPlayer(std::ostream &out, Player *player) const {
    using namespace std;
    out << "Player " << player->getPlayerNumber() << ':' << endl;
    out << "Downloaded: " << player->getDlDataCount() << 'D, ';
    out << player->getDlVirusCount() << 'V';
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

std::ostream &operator<<(std::ostream &out, const Grid &g) {
    Player *playerOne = g.players[0];
    Player *playerTwo = g.players[1];
    g.printPlayer(out, playerOne);
    out << g.textDisplay;
    g.printPlayer(out, playerTwo);
}
