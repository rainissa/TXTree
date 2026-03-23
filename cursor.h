#ifndef CURSOR_H
#define CURSOR_H

#define MAX_ROW 100

// cursor baris & kolom
extern int cursor_row;
extern int cursor_col;

// validasi
int isCursorValid();

//inisiasi
void setCursor(int row, int col);

// navigasi baris
void moveUp();
void moveDown();

// navigasi kolom
void moveLeft();
void moveRight();

#endif