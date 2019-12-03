#ifndef INFO_H
#define INFO_H
#include <vector>

enum class State { Link, ServerPort, PlayerOneFireWall, PlayerTwoFireWall, Empty };

struct Info {
    size_t row, col;
    char linkName;
    State state;
};

#endif
