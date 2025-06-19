#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include "utils.h"

void printCentered(const char* text, int totalWidth) {
    int len = strlen(text);
    int padding = (totalWidth - len) / 2;
    int i;
    for(i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
}

void clearScreen() {
    #ifdef _WIN32
    static HANDLE hStdOut = NULL;
    static CONSOLE_SCREEN_BUFFER_INFO csbi;
    static DWORD count, cellCount;
    static COORD homeCoords = {0, 0};
    
    if (hStdOut == NULL) {
        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hStdOut, &csbi);
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    }
    
    FillConsoleOutputCharacter(hStdOut, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hStdOut, homeCoords);
    #else
    system("clear");
    #endif
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printBorder() {
    int i;
    printf("+");
    for(i = 0; i < 40; i++) printf("-");
    printf("+\n");
}

void delay(int milliseconds) {
    Sleep(milliseconds);
}

char getKeyPress() {
    if(_kbhit()) {
        return _getch();
    }
    return 0;
}

int isValidInput(char input) {
    input = toupper(input);
    return (input == 'A' || input == 'D' || input == 'S' || 
            input == 'W' || input == 'U' || input == 'Q');
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
