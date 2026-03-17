#include <stdio.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <string.h>
#include "history.h"
=======
>>>>>>> e4d8919e289fe9f218912ed5eb313c39dff72f87
#include "cursor.h"
#include "history.h"
#include "text-edit.h"

// Variabel buffer global dari text-edit.c
extern char buffer[MAX_ROW][MAX_COL];
extern int jumlahBaris;
<<<<<<< HEAD
=======
#include "cursor.h"
#include "history.h"
#include "text-edit.h"
>>>>>>> f5416eac6ce18fc94290e32d0a8fe0c1b8d491fd
=======
>>>>>>> e4d8919e289fe9f218912ed5eb313c39dff72f87

Action undoStack[STACK_SIZE];
int undoTop = -1;

Action redoStack[STACK_SIZE];
int redoTop = -1;

void pushUndo(int row, int karakter, char c){

    if(undoTop < STACK_SIZE-1){

        undoTop++;
        undoStack[undoTop].row = row;
        undoStack[undoTop].karakter = karakter;
        undoStack[undoTop].prev_char = c;

    }
}

void undo(){

    if(undoTop >= 0){

        Action last = undoStack[undoTop];
        undoTop--;

        buffer[last.row][last.karakter] = last.prev_char;

        cursor_row = last.row;
        cursor_karakter = last.karakter;

    }
    else{
        printf("Undo stack kosong\n");
    }
}

void redo() {
    
}