#ifndef CURSOR_H
#define CURSOR_H

// cursor baris & kolom
extern int cursor_row;
extern int cursor_col;

void validateCursor();

// set cursor ke posisi tertentu
void setCursor(int row, int col);

#endif