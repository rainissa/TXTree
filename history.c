#include <stdio.h>
#include "cursor.h"
#include "history.h"
#include "text-edit.h"

// Variabel buffer global dari text-edit.c
extern char buffer[MAX_ROW][MAX_COL];
extern int jumlahBaris;

Action undoStack[STACK_SIZE];
int undoTop = -1;

Action redoStack[STACK_SIZE];
int redoTop = -1;

void pushUndo(int row, int karakter, char c){

    if(top < STACK_SIZE-1){

        top++;
        undoStack[top].row = row;
        undoStack[top].karakter = karakter;
        undoStack[top].prev_char = c;

    }
}

void undo(){

    if(top >= 0){

        Action last = undoStack[top];
        top--;

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