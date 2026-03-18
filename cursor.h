#ifndef CURSOR_H
#define CURSOR_H

#define MAX_ROW 100

<<<<<<< HEAD
extern int cursor; 
=======
// cursor baris & kolom
extern int cursor_row;
extern int cursor_col;
>>>>>>> cursor

// validasi
int isCursorValid();

// navigasi baris
void moveUp();
void moveDown();

// navigasi kolom
void moveLeft();
void moveRight();

#endif