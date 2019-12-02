#ifndef GRID_H
#define GRID_H
#include <vector>
#include <iostream>
#include "subject.h"
#include "cell.h"
#include "textDisplay.h"
#include "player.h"
#include "link.h"
#include "enums.h"

class Grid : public Subject {
    private:
        std::vector<std::vector<Cell>> theGrid; // 2D Vector of grid cells
        TextDisplay *textDisplay = nullptr; // Renders the game with text
        // GraphicDisplay *graphicDisplay = nullptr; // renders the game with graphics 
        std::vector<Player*> players; // Vector of players of the game
        Player *activePlayer; // The player with the active turn
        void printPlayer(std::ostream &out, Player *player) const;
    public:
        bool isFinished(); // returns True if the game is finished
        Player *whoWon(); // returns the winning player
        void init(std::string pOneAbil, std::string pTwoAbil, std::string pOneLinks, 
            std::string pTwoLinks, bool hasGraphics); // initializes the game
        void moveLink(Link *link, Direction dir); // moves a link a certain direction
        // void addGraphicsDisplay(GraphicsDisplay *graphicsDisplay) // adds GraphicsDisplay
        void addTextDisplay(TextDisplay *textDisplay); // adds TextDisplay
        Info getInfo() override;

        friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
