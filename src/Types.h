#ifndef TYPES_H_
#define TYPES_H_

#include <cstdlib>

const int grid_rows = 20;
const int grid_cols = 20;

const int enemy_basic  = 0;
const int enemy_fast   = 1;
const int enemy_strong = 2;

struct Position {
    int row;
    int col;
};

#endif // TYPES_H_
