#include "graphics.h"
#include "subject.h"

//void fillRectangle(int x, int y, int width, int height, int colour=Black);
GraphicsDisplay::GraphicsDisplay() : window{new Xwindow(400, 800)} {
    for (int row = 200; row < 600; row += 50) {
        for (int col = 0; col < 400; col += 50) {
            window->fillRectangle(col + 5, row, 40, 40);
        }
    }
}

void GraphicsDisplay::drawPlayerData(Player *player, Player *activePlayer) {
    int startingHeight = (player->getPlayerNumber() == 1) ? 0 : 600;
    int gutterWidth = 20;
    std::string playerName = "Player " + std::to_string(player->getPlayerNumber());
    std::string downloadedStr = "Downloaded";
    std::string dataCount = std::to_string(player->getDlDataCount()) + " Data";
    std::string virusCount = std::to_string(player->getDlVirusCount()) + " Virus";
    std::string abilitiesStr = "Abilities";
    std::vector<Link*> links = player->getOwnedLinks();
    int linkRowHeight = startingHeight + 140;
    for (size_t i = 0; i < links.size(); i++) {
        std::string linkChar(1, links[i]->getName());
        std::string linkString = linkChar + ": ";
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
        window->drawString(gutterWidth + ((i % 4) * 50), linkRowHeight, linkString);
        if (i == 3 || i == 7) {
            linkRowHeight += 40;
        }
    }
    window->drawBigString(gutterWidth, startingHeight + 50, playerName);
    window->drawString(gutterWidth, startingHeight + 100, downloadedStr);
    window->drawString(gutterWidth, startingHeight + 120, dataCount);
    window->drawString(gutterWidth + 100, startingHeight + 120, virusCount);
}

void GraphicsDisplay::notify(Subject &whoFrom) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Info cellInfo = whoFrom.getInfo();
            size_t row = (cellInfo.row * 50) + 200;
            size_t col = cellInfo.col * 50;
            std::string cellString;
            if (cellInfo.state == State::Link) {
                cellString = std::string(1, cellInfo.linkName);
                window->drawBigString(col + 20, row + 40, cellString, Xwindow::White);
            } else if (cellInfo.state == State::ServerPort) {
                window->fillRectangle(col + 5, row, 40, 40, Xwindow::Blue);
                cellString = "S";
                window->drawBigString(col + 20, row + 40, cellString, Xwindow::White);
            } else if (cellInfo.state == State::PlayerOneFireWall) {
                window->fillRectangle(col + 5, row, 40, 40, Xwindow::Red);
                cellString = "M";
                window->drawBigString(col + 20, row + 40, cellString, Xwindow::White);
            } else if (cellInfo.state == State::PlayerTwoFireWall) {
                window->fillRectangle(col + 5, row, 40, 40, Xwindow::Red);
                cellString = "W";
                window->drawBigString(col + 20, row + 40, cellString, Xwindow::White);
            } else if (cellInfo.state == State::Empty) {
                window->fillRectangle(col + 5, row, 40, 40, Xwindow::Black);
            }
        }
    }
}
