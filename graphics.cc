#include "graphics.h"
#include "subject.h"

GraphicsDisplay::GraphicsDisplay() : window{new Xwindow(400, 900)} {
    window->fillRectangle(0, 10, 400, 30);
    window->fillRectangle(0, 20, 400, 10, Xwindow::White);
    window->fillRectangle(0, 80, 400, 30);
    window->fillRectangle(0, 90, 400, 10, Xwindow::White);
    window->drawStringFont(165, 65, "RAIINET",
    "-misc-open sans extrabold-extrabold-r-normal--0-0-0-0-p-0-ascii-0");
}

void GraphicsDisplay::drawPlayerData(Player *player, Player *activePlayer) {
    int startingHeight = (player->getPlayerNumber() == 1) ? 100 : 700;
    window->fillRectangle(0, startingHeight, 400, 200, Xwindow::White);
    int gutterWidth = 20;
    std::string playerName = "PLAYER " + std::to_string(player->getPlayerNumber());
    std::string downloadedStr = "DOWNLOADED";
    std::string dataCount = std::to_string(player->getDlDataCount()) + " Data";
    std::string virusCount = std::to_string(player->getDlVirusCount()) + " Virus";
    std::string abilitiesStr = "Abilities";
    std::vector<Link*> links = player->getOwnedLinks();
    int linkRowHeight = startingHeight + 140;
    for (size_t i = 0; i < links.size(); i++) {
        std::string linkChar(1, links[i]->getName());
        std::string linkName = linkChar + ": ";
        std::string linkString = "";
        window->drawStringFont(gutterWidth + ((i % 4) * 90), linkRowHeight, linkName,
        "-misc-open sans-bold-r-normal--0-0-0-0-p-0-ascii-0");
        if (links[i]->isHidden() && player != activePlayer) {
            linkString += "?";
        } else {
            if (links[i]->getLinkType() == LinkType::Virus) {
                linkString += "V";
            } else if (links[i]->getLinkType() == LinkType::Data) {
                linkString += "D";
            }
            linkString += std::to_string(links[i]->getStrength());
        }
        window->drawStringFont(gutterWidth + ((i % 4) * 90) + 20, linkRowHeight, linkString,
        "-misc-open sans-medium-r-normal--0-0-0-0-p-0-ascii-0");
        if (i == 3 || i == 7) {
            linkRowHeight += 40;
        }
    }
    window->fillRectangle(0, startingHeight + 20, 400, 50);
    window->drawStringFont(gutterWidth, startingHeight + 50, playerName, 
        "-misc-open sans extrabold-extrabold-r-normal--0-0-0-0-p-0-ascii-0", Xwindow::White);
    window->drawStringFont(gutterWidth, startingHeight + 100, downloadedStr,
    "-misc-open sans-bold-r-normal--0-0-0-0-p-0-ascii-0");
    window->drawStringFont(gutterWidth + 180, startingHeight + 100, dataCount,
    "-misc-open sans-bold-r-normal--0-0-0-0-p-0-ascii-0", Xwindow::Green);
    window->drawStringFont(gutterWidth + 300, startingHeight + 100, virusCount,
    "-misc-open sans-bold-r-normal--0-0-0-0-p-0-ascii-0", Xwindow::Red);
}

void GraphicsDisplay::notify(Subject &whoFrom) {
    Info cellInfo = whoFrom.getInfo();
    size_t row = (cellInfo.row * 50) + 300;
    size_t col = cellInfo.col * 50;
    std::string cellString;
    int colour = Xwindow::Black;
    if (cellInfo.state == State::Link) {
        cellString = std::string(1, cellInfo.linkName);
    } else if (cellInfo.state == State::ServerPort) {
        colour = Xwindow::Blue;
        cellString = "S";
    } else if (cellInfo.state == State::PlayerOneFireWall) {
        colour = Xwindow::Red;
        cellString = "M";
    } else if (cellInfo.state == State::PlayerTwoFireWall) {
        colour = Xwindow::Red;
        cellString = "W";
    } else if (cellInfo.state == State::Empty) {
        window->fillRectangle(col, row, cellSize, cellSize, colour);
        return;
    }
    window->fillRectangle(col, row, cellSize, cellSize, colour);
    window->drawStringFont(
        col + 20, row + 30, 
        cellString, 
        "-misc-open sans extrabold-extrabold-r-normal--0-0-0-0-p-0-ascii-0", 
        Xwindow::White
    );
}
