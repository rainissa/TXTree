#include <string.h>
#include "cursor.h"
#include "text-edit.h"

// inisialisasi
int cursor_row = 0;
int cursor_col = 0;

// fungsi validasi & normalisasi cursor
void validateCursor() {
    if (jumlahBaris == 0) {
        cursor_row = 0;
        cursor_col = 0;
        return;
    }

    if (cursor_row < 0) cursor_row = 0;
    if (cursor_row >= jumlahBaris) cursor_row = jumlahBaris - 1;

    int len = strlen(buffer[cursor_row]);

    if (cursor_col < 0) cursor_col = 0;
    if (cursor_col > len) cursor_col = len;
}


void setCursor(int row, int col) {
    cursor_row = row;
    cursor_col = col;
    validateCursor();
}