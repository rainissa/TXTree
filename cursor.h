#ifndef CURSOR_H
#define CURSOR_H

#define MAX_BARIS 100

// cursor baris & kolom
extern int cursor_row;
extern int cursor_col;

// validasi
int isCursorValid();

// navigasi baris
void moveUp();
void moveDown();

// navigasi kolom
void moveLeft();
void moveRight();

#endif