#include <stdio.h>
#include "undo.h"
#include "cursor.h"

extern char text[MAX_ROW][MAX_COL];
Action undoStack[STACK_SIZE];
int top = -1;

void pushUndo(int row, int col, char c){

    if(top < STACK_SIZE-1){

        top++;
        undoStack[top].row = row;
        undoStack[top].col = col;
        undoStack[top].prev_char = c;

    }
}

void undo(){

    if(top >= 0){

        Action last = undoStack[top];
        top--;

        text[last.row][last.col] = last.prev_char;

        cursor_row = last.row;
        cursor_col = last.col;

    }
    else{
        printf("Undo stack kosong\n");
    }
}