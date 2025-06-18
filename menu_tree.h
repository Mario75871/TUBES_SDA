#ifndef MENU_TREE_H
#define MENU_TREE_H

typedef struct Menu {
    char label[30];
    int menuId;
    struct Menu* left;  // opsi kiri
    struct Menu* right; // opsi kanan
    struct Menu* parent; // parent node
} Menu;

extern Menu* mainMenuRoot;

Menu* createMainMenu();
void showMainMenu();
Menu* navigate(Menu* current, char direction);
void freeMenu(Menu* root);
void showInstructions();

#endif
