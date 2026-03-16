#include "cursor.h"

int cursor_row = 0;
int cursor_col = 0;

void moveLeft() {
    if (cursor_col > 0)
        cursor_col--;
}

void moveRight() {
    if (cursor_col < MAX_COL - 1)
        cursor_col++;
}

void moveUp() {
    if (cursor_row > 0)
        cursor_row--;
}

void moveDown() {
    if (cursor_row < MAX_ROW - 1)
        cursor_row++;
}