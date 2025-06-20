#ifndef SCORE_HISTORY_H
#define SCORE_HISTORY_H

typedef struct History {
    int score;
    int level;
    int gameNumber;
    struct History* prev;
    struct History* next;
} History;

extern History* historyHead;
extern History* historyTail;
extern int gameCounter;

void initHistory();
void addHistory(int score, int level);
void showHistoryForward();
void showHistoryBackward();
void showGameHistory();
void freeHistory();
int getHistoryCount();

#endif
