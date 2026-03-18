#include <stdio.h>
#include <string.h>
#include "clipboard.h"
#include "cursor.h"
#include "history.h"

char clipboard[MAX_CLIPBOARD_ROW][MAX_KARAKTER];
int jumlahClipboard = 0;

/* mengatur cursor */
void setCursor(int row, int col) {
    if (row >= 0 && row < jumlahBaris) {
        cursor_row = row;
        int len = strlen(buffer[cursor_row]);
        if (col < 0) col = 0;
        if (col > len) col = len;
        cursor_col = col;
        printf("Cursor di baris %d kolom %d\n", cursor_row, cursor_col);
    } else {
        printf("Posisi cursor tidak valid\n");
    }
}

/* COPY BLOK BARIS */
void copyBlock(int start, int end){
    if (start < 0 || end >= jumlahBaris || start > end){
        printf("Range tidak valid\n");

        return;
    }

    jumlahClipboard = 0;

    for (int i = start; i <= end; i++){
        if (jumlahClipboard >= MAX_CLIPBOARD_ROW){
            printf("Clipboard penuh\n");

            break;
        }

        strcpy(clipboard[jumlahClipboard], buffer[i]);
        jumlahClipboard++;
    }

    printf("Blok baris berhasil dicopy\n");
}

/* CUT BLOK BARIS */
void cutBlock(int start, int end){
    if (!isCursorValid()) {
        printf("Cursor tidak valid\n");
        return;
    }

    if (start < 0 || end >= jumlahBaris || start > end){
        printf("Range tidak valid\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    copyBlock(start, end);

    int jumlahHapus = end - start + 1;

    for (int i = start; i < jumlahBaris - jumlahHapus; i++){
        strcpy(buffer[i], buffer[i + jumlahHapus]);
    }

    jumlahBaris -= jumlahHapus;

      // update cursor
    if (cursor_row >= jumlahBaris) cursor_row = jumlahBaris - 1;
    if (cursor_row < 0) cursor_row = 0;
    if (cursor_col > strlen(buffer[cursor_row])) cursor_col = strlen(buffer[cursor_row]);

    printf("Blok baris dipotong\n");
}

/* PASTE BLOK */
void pasteBlock(){
    if (jumlahClipboard == 0){
        printf("Clipboard kosong\n");
        return;
    }

        if (!isCursorValid()) {           
        printf("Cursor tidak valid\n");
        return;
    }

    if (jumlahBaris + jumlahClipboard >= MAX_ROW){
        printf("Dokumen penuh\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    // simpan sisa kanan baris cursor
    char temp[MAX_KARAKTER];
    strcpy(temp, buffer[cursor_row] + cursor_col);
    buffer[cursor_row][cursor_col] = '\0';

    // geser baris di bawah cursor untuk memberi ruang
    for (int i = jumlahBaris - 1; i > cursor_row; i--) {
        strcpy(buffer[i + jumlahClipboard], buffer[i]);
    }

    // sisipkan baris clipboard
    for (int i = 0; i < jumlahClipboard; i++) {
        strcpy(buffer[cursor_row + 1 + i], clipboard[i]);
    }

    // gabungkan sisa kanan ke baris terakhir dari clipboard
    strcat(buffer[cursor_row + jumlahClipboard], temp);

    jumlahBaris += jumlahClipboard;

    // update cursor di akhir blok yang ditempel
    cursor_row = cursor_row + jumlahClipboard;
    cursor_col = 0;

    printf("Clipboard berhasil ditempel\n");
}