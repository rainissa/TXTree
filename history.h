#ifndef HISTORY_H
#define HISTORY_H

#include "text-edit.h" // Supaya dapet MAX_KARAKTER

#define STACK_SIZE 100

typedef struct{
    int row;
    int karakter;
    char prev_char;
} Action;

void pushUndo(int row, int karakter, char c);
void undo();
void redo();
void clearRedo();

#endif