#include "AIController.h"
#include <cstdlib>

int AIController::chooseSpawnColumn(const Tower towers[], int towerCount,
                                    const int occCols[], int occCount)
{
    for (int tries = 0; tries < 50; tries++) {
        int col = rand() % grid_cols;
        int occupied = 0;
        for (int i = 0; i < occCount; i++) {
            if (occCols[i] == col) {
                occupied = 1;
                break;
            }
        }
        if (occupied) continue;

        int tooClose = 0;
        for (int t = 0; t < towerCount; t++) {
            int diff = towers[t].position.col - col;
            if (diff < 0) diff = -diff;
            if (diff < 3) {
                tooClose = 1;
                break;
            }
        }
        if (tooClose) continue;

        return col;
    }

    for (int col = 0; col < grid_cols; col++) {
        int occupied = 0;
        for (int i = 0; i < occCount; i++) {
            if (occCols[i] == col) {
            	occupied = 1;
            	break;
            }
        }
        if (!occupied) return col;
    }

    return grid_cols / 2;
}
