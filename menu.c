#include <stdio.h>
#include <windows.h>
#include "menu.h"
#include "utils.h"

void displayMainMenu() {
    clearScreen();
    printf("\n");
	setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	printCentered("========  =======  ========  =====    ==  ======= \n", 80);
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printCentered("   ==     ==          ==     ==   ==  ==  ==      \n", 80);
	setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printCentered("   ==     =====       ==     ======   ==  ======= \n", 80);
	setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printCentered("   ==     ==          ==     ==   ==  ==       == \n", 80);
	setColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printCentered("   ==     =======     ==     ==   ==  ==  ======= \n", 80);
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("\n");
    
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printCentered("+============================================+\n", 80);
    printCentered("|                                            |\n", 80);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printCentered("|             1. Start New Game              |\n", 80);
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printCentered("|             2. Leaderboard                 |\n", 80);
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printCentered("|             3. Game History                |\n", 80);
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printCentered("|             4. Instructions                |\n", 80);
    setColor(FOREGROUND_INTENSITY);
    printCentered("|             5. Exit                        |\n", 80);
    printCentered("|                                            |\n", 80);
    printCentered("+============================================+\n", 80);

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("\n");
}

void showInstructions() {
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
