#ifndef UTILS_H
#define UTILS_H

void printCentered(const char* text, int totalWidth);
void clearScreen();
void gotoxy(int x, int y);
void setColor(int color);
void printBorder();
void delay(int milliseconds);
char getKeyPress();
int isValidInput(char input);
void hideCursor();
void showCursor();

#endif
