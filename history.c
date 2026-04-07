#include <stdio.h>
#include <string.h>
#include "history.h"
#include "cursor.h"
#include "text-edit.h"
#include "config.h"

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
// Helper: simpan state saat ini ke stack
// ======================
static void saveToStack(Snapshot *stack, int *top) {
    // shift rolling jika stack penuh
    if (*top == STACK_SIZE - 1) {
        for (int i = 0; i < STACK_SIZE - 1; i++) {
            stack[i] = stack[i + 1];
        }
        (*top)--;
    }

    (*top)++;
    stack[*top].jumlahBaris = jumlahBaris;
    stack[*top].cursor_row  = cursor_row;
    stack[*top].cursor_col  = cursor_col;

    for (int i = 0; i < MAX_ROW; i++) {
        if (i < jumlahBaris)
            strcpy(stack[*top].buffer[i], buffer[i]);
        else
            stack[*top].buffer[i][0] = '\0';
    }
}

// ======================
// Helper: restore snapshot ke buffer aktif
// ======================
static void restoreSnapshot(Snapshot *snap) {
    jumlahBaris = snap->jumlahBaris;
    cursor_row  = snap->cursor_row;
    cursor_col  = snap->cursor_col;

    for (int i = 0; i < jumlahBaris; i++) {
        strcpy(buffer[i], snap->buffer[i]);
    }

    // bersihkan sisa baris
    for (int i = jumlahBaris; i < MAX_ROW; i++) {
        buffer[i][0] = '\0';
    }

    isCursorValid();
}

// ======================
// Push snapshot sebelum edit
// ======================
void pushSnapshot() {
    saveToStack(undoStack, &undoTop);
}

// ======================
// Undo
// ======================
void undo() {
    if (undoTop < 0) {
        printf("\n[!] Tidak ada aksi untuk di-undo.\n");
        return;
    }

    saveToStack(redoStack, &redoTop);
    restoreSnapshot(&undoStack[undoTop]);
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

    saveToStack(undoStack, &undoTop);
    restoreSnapshot(&redoStack[redoTop]);
    redoTop--;

    printf("\n[v] Redo berhasil.\n");
}