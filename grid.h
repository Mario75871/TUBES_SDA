#ifndef GRID_H
#define GRID_H

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

struct Tetromino;

extern int grid[GRID_HEIGHT][GRID_WIDTH];

void initGrid();
void printGrid(struct Tetromino* currentTetromino);
int checkFullLines();
void clearLine(int line);
int isValidPosition(int x, int y);

#endif
