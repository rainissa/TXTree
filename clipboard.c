#include <stdio.h>
#include <string.h>
#include "clipboard.h"
#include "cursor.h"
#include "history.h"

char clipboard[MAX_KARAKTER];

void copyLine(){
    if (jumlahBaris == 0){
        printf("Dokumen kosong\n");
        return;
    }

    if (!isCursorValid()){
        printf("Cursor tidak valid\n");
        return;
    }

    int len = strlen(buffer[cursor_row]);

    int col = cursor_col;
    if (col > len) col = len;

    strncpy(clipboard, buffer[cursor_row] + col, MAX_KARAKTER - 1);
    clipboard[MAX_KARAKTER - 1] = '\0';

    printf("Copy berhasil\n");
}

void cutLine(){
    if (jumlahBaris == 0){
        printf("Dokumen kosong\n");
        return;
    }

    if (!isCursorValid()){
        printf("Cursor tidak valid\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    int len = strlen(buffer[cursor_row]);

    int col = cursor_col;
    if (col > len) col = len;

    strncpy(clipboard, buffer[cursor_row] + col, MAX_KARAKTER - 1);
    clipboard[MAX_KARAKTER - 1] = '\0';

    buffer[cursor_row][col] = '\0';

    printf("Cut berhasil\n");
}

void pasteLine(){
    if (clipboard[0] == '\0'){
        printf("Clipboard kosong\n");
        return;
    }

    if (!isCursorValid()){
        printf("Cursor tidak valid\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    char temp[MAX_KARAKTER];

    int len = strlen(buffer[cursor_row]);

    int col = cursor_col;
    if (col > len) col = len;

    strncpy(temp, buffer[cursor_row] + col, MAX_KARAKTER - 1);
    temp[MAX_KARAKTER - 1] = '\0';

    int kiri = col;
    int total = kiri + strlen(clipboard) + strlen(temp) + 1;

    if (total > MAX_KARAKTER){
        printf("Paste gagal: melebihi kapasitas baris\n");
        return;
    }

    buffer[cursor_row][col] = '\0';

    int sisa = MAX_KARAKTER - strlen(buffer[cursor_row]) - 1;
    strncat(buffer[cursor_row], clipboard, sisa);

    sisa = MAX_KARAKTER - strlen(buffer[cursor_row]) - 1;
    strncat(buffer[cursor_row], temp, sisa);

    cursor_col = col + strlen(clipboard);

    printf("Paste berhasil\n");
}