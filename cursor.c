#include "cursor.h"
#include "text-edit.h"
#include <string.h>
#include "config.h"

// inisialisasi
int cursor_row = 0;
int cursor_col = 0;

// validasi cursor baris
int isCursorValid() {
    return (cursor_row >= 0 && cursor_row < jumlahBaris);
}

// ======================
// NAVIGASI BARIS
// ======================

void moveUp() {
    if (cursor_row > 0) {
        cursor_row--;

        // biar kolom gak keluar dari panjang string
        if (cursor_col > strlen(buffer[cursor_row])) {
            cursor_col = strlen(buffer[cursor_row]);
        }
    }
}

void moveDown() {
    if (cursor_row < jumlahBaris - 1) {
        cursor_row++;

        if (cursor_col > strlen(buffer[cursor_row])) {
            cursor_col = strlen(buffer[cursor_row]);
        }
    }
}

// ======================
// NAVIGASI KOLOM
// ======================

void moveLeft() {
    if (cursor_col > 0) {
        cursor_col--;
    }
}

void moveRight() {
    if (cursor_col < strlen(buffer[cursor_row])) {
        cursor_col++;
    }
}

void setCursor(int row, int col) {
    if (row >= 0 && row < jumlahBaris) {
        cursor_row = row;

        int panjang = strlen(buffer[cursor_row]);
        if (col >= 0 && col <= panjang)
            cursor_col = col;
        else
            cursor_col = panjang;
    }
}