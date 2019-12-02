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
void moveLink(Link *link, Direction dir); // moves a link a certain direction
// void addGraphicsDisplay(GraphicsDisplay graphicsDisplay) // adds GraphicsDisplay
void addTextDisplay(TextDisplay textDisplay); // adds TextDisplay

Info Grid::getInfo() {
    return Info{theGrid};
}

friend std::ostream &operator<<(std::ostream &out, const Grid &g);