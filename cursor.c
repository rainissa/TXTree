#include "cursor.h"
#include "text-edit.h"
#include <string.h>

// inisialisasi
int cursor_row = 0;
int cursor_col = 0;

// validasi cursor baris
int isCursorValid() {

     if (jumlahBaris == 0) {
        cursor_row = 0;
        cursor_col = 0;
        return 1;
    }

    // validasi baris
    if (cursor_row < 0)
        cursor_row = 0;

    if (cursor_row >= jumlahBaris)
        cursor_row = jumlahBaris - 1;

    // validasi kolom
    int panjang = strlen(buffer[cursor_row]);

    if (cursor_col < 0)
        cursor_col = 0;

    if (cursor_col > panjang)
        cursor_col = panjang;

    return 1; 
}

// ======================
// NAVIGASI BARIS
// ======================

void moveUp() {
    cursor_row--;
    isCursorValid();
}

void moveDown() {
    cursor_row++;
    isCursorValid();
}

// ======================
// NAVIGASI KOLOM
// ======================

void moveLeft() {
    cursor_col--;
    isCursorValid();
}

void moveRight() {
    cursor_col++;
    isCursorValid();
}

void setCursor(int row, int col) {
    cursor_row = row;
    cursor_col = col;
    isCursorValid();
}