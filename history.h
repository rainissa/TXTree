#ifndef HISTORY_H
#define HISTORY_H

#include "text-edit.h" // Supaya dapet MAX_KARAKTER

#define STACK_SIZE 100

// Enumerasi untuk membedakan tipe aksi
typedef enum { EDIT, TAMBAH, HAPUS } ActionType;

typedef struct {
    int row;                      // Posisi baris di Array 2D
    char dataLama[MAX_KARAKTER];  // Teks lama sebelum diubah
    ActionType tipe;              // Jenis aksi yang dilakukan
} Action;

// Fungsi utama History
void pushUndo(int row, char *teks, ActionType tipe);
void undo();
void redo();
void clearRedo();

#endif