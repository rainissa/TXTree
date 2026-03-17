#ifndef CURSOR_H
#define CURSOR_H

#define MAX_ROW 100

<<<<<<< HEAD
extern int cursor_row;
extern int cursor_karakter;
=======
// extern supaya variabel ini bisa dibaca di main.c dan text-edit.c
extern int cursor; 
>>>>>>> cursor

int isCursorValid();
void moveUp();
void moveDown();

#endif