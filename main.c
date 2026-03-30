#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text-edit.h"
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "open-save.h"

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

int main() {
    int pilihan;
    int pos;

    // ✅ INISIALISASI WAJIB
    clipboard[0] = '\0';

    while (1) {
        system("cls");

        tampilkanHeader();

        printf("\n=== ISI DOKUMEN ===\n");
        tampilkan();

        printf("\nCursor di baris: %d, kolom: %d\n", cursor_row, cursor_col);

        tampilkanMenu();

        printf("Pilih menu: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid!\n");
            while(getchar() != '\n');
            pauseScreen();
            continue;
        }
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
                copyLine();   // ✅ tidak perlu cek lagi
                break;

            case 8:
                cutLine();    // ✅ tidak perlu cek lagi
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

            case 12:
                if (jumlahBaris == 0){
                    printf("Dokumen masih kosong!\n");
                    break;
                }

                printf("Masukkan baris cursor: ");
                if (scanf("%d", &pos) != 1){
                    printf("Input tidak valid!\n");
                    while(getchar() != '\n');
                    break;
                }
                getchar();

                if (pos >= 0 && pos < jumlahBaris){
                    int col;

                    printf("Masukkan kolom cursor: ");
                    if (scanf("%d", &col) != 1){
                        printf("Input tidak valid!\n");
                        while(getchar() != '\n');
                        break;
                    }
                    getchar();

                    int len = strlen(buffer[pos]);

                    if (col < 0) col = 0;
                    if (col > len) col = len;

                    setCursor(pos, col);
                }
                else {
                    printf("Posisi tidak valid!\n");
                } 
                break;

            case 13:
                return 0;

            default:
                printf("Menu tidak valid!\n");
        }

        pauseScreen();
    }
}