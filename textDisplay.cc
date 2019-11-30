#include <vector>
#include "textDisplay.h"

using namespace std;

TextDisplay() {
  for (int i = 0; i < 8; i++) {
    vector<char> row;
    for (int j = 0; j < 8; j++) {
      row.push_back('.');
    }
    theDisplay.push_back(row);
  }
}
void notify(Subject &whoFrom) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Cell curCell = whoFrom[i][j];
      if (curCell.hasLink()) {
        theDisplay[i][j] = curCell.getLink().getName();
      }
      else if (curCell.hasServerPort()) {
        theDisplay[i][j] = 'S';
      }
      else {
        theDisplay[i][j] = '.';
      }
    }
  }

}
friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  return out;
}
