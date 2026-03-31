#include <stdio.h>
#include <stdlib.h>

#include "text-edit.h"
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "open-save.h"
#include "config.h"

void tampilkanHeader() {
    printf("=========================================\n");
    printf("         TxTree Text Editor\n");
    printf("=========================================\n");
}

void tampilkanMenu() {
    printf("\n========== MENU ==========\n");
    printf("1. Tambah Baris\n");
    printf("2. Hapus Baris\n");
    printf("3. Edit Baris\n");
    printf("4. Sisip Baris\n");
    printf("5. Save File\n");
    printf("6. Open File\n");
    printf("7. Copy (cursor)\n");
    printf("8. Cut (cursor)\n");
    printf("9. Paste\n");
    printf("10. Undo\n");
    printf("11. Redo\n");
    printf("12. Set Cursor\n");
    printf("13. Keluar\n");
    printf("==========================\n");
}

int main() {
    int pilihan;
    int pos;

    while (1) {
        system("cls");

        tampilkanHeader();

        printf("\n=== ISI DOKUMEN ===\n");
        tampilkan();  // nanti diperbaiki supaya ada cursor

        printf("\nCursor di baris: %d\n", cursor_row);

        tampilkanMenu();

        printf("Pilih menu: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n");
            while(getchar() != '\n');
            continue;
        }
        getchar();

        switch (pilihan) {

            case 1: tambahBaris(); break;
            case 2: hapusBaris(); break;
            case 3: editBaris(); break;
            case 4: sisipBaris(); break;
            case 5: saveFile(); break;
            case 6: openFile(); break;

            case 7:
                copyLine(cursor_row);
                printf(">> Copy berhasil\n");
                break;

            case 8:
                cutLine(cursor_row);
                printf(">> Cut berhasil\n");
                break;

            case 9:
                pasteLine(cursor_row);
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

                if (pos >= 0 && pos < jumlahBaris)
                    setCursor(pos, 0);
                else
                    printf("Posisi tidak valid!\n");
                break;

            case 13:
                return 0;

            default:
                printf("Menu tidak valid!\n");
        }

        pauseScreen();
    }
}