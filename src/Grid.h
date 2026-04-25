#ifndef GRID_H_
#define GRID_H_

#include <iostream>
using namespace std;

#include "Castle.h"
#include "Tower.h"
#include "Enemy.h"


class Grid {
public:
    static void print(const Castle& castle,
                      const Tower towers[], int towerCount,
                      const Enemy enemies[], int enemyCount)
    {
        for (int r = 0; r < grid_rows; r++) {
            for (int c = 0; c < grid_cols; c++) {
                char ch = '.';

                if (r == castle.position.row && c == castle.position.col) {
                    ch = 'C';
                }

                for (int i = 0; i < towerCount; i++) {
                    if (towers[i].position.row == r && towers[i].position.col == c) {
                        ch = 'T';
                        break;
                    }
                }

                // Enemies
                for (int j = 0; j < enemyCount; j++) {
                    if (enemies[j].alive == 1 &&
                        enemies[j].position.row == r &&
                        enemies[j].position.col == c)
                    {
                        if (enemies[j].type == enemy_fast)       ch = 'F';
                        else if (enemies[j].type == enemy_strong) ch = 'S';
                        else                                      ch = 'B';
                        break;
                    }
                }

                cout << ch;
            }
            cout << "\n";
        }
    }
};

#endif // GRID_H_
