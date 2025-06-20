#include <stdio.h>
#include <stdlib.h>
#include "score_history.h"
#include "utils.h"

History* historyHead = NULL;
History* historyTail = NULL;
int gameCounter = 0;

void initHistory() {
    historyHead = NULL;
    historyTail = NULL;
    gameCounter = 0;
}

void addHistory(int score, int level) {
    History* newNode = (History*)malloc(sizeof(History));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->gameNumber = ++gameCounter;
    newNode->score = score;
    newNode->level = level;
    newNode->prev = historyTail;
    newNode->next = NULL;

    if (historyTail != NULL)
        historyTail->next = newNode;
    else
        historyHead = newNode;

    historyTail = newNode;
}

void showHistoryForward() {
    History* current = historyHead;
    printf("===== RIWAYAT PERMAINAN =====\n");
    while (current != NULL) {
        printf("Game #%d - Skor: %d - Level: %d\n", current->gameNumber, current->score, current->level);
        current = current->next;
    }
}
void showHistoryBackward() {
    History* current = historyTail;
    printf("===== RIWAYAT PERMAINAN =====\n");
    while (current != NULL) {
        printf("Game #%d - Skor: %d - Level: %d\n", current->gameNumber, current->score, current->level);
        current = current->prev;
    }
}

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

void freeHistory() {
    History* current = historyHead;
    while (current != NULL) {
        History* temp = current;
        current = current->next;
        free(temp);
    }
    historyHead = NULL;
    historyTail = NULL;
    gameCounter = 0;
}

int getHistoryCount() {
    int count = 0;
    History* current = historyHead;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
