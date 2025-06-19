#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* tetrominoQueue = NULL;

void initQueue() {
    tetrominoQueue = (Queue*)malloc(sizeof(Queue));
    tetrominoQueue->front = NULL;
    tetrominoQueue->rear = NULL;
}

void enqueue(int type) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    newNode->tetrominoType = type;
    newNode->next = NULL;
    
    if(tetrominoQueue->rear == NULL) {
        tetrominoQueue->front = tetrominoQueue->rear = newNode;
    } else {
        tetrominoQueue->rear->next = newNode;
        tetrominoQueue->rear = newNode;
    }
}

int dequeue() {
    if(tetrominoQueue->front == NULL) {
        return -1; // Queue empty
    }
    
    QNode* temp = tetrominoQueue->front;
    int type = temp->tetrominoType;
    
    tetrominoQueue->front = tetrominoQueue->front->next;
    
    if(tetrominoQueue->front == NULL) {
        tetrominoQueue->rear = NULL;
    }
    
    free(temp);
    return type;
}

int peekQueue() {
    if(tetrominoQueue->front == NULL) {
        return -1;
    }
    return tetrominoQueue->front->tetrominoType;
}

void freeQueue() {
    if(!tetrominoQueue) return;
    
    while(tetrominoQueue->front) {
        QNode* temp = tetrominoQueue->front;
        tetrominoQueue->front = tetrominoQueue->front->next;
        free(temp);
    }
    
    free(tetrominoQueue);
    tetrominoQueue = NULL;
}

int isQueueEmpty() {
    return (tetrominoQueue->front == NULL);
}
