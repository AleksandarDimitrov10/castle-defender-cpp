#ifndef GAME_H_
#define GAME_H_

#include <iostream>
using namespace std;

#include <cstdlib>
#include <ctime>
#include "Grid.h"
#include "AIController.h"

const int max_towers  = 5;
const int max_enemies = 50;

// Game control (arrays only, simple I/O)
class Game {
public:
    Game();

    void setup();
    void run();    // main loop

private:
    Castle castle;
    Tower towers[max_towers];
    int towerCount;

    Enemy enemies[max_enemies];
    int enemyCount;

    AIController ai;

    int score;
    int destroyed;
    int upgradePoints;

    void printStats() const;
    int  isEnemyAt(const Position& p) const;
    int  isTowerAt(const Position& p) const;
    int  isEmptyCell(const Position& p) const;
    int  isBlockedForEnemyMove(const Position& p) const;

    void spawnEnemyIfNeeded();
    void moveEnemies();
    void towersAttack();
    void cleanupDeadAndCastleHits();
    int  noEnemiesAlive() const { return enemyCount == 0; }

    void promptUpgrades();
};

#endif // GAME_H_
