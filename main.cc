#include <iostream>
#include <string>
#include "grid.h"
using namespace std;


int main(int argc, char *argv[]) {
    string pOneAbils;
    string pTwoAbils;
    string pOneLinks;
    string pTwoLinks;
    bool enabledGraphics = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "-graphics") {
            enabledGraphics = true;
        } else {
            if (argc <= i + 1) {
                throw invalid_argument("Invalid command line args supplied");
            }
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
    g.init(pOneAbils, pTwoAbils, pOneLinks, pTwoLinks, enabledGraphics);
    return 0;
}