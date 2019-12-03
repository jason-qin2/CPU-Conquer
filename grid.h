#ifndef GRID_H
#define GRID_H
#include <vector>
#include <iostream>
#include "cell.h"
#include "textDisplay.h"
#include "player.h"
#include "link.h"
#include "enums.h"
#include "info.h"
#include "graphics.h"

class Grid {
    private:
        std::vector<std::vector<Cell>> theGrid; // 2D Vector of grid cells
        TextDisplay *textDisplay = nullptr; // Renders the game with text
        GraphicsDisplay *graphicsDisplay = nullptr; // renders the game with graphics
        std::vector<Player*> players; // Vector of players of the game
        Player *activePlayer; // The player with the active turn
        void printPlayer(std::ostream &out, Player *player) const;
        std::vector<Ability*> initAbilities(std::string abilitiesStr, int playerNum);
        std::vector<Link*> initLinks(std::string linksStr, int playerNum);
        void move(size_t row, size_t col, Link *link);
        void serverPort(size_t row, Link *link);
        bool isValidMove(size_t row, size_t col);
    public:
        ~Grid();
        bool isFinished(); // returns True if the game is finished
        Player *whoWon(); // returns the winning player
        void init(std::string pOneAbil, std::string pTwoAbil, std::string pOneLinks,
            std::string pTwoLinks, bool hasGraphics); // initializes the game
        void moveLink(Link *link, Direction dir); // moves a link a certain direction
        Cell *getCell(int row, int col);
        Player *getPlayer(int playerNum);
        Player *getActivePlayer();
        void changeActivePlayer();
        void renderGraphics();
        void remove(Link *link);
        void spawnLink(Link *link);

        friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
