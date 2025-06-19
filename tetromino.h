#ifndef TETROMINO_H
#define TETROMINO_H

typedef struct Block {
    int x, y;
    struct Block* next;
} Block;

typedef struct Tetromino {
    Block* head;
    int type; // 0-6, jenis tetromino
    int centerX, centerY; // Untuk rotasi
} Tetromino;

// Tetromino shapes (7 types: I, O, T, S, Z, J, L)
extern int tetrominoShapes[7][4][2];

Tetromino* createTetromino(int type);
void freeTetromino(Tetromino* tetromino);
void moveTetromino(Tetromino* tetromino, int dx, int dy);
void rotateTetromino(Tetromino* tetromino);
int canMove(Tetromino* tetromino, int dx, int dy);
void placeTetromino(Tetromino* tetromino);
void printTetromino(Tetromino* tetromino);

#endif
