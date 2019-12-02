#include <iostream>
#include <string>
#include "grid.h"
#include "exceptions.h"
using namespace std;

void printInvalidArgs(char *programName) {
    cout << "Invalid arguments supplied" << endl;
    cout << "Usage: " << programName << " ";
    cout << "-ability1 <order> -ability2 <order> ";
    cout << "-link1 <order> -link2 <order> -graphics (optional)" << endl;
}

int main(int argc, char *argv[]) {
    string pOneAbils = "LFDSP";
    string pTwoAbils = "LFDSP";
    string pOneLinks = "V1V2V3V4D1D2D3D4";
    string pTwoLinks = "V1V2V3V4D1D2D3D4";
    bool enabledGraphics = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "-graphics") {
            enabledGraphics = true;
        } else {
            if (argv[i] == "-ability1") {
                pOneAbils = argv[i + 1];
            } else if (argv[i] == "-ability2") {
                pTwoAbils = argv[i + 1];
            } else if (argv[i] == "-link1") {
                pOneLinks = argv[i + 1];
            } else if (argv[i] == "-link2") {
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
    bool usedAbility = false;
    while (true) {
        cin >> cmd;
        if (cmd == "abilities") {
            g.getActivePlayer()->printAbilities(cout);
        } else if (cmd == "ability") {
            int abilityNum;
            cin >> abilityNum;
            try {
                g.getActivePlayer()->useAbility(abilityNum);
                usedAbility = true;
                g.changeActivePlayer();
            } catch (AbilityError) {
                cout << "Invalid usage of ability" << endl;
            }
        } else if (cmd == "board") {
            cout << g;
        } else if (cmd == "quit") {
            return 0;
        } else if (cmd == "move") {
          Link *link;
          char name;
          string d;
          Direction dir;
          cin >> name;
          cin >> d;
          if (d == "up") {
            dir = Direction::North;
          } else if (d == "right") {
            dir = Direction::East;
          } else if (d == "down") {
            dir = Direction::South;
          } else if (d == "left") {
            dir = Direction::West;
          }
          for (int i = 0; i < g.getActivePlayer()->getOwnedLinks().size(); i++) {
            if (g.getActivePlayer()->getOwnedLinks()[i]->getName() == name) {
              link = g.getActivePlayer()->getOwnedLinks()[i];
            }
          }
          g.moveLink(link, dir);
          cout << g;
        }
    }
    return 0;
}
