#include <stdio.h>
#include <string.h>
#include "history.h"
#include "cursor.h"
#include "text-edit.h"

// Ambil variabel global dari file lain
extern char buffer[MAX_ROW][MAX_KARAKTER];
extern int jumlahBaris;
extern int cursor_row;
extern int cursor_col;

// Stack undo & redo
Snapshot undoStack[STACK_SIZE];
int undoTop = -1;

Snapshot redoStack[STACK_SIZE];
int redoTop = -1;

// ======================
// Clear redo
// ======================
void clearRedo() {
    redoTop = -1;
}

// ======================
// Push snapshot sebelum edit
// ======================
void pushSnapshot() {
    // setiap edit baru, redo harus dihapus
    clearRedo();

    // shift stack jika penuh (rolling history)
    if (undoTop == STACK_SIZE - 1) {
        for (int i = 0; i < STACK_SIZE - 1; i++) {
            undoStack[i] = undoStack[i + 1];
        }
        undoTop--;
    }

    undoTop++;

    undoStack[undoTop].jumlahBaris = jumlahBaris;
    undoStack[undoTop].cursor_row = cursor_row;
    undoStack[undoTop].cursor_col = cursor_col;

    for (int i = 0; i < jumlahBaris; i++) {
        strcpy(undoStack[undoTop].buffer[i], buffer[i]);
    }
}

// ======================
// Undo
// ======================
void undo() {
    if (undoTop < 0) {
        printf("\n[!] Tidak ada aksi untuk di-undo.\n");
        return;
    }

    // Simpan kondisi saat ini ke redo
    if (redoTop == STACK_SIZE - 1) {
        for (int i = 0; i < STACK_SIZE - 1; i++) {
            redoStack[i] = redoStack[i + 1];
        }
        redoTop--;
    }
    redoTop++;

    redoStack[redoTop].jumlahBaris = jumlahBaris;
    redoStack[redoTop].cursor_row = cursor_row;
    redoStack[redoTop].cursor_col = cursor_col;
    for (int i = 0; i < jumlahBaris; i++) {
        strcpy(redoStack[redoTop].buffer[i], buffer[i]);
    }

    // Restore dari undo
    jumlahBaris = undoStack[undoTop].jumlahBaris;
    cursor_row = undoStack[undoTop].cursor_row;
    cursor_col = undoStack[undoTop].cursor_col;

    for (int i = 0; i < jumlahBaris; i++) {
        strcpy(buffer[i], undoStack[undoTop].buffer[i]);
    }
    // Bersihkan sisa baris
    for (int i = jumlahBaris; i < MAX_ROW; i++) {
        buffer[i][0] = '\0';
    }

    // Validasi cursor
    if (cursor_row >= jumlahBaris && jumlahBaris > 0) cursor_row = jumlahBaris - 1;
    if (cursor_row < 0) cursor_row = 0;
    if (cursor_col < 0) cursor_col = 0;
    int len = (jumlahBaris > 0) ? strlen(buffer[cursor_row]) : 0;
    if (cursor_col > len) cursor_col = len;

    undoTop--;

    printf("\n[v] Undo berhasil.\n");
}

// ======================
// Redo
// ======================
void redo() {
    if (redoTop < 0) {
        printf("\n[!] Tidak ada aksi untuk di-redo.\n");
        return;
    }

    // Simpan kondisi saat ini ke undo tanpa clear redo
    if (undoTop == STACK_SIZE - 1) {
        for (int i = 0; i < STACK_SIZE - 1; i++) {
            undoStack[i] = undoStack[i + 1];
        }
        undoTop--;
    }
    undoTop++;

    undoStack[undoTop].jumlahBaris = jumlahBaris;
    undoStack[undoTop].cursor_row = cursor_row;
    undoStack[undoTop].cursor_col = cursor_col;
    for (int i = 0; i < jumlahBaris; i++) {
        strcpy(undoStack[undoTop].buffer[i], buffer[i]);
    }

    // Restore dari redo
    jumlahBaris = redoStack[redoTop].jumlahBaris;
    cursor_row = redoStack[redoTop].cursor_row;
    cursor_col = redoStack[redoTop].cursor_col;

    for (int i = 0; i < jumlahBaris; i++) {
        strcpy(buffer[i], redoStack[redoTop].buffer[i]);
    }
    // Bersihkan sisa baris
    for (int i = jumlahBaris; i < MAX_ROW; i++) {
        buffer[i][0] = '\0';
    }

    // Validasi cursor
    if (cursor_row >= jumlahBaris && jumlahBaris > 0) cursor_row = jumlahBaris - 1;
    if (cursor_row < 0) cursor_row = 0;
    if (cursor_col < 0) cursor_col = 0;
    int len = (jumlahBaris > 0) ? strlen(buffer[cursor_row]) : 0;
    if (cursor_col > len) cursor_col = len;

    redoTop--;

    printf("\n[v] Redo berhasil.\n");
}