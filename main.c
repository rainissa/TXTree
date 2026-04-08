#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text-edit.h"
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "open-save.h"
#include "config.h"

#define CLEAR() system("cls")

void tampilkanHeader() {
    printf("=========================================\n");
    printf("         TxTree Text Editor\n");
    printf("=========================================\n");
}

void tampilkanMenu() {
    printf("\n========== MENU ==========\n");
    printf("1. Tambah Baris\n");
    printf("2. Edit Baris\n");
    printf("3. Sisip Baris\n");
    printf("4. Save File\n");
    printf("5. Open File\n");
    printf("6. Copy\n");
    printf("7. Cut\n");
    printf("8. Paste\n");
    printf("9. Undo\n");
    printf("10. Redo\n");
    printf("11. Set Cursor\n");
    printf("12. Keluar\n");
    printf("==========================\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int inputInt() {
    int value;
    while (1) {
        if (scanf("%d", &value) == 1) {
            clearInputBuffer();
            return value;
        }
        printf("Input tidak valid! Masukkan angka: ");
        clearInputBuffer();
    }
}

int main() {
    int pilihan;

    clipboard[0] = '\0';

    while (1) {
        CLEAR();

        tampilkanHeader();

        printf("\n=== ISI DOKUMEN ===\n");
        tampilkan();

        validateCursor();

        printf("\nCursor di baris: %d, kolom: %d\n", cursor_row + 1, cursor_col + 1);

        tampilkanMenu();

        printf("Pilih menu: ");
        pilihan = inputInt();

        CLEAR();
        tampilkanHeader();

        switch (pilihan) {

            case 1:
                tambahBaris();
                break;

            case 2:
                editBaris();
                break;

            case 3:
                sisipBaris();
                break;

            case 4:
                saveFile();
                break;

            case 5:
                openFile();
                break;

            case 6:
                copyLine();
                break; 

            case 7:
                cutLine();
                break;

            case 8:
                pasteLine();
                break;

            case 9:
                undo();
                break;

            case 10:
                redo();
                break;

            case 11: {
                if (jumlahBaris == 0) {
                    printf("Dokumen masih kosong!\n");
                    break;
                }

                int pos, col;

                printf("Masukkan baris cursor (1-%d): ", jumlahBaris);
                pos = inputInt() - 1;

                if (pos < 0 || pos >= jumlahBaris) {
                    printf("Posisi baris tidak valid!\n");
                    break;
                }

                printf("Masukkan kolom cursor (1-%d): ", (int)strlen(buffer[pos]) + 1);
                col = inputInt() - 1;

                int panjang = strlen(buffer[pos]);
                if (col < 0 || col > panjang) {
                    printf("Posisi kolom tidak valid!\n");
                    break;
                }

                setCursor(pos, col);
                break;
            }

            case 12:
                printf("Keluar program...\n");
                return 0;

            default:
                printf("Menu tidak valid!\n");
        }

        validateCursor();

        pauseScreen();
    }
}