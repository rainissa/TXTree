#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "text-edit.h"
#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "open-save.h"

#define CLEAR() system("cls")

extern List L;
extern int jumlahBaris;
extern int isModified;

void tampilkanHeader(void)
{
    printf("=========================================\n");
    printf("             TxTree Text Editor          \n"); 
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
    printf("8. Pindah Cursor\n");
    printf("9. Undo\n");
    printf("10. Redo\n");
    printf("11. Keluar\n");
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
        printf("[!] Input tidak valid! Masukkan angka yang benar: ");
        clearInputBuffer();
    }
}

int konfirmasiKeluar(void)
{
    char jawab;
    while (1)
    {
        printf("\nMasih ada perubahan yang belum disimpan.\n");
        printf("Yakin ingin keluar? (y/n): ");

        scanf(" %c", &jawab);
        clearInputBuffer();

        jawab = (char)tolower((unsigned char)jawab);

        if (jawab == 'y') return 1;
        if (jawab == 'n') return 0;

        printf("[!] Pilihan tidak valid! Gunakan 'y' atau 'n'.\n");
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

        validateCursor();

        printf("\n=== ISI DOKUMEN ===\n");
        tampilkan();

        if (getCursor() != NULL)
        {
            printf("\nCursor aktif di baris: %d\n", getCursorIndex() + 1);
        }
        else
        {
            printf("\n[!] Cursor belum dipilih\n");
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
                if (jumlahBaris == 0)
                {
                    printf("[!] Dokumen masih kosong. Tambahkan baris terlebih dahulu.\n");
                }
                else
                {
                    editBaris();
                }
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
            {
			    int target;
			
			    if (jumlahBaris == 0)
			    {
			        printf("[!] Dokumen kosong. Cursor tidak bisa dipindahkan.\n");
			    }
			    else
			    {
			    	printf("Masukkan nomor baris target (1-%d): ", jumlahBaris);
			        target = inputInt();
			        
			        if (target >= 1 && target <= jumlahBaris) 
                    {
                        restoreCursorByIndex(target - 1);
                        printf("[v] Cursor berhasil dipindahkan ke baris %d.\n", target);
                    } 
                    else 
                    {
                        printf("[!] Nomor baris di luar jangkauan!\n");
                    }
			    }
			    break;
            }

            case 9:
                undo();
                break;

            case 10:
                redo();
                break;

            case 11:
                if (isModified && !konfirmasiKeluar())
                {
                    break;
                }
                printf("Menutup program...\n");
                clearHistory();
                return 0;

            default:
                printf("[!] Menu tidak tersedia. Silakan pilih menu yang benar.\n");
                break;
        }

        pauseScreen();
    }

    return 0;
}