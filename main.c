#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "grid.h"
#include "tetromino.h"
#include "queue.h"
#include "score_history.h"	
#include "bst_score.h"
#include "menu.h"
#include "utils.h"

void startGame();

int gameRunning = 1;

void startGame() {
    clearScreen();
    hideCursor();
    initGrid();

    int score = 0;
    int level = 1;
    int linesCleared = 0;
    int gameOver = 0;
    int i;

    for(i = 0; i < 7; i++) {
        enqueue(rand() % 7);
    }

    Tetromino* currentTetromino = createTetromino(dequeue());
    enqueue(rand() % 7);

    int dropCounter = 0;
    int dropSpeed = 800 - (level * 100);
    const int INPUT_DELAY = 50;

    while(!gameOver) {

        gotoxy(0, 0);
        printCentered("=== TETRIS GAME ===", 80);
        printCentered("\n", 80);
        printCentered("Controls: [A] Left  [D] Right  [S] Drop  [W] Rotate  [Q] Quit", 80);
        printCentered("\n\n", 80);

        char info[100];
        snprintf(info, sizeof(info), "Score: %-8d Level: %-3d Lines: %-4d", score, level, linesCleared);
        printCentered(info, 80);
        printCentered("\n", 80);

        char preview[100];
        snprintf(preview, sizeof(preview), "Next pieces: %c %c %c", 
                 "IOSZTJL"[peekQueue(0)],
                 "IOSZTJL"[peekQueue(1)],
                 "IOSZTJL"[peekQueue(2)]);
        printCentered(preview, 80);
        printCentered("\n", 80);

        printGrid(currentTetromino);

        if(_kbhit()) {
            char input = _getch();
            input = toupper(input);

            switch(input) {
                case 'A': 
					if(canMove(currentTetromino, -1, 0)) { moveTetromino(currentTetromino, -1, 0); } 
					break;
                case 'D': if(canMove(currentTetromino, 1, 0)) { moveTetromino(currentTetromino, 1, 0); } break;
                case 'S': if(canMove(currentTetromino, 0, 1)) { moveTetromino(currentTetromino, 0, 1); score += 1; } break;
                case 'W': rotateTetromino(currentTetromino);
                    break;
                case 'P':
    				clearScreen();
    				printCentered("\nGame dijeda. Tekan [P] lagi untuk melanjutkan...\n", 80);
    				while(1) {
        				if(_kbhit()) {
            				char pauseKey = toupper(_getch());
            				if(pauseKey == 'P') break;
        				}
        				Sleep(100);
    				}
    				break;
                case 'Q':
                    gameOver = 1;
                    continue;
            }
        }

        dropCounter += INPUT_DELAY;
        if(dropCounter >= dropSpeed) {
            if(canMove(currentTetromino, 0, 1)) {
                moveTetromino(currentTetromino, 0, 1);
            } else {
                placeTetromino(currentTetromino);

                int cleared = checkFullLines();
                if(cleared > 0) {
                    linesCleared += cleared;
                    score += cleared * 100 * level;

                    if(linesCleared >= level * 10) {
                        level++;
                        dropSpeed = 800 - (level * 100);
                        if(dropSpeed < 100) dropSpeed = 100;
                    }
                }

                freeTetromino(currentTetromino);
                currentTetromino = createTetromino(dequeue());
                enqueue(rand() % 7);

                if(!canMove(currentTetromino, 0, 0)) {
                    gameOver = 1;
                }
            }
            dropCounter = 0;
        }

        Sleep(INPUT_DELAY);
    }

    clearScreen();
    printf("\n\n");
    printCentered("GAME OVER\n", 80);

    char gameOverInfo[100];
    snprintf(gameOverInfo, sizeof(gameOverInfo), "Final Score: %d | Level: %d | Lines Cleared: %d",
             score, level, linesCleared);
    printCentered(gameOverInfo, 80);
    printf("\n\n");

    addHistory(score, level);

    char playerName[20];
    printCentered("Enter your name: ", 80);
    scanf("%19s", playerName);
    insertScore(score, playerName);

    printf("\n");
    printCentered("Score saved to leaderboard!", 80);
    Sleep(1500);

    freeTetromino(currentTetromino);
    showCursor();
}

int main() {
    srand(time(NULL));

    initGrid();
    initQueue();
    initHistory();
    loadLeaderboard("leaderboard.txt");


    while(gameRunning) {
        showCursor();
        displayMainMenu();

        printCentered("Select option (1-5): ", 80);
        int choice;
        scanf("%d", &choice);

        switch(choice) {
            case 1: startGame(); break;
            case 2: showLeaderboard(); break;
            case 3: showGameHistory(); break;
            case 4: showInstructions(); break;
            case 5: gameRunning = 0; printf("\n"); printCentered("Thank you for playing!\n", 80); break;
            default: printf("\n"); printCentered("Invalid choice! Please select 1-5\n", 80); Sleep(1000);
        }

        if(choice != 5) {
            printf("\n");
            printCentered("Press Enter to continue...", 80);
            while(getchar() != '\n');
            getchar();
        }
    }

    saveLeaderboard("leaderboard.txt");

    freeHistory();
    freeQueue();
    freeTree(scoreRoot);

    return 0;
}
