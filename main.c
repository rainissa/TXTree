#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "text-edit.h"
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "open-save.h"

/* variabel global untuk clipboard */
char dokumen[MAX_BARIS][MAX_KARAKTER];
char clipboard[MAX_KARAKTER];
int cursor = 0;

/* sinkronisasi buffer text-edit ke dokumen clipboard */
void syncBufferToDokumen() {
    for(int i = 0; i < jumlahBaris; i++){
        strcpy(dokumen[i], buffer[i]);
    }
}

/* sinkronisasi dokumen clipboard ke buffer text-edit */
void syncDokumenToBuffer() {
    for(int i = 0; i < jumlahBaris; i++){
        strcpy(buffer[i], dokumen[i]);
    }
}

int main(){

    int pilihan;

    while(1){

        tampilkan();

        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();

        switch(pilihan){

            case 1:
                tambahBaris();
                break;

            case 2:
                hapusBaris();
                break;

            case 3:
                editBaris();
                break;

            case 4:
                sisipBaris();
                break;

            case 5:
                saveFile();
                break;

            case 6:
                openFile();
                break;

            case 7:
                printf("Keluar dari program...\n");
                exit(0);

            case 8:
                syncBufferToDokumen();
                copyLine();
                syncDokumenToBuffer();
                break;

            case 9:
                syncBufferToDokumen();
                cutLine();
                syncDokumenToBuffer();
                break;

            case 10:
                syncBufferToDokumen();
                pasteLine();
                syncDokumenToBuffer();
                break;

            case 11:
                undo();
                break;

            default:
                printf("Menu tidak valid!\n");
        }

        pauseScreen();
    }

    return 0;
}