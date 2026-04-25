#ifndef TOWER_H_
#define TOWER_H_

#include "Types.h"

class Tower {
public:
    Position position;
    int range;
    int damage;
    int level;

    Tower() {
        position.row = 0; position.col = 0;
        range = 2;
        damage = 1;
        level = 1;
    }

    Tower(Position p) {
        position = p;
        range = 2;
        damage = 1;
        level = 1;
    }
};

#endif // TOWER_H_
