#include <stdio.h>
#include <stdlib.h>
#include "score_history.h"
#include "utils.h"

History* historyHead = NULL;
History* historyTail = NULL;
int gameCounter = 0;

void initHistory() { /* ... no changes ... */ }
void addHistory(int score, int level) { /* ... no changes ... */ }
void showHistoryForward() { /* ... no changes ... */ }
void showHistoryBackward() { /* ... no changes ... */ }

void showGameHistory() {
    clearScreen();
    if (historyHead == NULL) {
        printf("No game history available.\n");
        return;
    }
    int choice;
    printf("=== LIHAT RIWAYAT PERMAINAN ===\n");
    printf("1. Dari Terlama ke Terbaru\n");
    printf("2. Dari Terbaru ke Terlama\n");
    printf("Pilihan Anda (1-2): ");
    scanf("%d", &choice);
    printf("\n");
    switch (choice) {
        case 1: showHistoryForward(); break;
        case 2: showHistoryBackward(); break;
        default: printf("Pilihan tidak valid!\n");
    }
}

void freeHistory() { /* ... no changes ... */ }
int getHistoryCount() { /* ... no changes ... */ }
