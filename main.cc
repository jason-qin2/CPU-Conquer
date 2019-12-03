#include <iostream>
#include <fstream>
#include <string.h>
#include "grid.h"
#include "exceptions.h"
using namespace std;

void printInvalidArgs(char *programName) {
    std::cout << "Invalid arguments supplied" << endl;
    std::cout << "Usage: " << programName << " ";
    std::cout << "-ability1 <order> -ability2 <order> ";
    std::cout << "-link1 <order> -link2 <order> -graphics (optional)" << endl;
}

int main(int argc, char *argv[]) {
    string pOneAbils = "LFDSP";
    string pTwoAbils = "LFDSP";
    string pOneLinks = "V1V2V3V4D1D2D3D4";
    string pTwoLinks = "V1V2V3V4D1D2D3D4";
    bool enabledGraphics = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-graphics") == 0) {
            enabledGraphics = true;
        } else {
            if (strcmp(argv[i], "-ability1") == 0) {
                pOneAbils = argv[i + 1];
            } else if (strcmp(argv[i], "-ability2") == 0) {
                pTwoAbils = argv[i + 1];
            } else if (strcmp(argv[i], "-link1") == 0) {
                pOneLinks = argv[i + 1];
            } else if (strcmp(argv[i], "-link2") == 0) {
                pTwoLinks = argv[i + 1];
            }
            i++;
        }
    }
    Grid g;
    try {
        g.init(pOneAbils, pTwoAbils, pOneLinks, pTwoLinks, enabledGraphics);
    } catch (InvalidArguments) {
        printInvalidArgs(argv[0]);
        return 1;
    }
    string cmd;
    streambuf* streamBuffer = 0; // default cin streambuf object
    ifstream inputFile;     // file stream for reading input
    bool usedAbility = false;
    while (std::cin >> cmd) {
        if (cmd == "abilities") {
            g.getActivePlayer()->printAbilities(std::cout);
        } else if (cmd == "ability") {
            if (usedAbility) {
                std::cout << "Already used an ability this turn." << endl;
                continue;
            }
            int abilityNum;
            std::cin >> abilityNum;
            try {
                g.getActivePlayer()->useAbility(abilityNum);
                usedAbility = true;
            } catch (AbilityError) {
                std::cout << "Invalid usage of ability" << endl;
            }
        } else if (cmd == "board") {
            std::cout << g;
        } else if (cmd == "sequence") {
            string fileName;
            std::cin >> fileName;
            inputFile.open(fileName);
            streamBuffer = std::cin.rdbuf(inputFile.rdbuf());
        } else if (cmd == "quit") {
            return 0;
        } else if (cmd == "move") {
          Link *link;
          char name;
          string d;
          Direction dir;
          std::cin >> name;
          std::cin >> d;
          if (d == "up") {
            dir = Direction::North;
          } else if (d == "right") {
            dir = Direction::East;
          } else if (d == "down") {
            dir = Direction::South;
          } else if (d == "left") {
            dir = Direction::West;
          }
          for (size_t i = 0; i < g.getActivePlayer()->getOwnedLinks().size(); i++) {
            if (g.getActivePlayer()->getOwnedLinks()[i]->getName() == name) {
              link = g.getActivePlayer()->getOwnedLinks()[i];
            }
          }
          try {
              g.moveLink(link, dir);
              g.changeActivePlayer();
              std::cout << g;
          } catch (InvalidMove) {
              std::cout << "This is not a valid move, please enter a valid move." << std::endl; 
          }
        }
    }
    if (streamBuffer) {
        std::cin.rdbuf(streamBuffer);
    }
    return 0;
}
