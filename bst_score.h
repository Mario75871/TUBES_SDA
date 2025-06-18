#ifndef BST_SCORE_H
#define BST_SCORE_H

typedef struct TreeNode {
    int score;
    char playerName[20];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

extern TreeNode* scoreRoot;

TreeNode* insertScore(int score, char* name);
void printDescending(TreeNode* root);
TreeNode* findMax(TreeNode* root);
void showLeaderboard();
void freeTree(TreeNode* root);

void saveLeaderboard(const char* filename);
void loadLeaderboard(const char* filename);

#endif
