#ifndef HISTORY_H
#define HISTORY_H

#include "config.h"

typedef struct {
    char buffer[MAX_ROW][MAX_KARAKTER];
    int jumlahBaris;
    int cursor_row;
    int cursor_col;
} Snapshot;

void pushSnapshot(); // menyimpan kondisi buffer & kursor ke stack undo
void undo(); // mengembalikan buffer & kursor ke snapshot sebelumnya
void redo(); // mengembalikan buffer & kursor ke snapshot setelah undo
void clearRedo(); // menghapus semua redo stack

#endif