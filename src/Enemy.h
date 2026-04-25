#ifndef ENEMY_H_
#define ENEMY_H_

#include "Types.h"

class Enemy {
public:
    Position position;
    int health;
    int speed;
    int alive; // alive = 1 , dead = 0
    int type;

    Enemy() {
        position.row = 0; position.col = 0;
        health = 3;
        speed = 1;
        alive = 0;
        type = enemy_basic;
    }

    Enemy(Position p, int h, int s, int t) {
        position = p;
        health = h;
        speed = s;
        alive = 1;
        type = t;
    }

    int isDead() const {
        return (alive == 0) || (health <= 0);
    }
};

#endif // ENEMY_H_
