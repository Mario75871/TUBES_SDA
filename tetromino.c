#include <stdio.h>
#include <stdlib.h>
#include "tetromino.h"
#include "grid.h"

int tetrominoShapes[7][4][2] = {
    {{0,1}, {1,1}, {2,1}, {3,1}},//I
    {{0,0}, {1,0}, {0,1}, {1,1}},//O
    {{1,0}, {2,0}, {0,1}, {1,1}},//S
    {{0,0}, {1,0}, {1,1}, {2,1}},//Z
    {{1,0}, {0,1}, {1,1}, {2,1}},//T
    {{0,0}, {0,1}, {1,1}, {2,1}},//J
    {{2,0}, {0,1}, {1,1}, {2,1}}//L
};

Tetromino* createTetromino(int type) {
    int i;
    Tetromino* tetromino = (Tetromino*)malloc(sizeof(Tetromino));
    tetromino->type = type;
    tetromino->head = NULL;
    tetromino->centerX = GRID_WIDTH / 2;
    tetromino->centerY = 1;
    
    for(i = 3; i >= 0; i--) {
        Block* newBlock = (Block*)malloc(sizeof(Block));
        newBlock->x = tetromino->centerX + tetrominoShapes[type][i][0] - 1;
        newBlock->y = tetromino->centerY + tetrominoShapes[type][i][1];
        newBlock->next = tetromino->head;
        tetromino->head = newBlock;
    }
    return tetromino;
}

void freeTetromino(Tetromino* tetromino) {
    if(!tetromino) return;
    Block* current = tetromino->head;
    while(current) {
        Block* temp = current;
        current = current->next;
        free(temp);
    }
    free(tetromino);
}

void moveTetromino(Tetromino* tetromino, int dx, int dy) {
    if(!tetromino) return;
    Block* current = tetromino->head;
    while(current) {
        current->x += dx;
        current->y += dy;
        current = current->next;
    }
    tetromino->centerX += dx;
    tetromino->centerY += dy;
}

int canMove(Tetromino* tetromino, int dx, int dy) {
    if(!tetromino) return 0;
    Block* current = tetromino->head;
    while(current) {
        int newX = current->x + dx;
        int newY = current->y + dy;
        if(newX < 0 || newX >= GRID_WIDTH || newY >= GRID_HEIGHT) {
            return 0;
        }
        if(newY >= 0 && grid[newY][newX] != 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void rotateTetromino(Tetromino* tetromino) {
    if(!tetromino || tetromino->type == 1) return;
    Block* current = tetromino->head;
    int originalX[4], originalY[4];
    int i = 0;
    
    while(current && i < 4) {
        originalX[i] = current->x;
        originalY[i] = current->y;
        int relativeX = current->x - tetromino->centerX;
        int relativeY = current->y - tetromino->centerY;
        current->x = tetromino->centerX - relativeY;
        current->y = tetromino->centerY + relativeX;
        current = current->next;
        i++;
    }
    
    if(!canMove(tetromino, 0, 0)) {
        current = tetromino->head;
        i = 0;
        while(current && i < 4) {
            current->x = originalX[i];
            current->y = originalY[i];
            current = current->next;
            i++;
        }
    }
}

void placeTetromino(Tetromino* tetromino) {
    if(!tetromino) return;
    Block* current = tetromino->head;
    while(current) {
        if(current->y >= 0 && current->y < GRID_HEIGHT && 
           current->x >= 0 && current->x < GRID_WIDTH) {
            grid[current->y][current->x] = tetromino->type + 1;
        }
        current = current->next;
    }
}

void printTetromino(Tetromino* tetromino) {
    if(!tetromino) return;
    printf("Current Tetromino (Type %d):\n", tetromino->type);
    Block* current = tetromino->head;
    while(current) {
        printf("Block at (%d, %d)\n", current->x, current->y);
        current = current->next;
    }
}
