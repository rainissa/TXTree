#ifndef CURSOR_H
#define CURSOR_H

// cursor baris & kolom
extern int cursor_row;
extern int cursor_col;

// validasi & sanitasi posisi cursor
// return 0 jika dokumen kosong, return 1 jika valid
int isCursorValid();

// set cursor ke posisi tertentu
void setCursor(int row, int col);

#endif