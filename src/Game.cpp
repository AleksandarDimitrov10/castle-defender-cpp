#include "Game.h"

Game::Game() {
    towerCount = 0;
    enemyCount = 0;
    score = 0;
    destroyed = 0;
    upgradePoints = 0;
    srand((unsigned)time(0));
}

void Game::setup() {
    cout << "=== CASTLE DEFENDER (Text) ===\n";
    cout << "Grid " << grid_rows << "x" << grid_cols << "\n";
    cout << "Castle at (" << castle.position.row << "," << castle.position.col << ")\n";
    cout << "Place up to 5 towers (not in rows 0-1, not on castle, empty cell).\n";

    for (int i = 0; i < max_towers; i++) {
        cout << "Tower " << (i + 1) << " row col (or -1 to stop): ";
        int r;
        cin >> r;

        if (r == -1) break;

        int c;
        cin >> c;

        if (!(r >= 0 && r < grid_rows && c >= 0 && c < grid_cols) || r < 2) {
            cout << "Invalid (bounds/top rows). Try again.\n";
            i--;
            continue;
        }

        Position p; p.row = r; p.col = c;

        if ((p.row == castle.position.row && p.col == castle.position.col) || !isEmptyCell(p)) {
            cout << "Invalid (occupied / castle). Try again.\n";
            i--;
            continue;
        }

        towers[towerCount] = Tower(p);
        towerCount++;
    }

    Grid::print(castle, towers, towerCount, enemies, enemyCount);
    printStats();
}

int Game::isEnemyAt(const Position& p) const {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].alive == 1 &&
            enemies[i].position.row == p.row && enemies[i].position.col == p.col) return 1;
    }
    return 0;
}

int Game::isTowerAt(const Position& p) const {
    for (int i = 0; i < towerCount; i++) {
        if (towers[i].position.row == p.row && towers[i].position.col == p.col) return 1;
    }
    return 0;
}

int Game::isEmptyCell(const Position& p) const {
    if (!(p.row >= 0 && p.row < grid_rows && p.col >= 0 && p.col < grid_cols)) return 0;
    if (p.row == castle.position.row && p.col == castle.position.col) return 0;
    if (isTowerAt(p)) return 0;
    if (isEnemyAt(p)) return 0;
    return 1;
}

int Game::isBlockedForEnemyMove(const Position& p) const {
    if (!(p.row >= 0 && p.row < grid_rows && p.col >= 0 && p.col < grid_cols)) return 1;
    if (p.row == castle.position.row && p.col == castle.position.col) return 0;
    if (isTowerAt(p)) return 1;
    if (isEnemyAt(p)) return 1;
    return 0;
}

void Game::spawnEnemyIfNeeded() {
    if (!ai.shouldSpawnThisTurn()) return;
    if (enemyCount >= max_enemies) return;

    int occ[grid_cols];
    int occN = 0;
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].alive == 1 && enemies[i].position.row == 0) {
            occ[occN] = enemies[i].position.col;
            occN++;
        }
    }

    int col = ai.chooseSpawnColumn(towers, towerCount, occ, occN);
    Position p;
    p.row = 0;
    p.col = col;

    if (!isEmptyCell(p)) return;

    int t = ai.chooseEnemyType();
    int hp = ai.base_enemy_health;
    int sp = 1;

    if (t == enemy_fast) {
        sp = 2;
        if (hp > 1) hp = hp - 1;
    } else if (t == enemy_strong) {
        sp = 1;
        hp = hp + 2;
    }

    enemies[enemyCount] = Enemy(p, hp, sp, t);
    enemyCount++;
    ai.onSpawned();
}

void Game::moveEnemies() {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].alive == 0) continue;

        int steps = enemies[i].speed;
        for (int s = 0; s < steps; s++) {
            Position cur = enemies[i].position;
            Position down;
            down.row = cur.row + 1; down.col = cur.col;

            Position dl;
            dl.row   = cur.row + 1; dl.col   = cur.col - 1;

            Position dr;
            dr.row   = cur.row + 1; dr.col   = cur.col + 1;

            if (!isBlockedForEnemyMove(down)) {
                enemies[i].position = down;
            } else if (!isBlockedForEnemyMove(dl)) {
                enemies[i].position = dl;
            } else if (!isBlockedForEnemyMove(dr)) {
                enemies[i].position = dr;
            } else {
                break;
            }
        }
    }
}

void Game::towersAttack() {
    for (int t = 0; t < towerCount; t++) {
        for (int e = 0; e < enemyCount; e++) {
            if (enemies[e].alive == 0) continue;

            int rowDiff = enemies[e].position.row - towers[t].position.row;
            if (rowDiff < 0) rowDiff = -rowDiff;

            int colDiff = enemies[e].position.col - towers[t].position.col;
            if (colDiff < 0) colDiff = -colDiff;

            if (rowDiff <= towers[t].range && colDiff <= towers[t].range) {
                enemies[e].health = enemies[e].health - towers[t].damage;
            }
        }
    }
}

void Game::cleanupDeadAndCastleHits() {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].alive == 0) continue;
        if (enemies[i].position.row == castle.position.row) {
            castle.health = castle.health - 10;
            enemies[i].alive = 0;
        }
    }

    Enemy keep[max_enemies];
    int k = 0;

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].health <= 0) {
            score = score + 10;
            destroyed = destroyed + 1;
            continue;
        }
        if (enemies[i].alive == 0) continue;
        keep[k] = enemies[i];
        k++;
    }

    for (int i = 0; i < k; i++) {
    	enemies[i] = keep[i];
    }

    enemyCount = k;
}

void Game:: printStats() const {
    cout << "Score: " << score
         << " | Destroyed: " << destroyed
         << " | Castle HP: " << castle.health
         << " | Wave " << ai.wave << "/" << ai.total_waves
         << " (spawned " << ai.spawned_this_wave << "/" << ai.enemies_per_wave << ")"
         << " | Upgrade Pts: " << upgradePoints
         << "\n";
}

void Game::promptUpgrades() {
    if (upgradePoints <= 0 || towerCount == 0) return;

    cout << "\n--- Upgrade Phase ---\n";
    cout << "You have " << upgradePoints << " upgrade point(s).\n";
    cout << "Choose a tower index [0.." << (towerCount-1) << "] and upgrade type:\n";
    cout << "  D = +1 damage,  R = +1 range\n";
    cout << "Enter -1 to skip.\n";

    while (upgradePoints > 0) {
        cout << "Upgrade> index type: ";
        int idx;
        cin >> idx;

        if (idx == -1) break;

        char type;
        cin >> type;

        if (idx < 0 || idx >= towerCount) {
            cout << "Invalid index.\n";
            continue;
        }

        if (type == 'D' || type == 'd') {
            towers[idx].damage = towers[idx].damage + 1;
            towers[idx].level  = towers[idx].level  + 1;
            upgradePoints--;
            cout << "Tower " << idx << " damage is now " << towers[idx].damage << "\n";
        } else if (type == 'R' || type == 'r') {
            towers[idx].range  = towers[idx].range  + 1;
            towers[idx].level  = towers[idx].level  + 1;
            upgradePoints--;
            cout << "Tower " << idx << " range is now " << towers[idx].range << "\n";
        } else {
            cout << "Type must be D or R.\n";
        }

        if (upgradePoints == 0) cout << "(no points left)\n";
    }
}

void Game::run() {
    cout << "\n--- GAME START ---\n";

    while (1) {
        if (castle.health <= 0) {
            cout << "\nGAME OVER\nPlayer Score: " << score
                 << "\nEnemies Destroyed: " << destroyed
                 << "\nCastle Health: 0\nWinner: AI\n";
            return;
        }

        spawnEnemyIfNeeded();
        moveEnemies();
        towersAttack();
        cleanupDeadAndCastleHits();

        Grid::print(castle, towers, towerCount, enemies, enemyCount);
        printStats();

        if (ai.spawned_this_wave == ai.enemies_per_wave && noEnemiesAlive()) {
            upgradePoints = upgradePoints + 1;
            ai.adapt(score);
            ai.onWaveCleared();

            if (ai.doneSpawningAllWaves()) {
                cout << "\nGAME OVER\nPlayer Score: " << score
                     << "\nEnemies Destroyed: " << destroyed
                     << "\nCastle Health: " << castle.health
                     << "\nWinner: Player\n";
                return;
            } else {
                promptUpgrades();
                cout << "--- Wave " << ai.wave
                     << " begins (enemy base HP = " << ai.base_enemy_health << ") ---\n";
            }
        }

        cout << "Enter 0 and press Enter to advance: ";
        int dummy; cin >> dummy;
    }
}
