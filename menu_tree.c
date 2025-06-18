#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_tree.h"
#include "utils.h" // Ditambahkan untuk fungsi clearScreen()

Menu* mainMenuRoot = NULL;

Menu* createMenuNode(char* label, int id) {
    Menu* newMenu = (Menu*)malloc(sizeof(Menu));
    strcpy(newMenu->label, label);
    newMenu->menuId = id;
    newMenu->left = NULL;
    newMenu->right = NULL;
    newMenu->parent = NULL;
    return newMenu;
}

Menu* createMainMenu() {
    mainMenuRoot = createMenuNode("TETRIS MAIN MENU", 0);
    
    Menu* startGame = createMenuNode("Start Game", 1);
    Menu* leaderboard = createMenuNode("Leaderboard", 2);
    Menu* history = createMenuNode("Game History", 3);
    Menu* instructions = createMenuNode("Instructions", 4);
    Menu* exit = createMenuNode("Exit", 5);
    
    mainMenuRoot->left = startGame;
    mainMenuRoot->right = leaderboard;
    
    startGame->parent = mainMenuRoot;
    startGame->right = history;
    
    leaderboard->parent = mainMenuRoot;
    leaderboard->left = instructions;
    leaderboard->right = exit;
    
    history->parent = startGame;
    instructions->parent = leaderboard;
    exit->parent = leaderboard;
    
    return mainMenuRoot;
}

void showMainMenu() {
    printf("\n=== TETRIS GAME MENU ===\n");
    printf("1. Start Game\n");
    printf("2. Leaderboard\n");
    printf("3. Game History\n");
    printf("4. Instructions\n");
    printf("5. Exit\n");
    printf("========================\n");
}

Menu* navigate(Menu* current, char direction) {
    if(!current) return NULL;
    
    switch(direction) {
        case 'L':
        case 'l':
            return current->left;
        case 'R':
        case 'r':
            return current->right;
        case 'U':
        case 'u':
            return current->parent;
        default:
            return current;
    }
}

void showTreeNavigation() {
    printf("\n=== NAVIGASI TREE MENU ===\n");
    printf("Gunakan navigasi tree:\n");
    printf("L - Kiri (Start Game)\n");
    printf("R - Kanan (Leaderboard)\n");
    printf("Dari Start Game -> R (History)\n");
    printf("Dari Leaderboard -> L (Instructions), R (Exit)\n");
    printf("U - Kembali ke parent\n");
    printf("Q - Keluar dari navigasi\n\n");
    
    Menu* current = mainMenuRoot;
    char input;
    
    while(1) {
        printf("Current: %s (ID: %d)\n", current->label, current->menuId);
        printf("Available: ");
        if(current->left) printf("L(%s) ", current->left->label);
        if(current->right) printf("R(%s) ", current->right->label);
        if(current->parent) printf("U(%s) ", current->parent->label);
        printf("\nInput (L/R/U/Q): ");
        
        scanf(" %c", &input);
        
        if(input == 'Q' || input == 'q') {
            break;
        }
        
        Menu* next = navigate(current, input);
        if(next) {
            current = next;
            if(current->menuId >= 1 && current->menuId <= 5) {
                printf("Memilih: %s\n", current->label);
                break;
            }
        } else {
            printf("Navigasi tidak valid!\n");
        }
    }
}

void showInstructions() {
    // MODIFIKASI: Layar dibersihkan sebelum menampilkan petunjuk
    clearScreen();
    
    printf("Kontrol Game:\n");
    printf("A/D - Gerakkan tetromino kiri/kanan\n");
    printf("S   - Percepat jatuh ke bawah\n");
    printf("W   - Rotasi tetromino\n");
    printf("U   - Undo (batalkan langkah terakhir)\n");
    printf("Q   - Keluar dari game\n\n");
    
    printf("Jenis Tetromino:\n");
    printf("0 - I piece (garis lurus)\n");
    printf("1 - O piece (kotak)\n");
    printf("2 - T piece (bentuk T)\n");
    printf("3 - S piece (bentuk S)\n");
    printf("4 - Z piece (bentuk Z)\n");
    printf("5 - J piece (bentuk J)\n");
    printf("6 - L piece (bentuk L)\n\n");
    
    printf("Scoring:\n");
    printf("- Setiap garis yang terhapus = 100 x Level\n");
    printf("- Level naik setiap 10 garis terhapus\n");
    printf("- Kecepatan bertambah setiap level naik\n\n");
    
    printf("Fitur Khusus:\n");
    printf("- Undo: Batalkan maksimal %d langkah terakhir\n", 10);
    printf("- Queue: Lihat tetromino selanjutnya\n");
    printf("- Leaderboard: Skor tertinggi tersimpan\n");
    printf("- History: Riwayat semua permainan\n");
}

void freeMenu(Menu* root) {
    if(root != NULL) {
        freeMenu(root->left);
        freeMenu(root->right);
        free(root);
    }
}
