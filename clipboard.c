#include <stdio.h>
#include <string.h>
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "config.h"
#include "text-edit.h"

char clipboard[MAX_KARAKTER];

void copyLine(){
    if (jumlahBaris == 0){
        printf("Dokumen kosong\n");
        return;
    }

    validateCursor();

    int len = strlen(buffer[cursor_row]);

    if (len == 0){
        printf("Baris kosong, tidak ada yang bisa dicopy\n");
        return;
    }

    int col = cursor_col;

    if (col >= len){
        printf("Tidak ada teks setelah cursor untuk dicopy\n");
        return;
    }

    strncpy(clipboard, buffer[cursor_row] + col, MAX_KARAKTER - 1);
    clipboard[MAX_KARAKTER - 1] = '\0';

    printf("Copy berhasil: \"%s\"\n", clipboard);
}

void cutLine(){
    if (jumlahBaris == 0){
        printf("Dokumen kosong\n");
        return;
    }

    validateCursor();

    int len = strlen(buffer[cursor_row]);

    if (len == 0){
        printf("Baris kosong, tidak ada yang bisa dicut\n");
        return;
    }

    int col = cursor_col;

    if (col >= len){
        printf("Tidak ada teks setelah cursor untuk dicut\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    strncpy(clipboard, buffer[cursor_row] + col, MAX_KARAKTER - 1);
    clipboard[MAX_KARAKTER - 1] = '\0';

    buffer[cursor_row][col] = '\0';

    cursor_col = col;

    printf("Cut berhasil\n");
}

void pasteLine(){
    if (clipboard[0] == '\0'){
        printf("Clipboard kosong\n");
        return;
    }

    validateCursor();

    int len = strlen(buffer[cursor_row]);
    int col = cursor_col;

    if (len >= MAX_KARAKTER - 1){
        printf("Baris sudah penuh\n");
        return;
    }

    char temp[MAX_KARAKTER];

    strncpy(temp, buffer[cursor_row] + col, MAX_KARAKTER - 1);
    temp[MAX_KARAKTER - 1] = '\0';

    int total = len + strlen(clipboard); // pakai len biar efisien
    if (total >= MAX_KARAKTER){
        printf("Paste gagal: melebihi kapasitas baris\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    buffer[cursor_row][col] = '\0';

    int sisa = MAX_KARAKTER - strlen(buffer[cursor_row]) - 1;
    strncat(buffer[cursor_row], clipboard, sisa);

    sisa = MAX_KARAKTER - strlen(buffer[cursor_row]) - 1;
    strncat(buffer[cursor_row], temp, sisa);

    cursor_col = col + strlen(clipboard);

    printf("Paste berhasil\n");
}