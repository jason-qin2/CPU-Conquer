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

void Grid::init(std::string pOneAbil, std::string pTwoAbil, 
std::string pOneLinks, std::string pTwoLinks, bool hasGraphics) {
    const int defaultGridSize = 8;
    for (size_t i = 0; i < defaultGridSize; i++) {
        for (size_t j = 0; j < defaultGridSize; j++) {
            theGrid[i].push_back(Cell(i, j));
        }
    }
}
void moveLink(Link *link, Direction dir);
// void addGraphicsDisplay(GraphicsDisplay graphicsDisplay) // adds GraphicsDisplay
void Grid::addTextDisplay(TextDisplay *textDisplay) {
    textDisplay = textDisplay;
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
