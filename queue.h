#ifndef QUEUE_H
#define QUEUE_H

typedef struct QNode {
    int tetrominoType;
    struct QNode* next;
} QNode;

typedef struct Queue {
    QNode* front;
    QNode* rear;
} Queue;

extern Queue* tetrominoQueue;

void initQueue();
void enqueue(int type);
int dequeue();
int peekQueue(int position);
void freeQueue();
int isQueueEmpty();

#endif
