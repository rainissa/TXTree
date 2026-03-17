#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "text-edit.h"
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "open-save.h"

/* variabel global untuk clipboard */
char buffer[MAX_ROW][MAX_COL];
char clipboard[MAX_COL];
int cursor = 0;

/* sinkronisasi buffer text-edit ke dokumen clipboard */
void syncBufferToDokumen() {
    for(int i = 0; i < jumlahBaris; i++){
        strcpy(buffer[i], buffer[i]);
    }
}

/* sinkronisasi dokumen clipboard ke buffer text-edit */
void syncDokumenToBuffer() {
    for(int i = 0; i < jumlahBaris; i++){
        strcpy(buffer[i],buffer[i]);
    }
}

/* tampilan header aplikasi */
void tampilkanHeader() {
    printf("=========================================\n");
    printf("         TxTree Text Editor 🌳\n");
    printf("=========================================\n");
}

/* tampilan menu */
void tampilkanMenu() {
    printf("\n========== MENU ==========\n");
    printf("1.  Tambah Baris\n");
    printf("2.  Hapus Baris\n");
    printf("3.  Edit Baris\n");
    printf("4.  Sisip Baris\n");
    printf("5.  Save File\n");
    printf("6.  Open File\n");
    printf("7.  Keluar\n");
    printf("8.  Copy\n");
    printf("9.  Cut\n");
    printf("10. Paste\n");
    printf("11. Undo\n");
    printf("12. Redo\n");
    printf("13. Set Cursor\n");
    printf("==========================\n");
}

/* jeda layar */
void pauseScreen() {
    printf("\nTekan ENTER untuk lanjut...");
    getchar();
}

int main(){

    int pilihan;

    while(1){

        system("cls"); // Windows (kalau Linux ganti "clear")
        tampilkanHeader();

        printf("\n=== ISI DOKUMEN ===\n");
        tampilkan();

        tampilkanMenu();

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
                printf(">> Copy berhasil\n");
                break;

            case 9:
                syncBufferToDokumen();
                cutLine();
                syncDokumenToBuffer();
                printf(">> Cut berhasil\n");
                break;

            case 10:
                syncBufferToDokumen();
                pasteLine();
                syncDokumenToBuffer();
                printf(">> Paste berhasil\n");
                break;

            case 11:
                undo();
                printf(">> Undo berhasil\n");
                break;

            case 12:
                redo();
                printf(">> Redo berhasil\n");
                break;

            case 13:
                printf("Masukkan posisi cursor: ");
                scanf("%d", &cursor);
                getchar();
                setCursor(cursor);
                printf(">> Cursor dipindahkan ke %d\n", cursor);
                break;

            default:
                printf("Menu tidak valid!\n");
        }

        pauseScreen();
    }

    return 0;
}