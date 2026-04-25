#ifndef CASTLE_H_
#define CASTLE_H_

#include "Types.h"

class Castle {
public:
    Position position;
    int health;

    Castle() {
        position.row = grid_rows - 1;
        position.col = grid_cols / 2;
        health = 100;
    }

    Castle(Position p) {
        position = p;
        health = 100;
    }
};

#endif // CASTLE_H_
