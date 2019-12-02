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
                printInvalidArgs(argv[0]);
                return 1;
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
    try {
        g.init(pOneAbils, pTwoAbils, pOneLinks, pTwoLinks, enabledGraphics);
    } catch (InvalidArguments) {
        printInvalidArgs(argv[0]);
        return 1;
    }
    return 0;
}