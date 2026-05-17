#include <stdio.h>
#include <stdlib.h>

#include "text-edit.h"
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "open-save.h"

#define CLEAR() system("cls")

extern List L;
extern int jumlahBaris;

void tampilkanHeader(void)
{
    printf("=========================================\n");
    printf("         TxTree Text Editor\n");
    printf("=========================================\n");
}

void tampilkanMenu(void)
{
    printf("\n========== MENU ==========\n");
    printf("1. Tambah Baris\n");
    printf("2. Edit Baris\n");
    printf("3. Save File\n");
    printf("4. Open File\n");
    printf("5. Copy Baris\n");
    printf("6. Cut Baris\n");
    printf("7. Paste Baris\n");
    printf("8. Undo\n");
    printf("9. Redo\n");
    printf("10. Keluar\n");
    printf("==========================\n");
}

void clearInputBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int inputInt(void)
{
    int value;

    while (1)
    {
        if (scanf("%d", &value) == 1)
        {
            clearInputBuffer();
            return value;
        }

        printf("Input tidak valid! Masukkan angka: ");
        clearInputBuffer();
    }
}

int main(void)
{
    int pilihan;

    CreateList(&L);

    initCursor();

    setClipboard("");

    while (1)
    {
        CLEAR();

        tampilkanHeader();

        printf("\n=== ISI DOKUMEN ===\n");

        tampilkan();

        validateCursor();

        if (getCursor() != NULL)
        {
            printf("\nCursor di baris: %d\n", getCursorIndex() + 1);
        }
        else
        {
            printf("\nCursor belum aktif\n");
        }

        tampilkanMenu();

        printf("Pilih menu: ");

        pilihan = inputInt();

        CLEAR();

        tampilkanHeader();

        switch (pilihan)
        {
            case 1:
                tambahBaris();
                break;

            case 2:
                editBaris();
                break;

            case 3:
                saveFile();
                break;

            case 4:
                openFile();
                break;

            case 5:
                copyLine();
                break;

            case 6:
                cutLine();
                break;

            case 7:
                pasteLine();
                break;

            case 8:
                undo();
                break;

            case 9:
                redo();
                break;

            case 10:
                printf("Keluar program...\n");
                clearHistory();
                return 0;

            default:
                printf("Menu tidak valid!\n");
                break;
        }

        validateCursor();

        pauseScreen();
    }

    return 0;
}