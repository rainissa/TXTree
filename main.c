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
    printf("2. Hapus Baris\n");
    printf("3. Edit Baris\n");
    printf("4. Sisip Baris\n");
    printf("5. Save File\n");
    printf("6. Open File\n");
    printf("7. Copy\n");
    printf("8. Cut\n");
    printf("9. Paste\n");
    printf("10. Undo\n");
    printf("11. Redo\n");
    printf("12. Set Cursor\n");
    printf("13. Keluar\n");
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

void validateCursor() {
    if (jumlahBaris == 0) {
        cursor_row = 0;
        cursor_col = 0;
        return;
    }

    if (cursor_row < 0) cursor_row = 0;
    if (cursor_row >= jumlahBaris) cursor_row = jumlahBaris - 1;

    int len = strlen(buffer[cursor_row]);

    if (cursor_col < 0) cursor_col = 0;
    if (cursor_col > len) cursor_col = len;
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

        printf("\nCursor di baris: %d, kolom: %d\n", cursor_row, cursor_col);

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
                break; 

            case 8:
                cutLine();
                break;

            case 9:
                pasteLine();
                break;

            case 10:
                undo();
                break;

            case 11:
                redo();
                break;

            case 12: {
                if (jumlahBaris == 0) {
                    printf("Dokumen masih kosong!\n");
                    break;
                }

                int pos, col;

                printf("Masukkan baris cursor: ");
                pos = inputInt();

                if (pos < 0 || pos >= jumlahBaris) {
                    printf("Posisi baris tidak valid!\n");
                    break;
                }

                printf("Masukkan kolom cursor: ");
                col = inputInt();

                int len = strlen(buffer[pos]);

                if (col < 0) col = 0;
                if (col > len) col = len;

                setCursor(pos, col);
                break;
            }

            case 13:
                printf("Keluar program...\n");
                return 0;

            default:
                printf("Menu tidak valid!\n");
        }

        validateCursor();

        pauseScreen();
    }
}