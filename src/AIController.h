#ifndef AICONTROLLER_H_
#define AICONTROLLER_H_

#include <cstdlib>
#include "Types.h"
#include "Tower.h"
#include "Enemy.h"

class AIController {
public:
    int total_waves;
    int enemies_per_wave;
    int wave;
    int spawned_this_wave;
    int base_enemy_health;

    AIController() {
        total_waves = 5;
        enemies_per_wave = 10;
        wave = 1;
        spawned_this_wave = 0;
        base_enemy_health = 3;
    }

    int chooseSpawnColumn(const Tower towers[], int towerCount,
                          const int occCols[], int occCount);

    int chooseEnemyType() {
        int r = rand() % 100;
        if (r < 50) return enemy_basic;
        if (r < 75) return enemy_fast;
        return enemy_strong;
    }

    void adapt(int player_score) {
        if (player_score >= wave * 80) {
            base_enemy_health++;
        }
    }

    int shouldSpawnThisTurn() const {
        return (wave <= total_waves) && (spawned_this_wave < enemies_per_wave);
    }

    void onSpawned() { spawned_this_wave++; }

    void onWaveCleared() {
        wave++;
        spawned_this_wave = 0;
    }

    int doneSpawningAllWaves() const {
        return wave > total_waves;
    }
};

#endif // AICONTROLLER_H_
