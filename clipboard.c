#include <stdio.h>
#include <string.h>
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "config.h"
#include "text-edit.h"

static char clipboard[MAX_KARAKTER];

void setClipboard(const char *text) {
    strncpy(clipboard, text, MAX_KARAKTER - 1);
    clipboard[MAX_KARAKTER - 1] = '\0';
}

char* getClipboard() {
    return clipboard;
}

int isClipboardEmpty() {
    return clipboard[0] == '\0';
}

int isValidCopyCut(int *col, int *len) {
    if (jumlahBaris == 0){
        printf("Dokumen kosong\n");
        return 0;
    }

    validateCursor();

    *len = strlen(buffer[cursor_row]);

    if (*len == 0){
        printf("Baris kosong\n");
        return 0;
    }

    *col = cursor_col;

    if (*col >= *len){
        printf("Tidak ada teks setelah cursor\n");
        return 0;
    }

    return 1;
}

void copyLine(){
    int col, len;

    if (!isValidCopyCut(&col, &len)) return;

    setClipboard(buffer[cursor_row] + col);

    printf("Copy berhasil: \"%s\"\n", getClipboard());
}

void cutLine(){
    int col, len;

    if (!isValidCopyCut(&col, &len)) return;

    pushSnapshot();
    clearRedo();

    setClipboard(buffer[cursor_row] + col);

    buffer[cursor_row][col] = '\0';
    cursor_col = col;

    printf("Cut berhasil\n");
}

void pasteLine(){
    if (jumlahBaris == 0){
        printf("Dokumen kosong\n");
        return;
    }

    if (isClipboardEmpty()){
        printf("Clipboard kosong\n");
        return;
    }

    validateCursor();

    int col = cursor_col;
    int len = strlen(buffer[cursor_row]);

    if (len >= MAX_KARAKTER - 1){
        printf("Baris sudah penuh\n");
        return;
    }

    char temp[MAX_KARAKTER];
    strcpy(temp, buffer[cursor_row] + col);

    char *clip = getClipboard();
    int clipLen = strlen(clip);
    int tempLen = strlen(temp);

    if (col + clipLen + tempLen >= MAX_KARAKTER){
        printf("Paste gagal: melebihi kapasitas baris\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    buffer[cursor_row][col] = '\0';

    int sisa = MAX_KARAKTER - strlen(buffer[cursor_row]) - 1;
    strncat(buffer[cursor_row], clip, sisa);

    sisa = MAX_KARAKTER - strlen(buffer[cursor_row]) - 1;
    strncat(buffer[cursor_row], temp, sisa);

    cursor_col = col + clipLen;

    printf("Paste berhasil\n");
}