#include <stdio.h>
#include <stdlib.h>

#include "text-edit.h"
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "open-save.h"

/* tampilan header */
void tampilkanHeader() {
    printf("=========================================\n");
    printf("         TxTree Text Editor\n");
    printf("=========================================\n");
}

/* menu */
void tampilkanMenu() {
    printf("\n========== MENU ==========\n");
    printf("1.  Tambah Baris\n");
    printf("2.  Hapus Baris\n");
    printf("3.  Edit Baris\n");
    printf("4.  Sisip Baris\n");
    printf("5.  Save File\n");
    printf("6.  Open File\n");
    printf("7.  Copy\n");
    printf("8.  Cut\n");
    printf("9.  Paste\n");
    printf("10. Undo\n");
    printf("11. Redo\n");
    printf("12. Set Cursor\n");
    printf("13. Keluar\n");
    printf("==========================\n");
}

void pauseScreen() {
    printf("\nTekan ENTER untuk lanjut...");
    getchar();
}

int main() {
    int pilihan;
    int pos;

    while (1) {
        system("cls");

        tampilkanHeader();

        printf("\n=== ISI DOKUMEN ===\n");
        tampilkan();

        tampilkanMenu();

        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {

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
                copyLine();
                printf(">> Copy berhasil\n");
                break;

            case 8:
                cutLine();
                printf(">> Cut berhasil\n");
                break;

            case 9:
                pasteLine();
                printf(">> Paste berhasil\n");
                break;

            case 10:
                undo();
                printf(">> Undo berhasil\n");
                break;

            case 11:
                redo();
                printf(">> Redo berhasil\n");
                break;

            case 12:
                printf("Masukkan posisi cursor: ");
                scanf("%d", &pos);
                getchar();
                setCursor(pos);
                break;

            case 13:
                printf("Keluar...\n");
                return 0;

            default:
                printf("Menu tidak valid!\n");
        }

        pauseScreen();
    }
}