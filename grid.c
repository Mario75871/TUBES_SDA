#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "grid.h"
#include "tetromino.h"
#include "utils.h"

int grid[GRID_HEIGHT][GRID_WIDTH];

#define TOP_LEFT_CORNER     "\xDA"
#define TOP_RIGHT_CORNER    "\xBF"
#define BOTTOM_LEFT_CORNER  "\xC0"
#define BOTTOM_RIGHT_CORNER "\xD9"
#define HORIZONTAL_LINE     "\xC4"
#define VERTICAL_LINE       "\xB3"
#define BLOCK_CHAR          "\xDB"
#define SHADOW_CHAR         "\xB0"

typedef enum {
    COLOR_I = 1, COLOR_O, COLOR_T, COLOR_S, COLOR_Z, 
    COLOR_J, COLOR_L, COLOR_SHADOW = 8
} BlockColors;

void initGrid() {
    int i, j;
    for(i = 0; i < GRID_HEIGHT; i++) {
        for(j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = 0;
        }
    }
}

void printGrid(struct Tetromino* currentTetromino) {
    const int SCREEN_WIDTH = 80;
    const int GRID_DISPLAY_WIDTH = GRID_WIDTH * 2 + 4;
    const int LEFT_PADDING = (SCREEN_WIDTH - GRID_DISPLAY_WIDTH) / 2;
    
    char paddingStr[LEFT_PADDING + 1];
    memset(paddingStr, ' ', LEFT_PADDING);
    paddingStr[LEFT_PADDING] = '\0';
    
    int i, j, k;
    int tempGrid[GRID_HEIGHT][GRID_WIDTH];
    memcpy(tempGrid, grid, sizeof(grid));
    
    if(currentTetromino) {
        int shadowY = currentTetromino->centerY;
        while(canMove((Tetromino*)currentTetromino, 0, shadowY - currentTetromino->centerY + 1)) {
            shadowY++;
        }
        
        Block* current = currentTetromino->head;
        while(current) {
            int x = current->x;
            int y = current->y + (shadowY - currentTetromino->centerY);
            if(y >= 0 && y < GRID_HEIGHT && x >= 0 && x < GRID_WIDTH && grid[y][x] == 0) {
                tempGrid[y][x] = COLOR_SHADOW;
            }
            current = current->next;
        }
        
        current = currentTetromino->head;
        while(current) {
            if(current->y >= 0 && current->y < GRID_HEIGHT && 
               current->x >= 0 && current->x < GRID_WIDTH) {
                tempGrid[current->y][current->x] = currentTetromino->type + 1;
            }
            current = current->next;
        }
    }

    printf(paddingStr);
    printf("%s", TOP_LEFT_CORNER);
    for(j = 0; j < GRID_WIDTH*2+2; j++) printf("%s", HORIZONTAL_LINE);
    printf("%s\n", TOP_RIGHT_CORNER);

    for(i = 0; i < GRID_HEIGHT; i++) {
        printf(paddingStr);
        printf("%s ", VERTICAL_LINE);
        
        for(j = 0; j < GRID_WIDTH; j++) {
            switch(tempGrid[i][j]) {
                case COLOR_I: setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
                case COLOR_O: setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
                case COLOR_T: setColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
                case COLOR_S: setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
                case COLOR_Z: setColor(FOREGROUND_RED | FOREGROUND_INTENSITY); break;
                case COLOR_J: setColor(FOREGROUND_BLUE | FOREGROUND_GREEN); break;
                case COLOR_L: setColor(FOREGROUND_RED | FOREGROUND_GREEN); break;
                case COLOR_SHADOW: 
                    setColor(FOREGROUND_INTENSITY);
                    printf("%s%s", SHADOW_CHAR, SHADOW_CHAR);
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    continue;
                default: 
                    setColor(FOREGROUND_INTENSITY);
                    printf("  ");
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    continue;
            }
            printf("%s%s", BLOCK_CHAR, BLOCK_CHAR);
            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        printf(" %s\n", VERTICAL_LINE);
    }

    printf(paddingStr);
    printf("%s", BOTTOM_LEFT_CORNER);
    for(j = 0; j < GRID_WIDTH*2+2; j++) printf("%s", HORIZONTAL_LINE);
    printf("%s\n\n", BOTTOM_RIGHT_CORNER);
}

int checkFullLines() {
    int linesCleared = 0;
    int i, j;
    
    for(i = GRID_HEIGHT - 1; i >= 0; i--) {
        int fullLine = 1;
        for(j = 0; j < GRID_WIDTH; j++) {
            if(grid[i][j] == 0) {
                fullLine = 0;
                break;
            }
        }
        if(fullLine) {
            Sleep(200); 
            clearLine(i);
            linesCleared++;
            i++; 
        }
    }
    return linesCleared;
}

void clearLine(int line) {
    int i, j;
    for(i = line; i > 0; i--) {
        for(j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = grid[i-1][j];
        }
    }
    for(j = 0; j < GRID_WIDTH; j++) {
        grid[0][j] = 0;
    }
}

int isValidPosition(int x, int y) {
    return (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT && grid[y][x] == 0);
}
