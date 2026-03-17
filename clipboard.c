#include <stdio.h>
#include <string.h>
#include "clipboard.h"

/* mengatur cursor */
void setCursor(int posisi){
    if (posisi >= 0 && posisi < jumlahBaris){
        cursor = posisi;
        printf("Cursor di baris %d\n", cursor);
    }
    else{
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
    if (start < 0 || end >= jumlahBaris || start > end){
        printf("Range tidak valid\n");
        return;
    }

    copyBlock(start, end);

    int jumlahHapus = end - start + 1;

    for (int i = start; i < jumlahBaris - jumlahHapus; i++){
        strcpy(buffer[i], buffer[i + jumlahHapus]);
    }

    jumlahBaris -= jumlahHapus;

    printf("Blok baris dipotong\n");
}

/* PASTE BLOK */
void pasteBlock(){
    if (jumlahClipboard == 0){
        printf("Clipboard kosong\n");
        return;
    }

    if (jumlahBaris + jumlahClipboard >= MAX_ROW){
        printf("Dokumen penuh\n");
        return;
    }

    for (int i = jumlahBaris - 1; i > cursor; i--){
        strcpy(buffer[i + jumlahClipboard], buffer[i]);
    }

    for (int i = 0; i < jumlahClipboard; i++){
        strcpy(buffer[cursor + 1 + i], clipboard[i]);
    }

    jumlahBaris += jumlahClipboard;

    printf("Clipboard berhasil ditempel\n");
}