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

int peekQueue(int position) {
    if(tetrominoQueue->front == NULL) {
        return -1;
    }
    
    QNode* current = tetrominoQueue->front;
    int i;
    for(i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }
    
    if(current == NULL) {
        return -1;
    }
    return current->tetrominoType;
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
