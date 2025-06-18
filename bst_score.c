#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst_score.h"
#include "utils.h"

TreeNode* scoreRoot = NULL;

TreeNode* createNode(int score, char* name) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->score = score;
    strcpy(newNode->playerName, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insertScore(int score, char* name) {
    if(scoreRoot == NULL) {
        scoreRoot = createNode(score, name);
        return scoreRoot;
    }
    
    TreeNode* current = scoreRoot;
    TreeNode* parent = NULL;
    
    while(current != NULL) {
        parent = current;
        if(score <= current->score) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    TreeNode* newNode = createNode(score, name);
    if(score <= parent->score) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    return newNode;
}

void printDescending(TreeNode* root) {
    if(root != NULL) {
        printDescending(root->right);
        printf("%-15s : %d\n", root->playerName, root->score);
        printDescending(root->left);
    }
}

TreeNode* findMax(TreeNode* root) {
    if(root == NULL) return NULL;
    while(root->right != NULL) {
        root = root->right;
    }
    return root;
}

void showLeaderboard() {
    clearScreen();
    if(scoreRoot == NULL) {
        printf("Belum ada skor yang tersimpan.\n");
        return;
    }
    
    printf("=== LEADERBOARD ===\n");
    printf("(Urutan dari skor tertinggi)\n\n");
    printf("%-15s : %s\n", "Nama", "Skor");
    printf("-------------------------\n");
    
    printDescending(scoreRoot);
    
    TreeNode* topPlayer = findMax(scoreRoot);
    if(topPlayer) {
        printf("\n\nTOP PLAYER: %s dengan skor %d\n", 
               topPlayer->playerName, topPlayer->score);
    }
}

void saveNodeToFile(TreeNode* node, FILE* file) {
    if (node == NULL || file == NULL) return;
    fprintf(file, "%d %s\n", node->score, node->playerName);
    saveNodeToFile(node->left, file);
    saveNodeToFile(node->right, file);
}

void saveLeaderboard(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Tidak bisa membuka file leaderboard untuk menyimpan.\n");
        return;
    }
    saveNodeToFile(scoreRoot, file);
    fclose(file);
}

void loadLeaderboard(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;
    int score;
    char playerName[20];
    while (fscanf(file, "%d %s", &score, playerName) == 2) {
        insertScore(score, playerName);
    }
    fclose(file);
}

void freeTree(TreeNode* root) {
    if(root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
