#include <vector>
#include <iostream>
#include "textDisplay.h"
#include "cell.h"
#include "ability.h"
#include "link.h"
#include "enums.h"
#include "subject.h"
#include "observer.h"

using namespace std;

TextDisplay::TextDisplay() {
  for (int i = 0; i < 8; i++) {
    vector<char> row;
    for (int j = 0; j < 8; j++) {
      row.push_back('.');
    }
    theDisplay.push_back(row);
  }
}

void TextDisplay::notify(Subject &whoFrom) {
    Info cellInfo = whoFrom.getInfo();
    size_t row = cellInfo.row;
    size_t col = cellInfo.col;
    if (cellInfo.state == State::Link) {
      theDisplay[row][col] = cellInfo.linkName;
    }
    else if (cellInfo.state == State::ServerPort) {
      theDisplay[row][col] = 'S';
    }
    else if (cellInfo.state == State::PlayerOneFireWall) {
      theDisplay[row][col] = 'm';
    }
    else if (cellInfo.state == State::PlayerTwoFireWall) {
      theDisplay[row][col] = 'w';
    }
    else if (cellInfo.state == State::Empty) {
      theDisplay[row][col] = '.';
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  return out;
}
