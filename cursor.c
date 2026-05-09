#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cursor.h"
#include "config.h"

extern int jumlahBaris;
extern char buffer[MAX_ROW][MAX_KARAKTER];

CursorNode *cursor_head = NULL;

void initCursor(void) {
    freeCursorList();

    CursorNode *node = (CursorNode*) malloc(sizeof(CursorNode));
    if (!node) {
        fprintf(stderr, "initCursor: gagal alokasi memori\n");
        return;
    }
    node->col  = 0;
    node->next = NULL;
    cursor_head = node;
}

void validateCursor(void) {
    if (!cursor_head) {
        initCursor();
        return;
    }

    if (jumlahBaris == 0) {
        cursor_head->col = 0;
        return;
    }

    int len = strlen(buffer[0]);
    if (cursor_head->col < 0)   cursor_head->col = 0;
    if (cursor_head->col > len) cursor_head->col = len;
}

void setCursor(int col) {
    if (!cursor_head) initCursor();
    cursor_head->col = col;
    validateCursor();
}

void pushCursor(int col) {
    CursorNode *node = (CursorNode*) malloc(sizeof(CursorNode));
    if (!node) {
        fprintf(stderr, "pushCursor: gagal alokasi memori\n");
        return;
    }
    node->col  = col;
    node->next = cursor_head;
    cursor_head = node;
    validateCursor();
}

int popCursor(void) {
    if (!cursor_head || !cursor_head->next) {
        printf("Tidak ada riwayat kolom cursor sebelumnya\n");
        return 0;
    }

    CursorNode *hapus = cursor_head;
    cursor_head = cursor_head->next;
    free(hapus);

    printf("Cursor kembali ke kolom %d\n", cursor_head->col);
    return 1;
}

void printCursorList(void) {
    CursorNode *temp = cursor_head;
    int i = 0;
    printf("=== Linked List Cursor ===\n");
    while (temp) {
        printf("  [%d] col=%d%s\n", i, temp->col, i == 0 ? "  <- AKTIF" : "");
        temp = temp->next;
        i++;
    }
    if (i == 0) printf("  (kosong)\n");
    printf("==========================\n");
}

void freeCursorList(void) {
    while (cursor_head) {
        CursorNode *hapus = cursor_head;
        cursor_head = cursor_head->next;
        free(hapus);
    }
}