#ifndef CURSOR_H
#define CURSOR_H

#define MAX_ROW 100
#define MAX_COL 100

extern int cursor_row;
extern int cursor_karakter;

void moveLeft();
void moveRight();
void moveUp();
void moveDown();

#endif