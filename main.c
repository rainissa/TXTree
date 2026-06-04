#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

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

int inputInt(void)
{
    char buf[23];
    int value;

    while (1)
    {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            continue;

        int terlalupanjang = 1;
        for (int i = 0; buf[i] != '\0'; i++)
        {
            if (buf[i] == '\n') { terlalupanjang = 0; break; }
        }
        if (terlalupanjang)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("[!] Input terlalu panjang! Masukkan angka yang benar: ");
            continue;
        }

        char *ptr = buf;
        while (*ptr == ' ' || *ptr == '\t') ptr++;

        if (*ptr == '\0' || *ptr == '\n')
        {
            printf("[!] Input tidak boleh kosong! Masukkan angka yang benar: ");
            continue;
        }

        char *check = ptr;
        int valid = 1;
        while (*check != '\0' && *check != '\n')
        {
            if (!isdigit((unsigned char)*check))
            {
                valid = 0;
                break;
            }
            check++;
        }

        if (!valid)
        {
            printf("[!] Input tidak valid! Masukkan angka saja: ");
            continue;
        }

        char *endptr;
        long result = strtol(ptr, &endptr, 10);

        if (result > INT_MAX || result < INT_MIN)
        {
            printf("[!] Angka terlalu besar! Masukkan angka yang benar: ");
            continue;
        }

        value = (int)result;
        return value;
    }
}

int konfirmasiKeluar(void)
{
    char buf[23];
    char jawab;

    while (1)
    {
        printf("\nMasih ada perubahan yang belum disimpan.\n");
        printf("Yakin ingin keluar? (y/n): ");

        if (fgets(buf, sizeof(buf), stdin) == NULL) continue;

        int terlalupanjang = 1;
        for (int i = 0; buf[i] != '\0'; i++)
        {
            if (buf[i] == '\n') { terlalupanjang = 0; break; }
        }
        if (terlalupanjang)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("[!] Pilihan tidak valid! Gunakan 'y' atau 'n'.\n");
            continue;
        }

        char *ptr = buf;
        while (*ptr == ' ' || *ptr == '\t') ptr++;

        if (*ptr == '\0' || *ptr == '\n')
        {
            printf("[!] Input tidak boleh kosong! Gunakan 'y' atau 'n'.\n");
            continue;
        }

        char *check = ptr + 1;
        while (*check == ' ' || *check == '\t') check++; // skip spasi di belakang juga
        if (*check != '\n' && *check != '\0')
        {
            printf("[!] Pilihan tidak valid! Gunakan 'y' atau 'n'.\n");
            continue;
        }

        jawab = (char)tolower((unsigned char)*ptr);
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