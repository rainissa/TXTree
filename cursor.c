#include <string.h>
#include "cursor.h"
#include "text-edit.h"

// inisialisasi
int cursor_row = 0;
int cursor_col = 0;

// validasi & sanitasi posisi cursor
// return 0 jika dokumen kosong, return 1 jika valid
int isCursorValid() {

    if (jumlahBaris == 0) {
        cursor_row = 0;
        cursor_col = 0;
        return 0;
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

void setCursor(int row, int col) {
    cursor_row = row;
    cursor_col = col;
    isCursorValid();
}