#include <stdio.h>
#include <string.h>
#include "text-edit.h"
#include "open-save.h"
#include "cursor.h"
#include "config.h"
#include "history.h"

extern List L;
extern int jumlahBaris;

int isModified = 0;
char currentFile[100] = "";
int cekTxt(char namaFile[])
{
    int panjang = strlen(namaFile);
    int i;
    int hanyaSpasi = 1;
    if(panjang <= 4)
    {
        return 0;
    }
    for (i=0; i<panjang-4; i++)
    {
        if (namaFile[i] != ' ')
        {
            hanyaSpasi = 0;
            break;
        }
    }
    if (hanyaSpasi)
    {
        return 0;
    }
    if(namaFile[panjang-4] == '.' &&
        (namaFile[panjang-3] == 't' || namaFile[panjang-3] == 'T') &&
        (namaFile[panjang-2] == 'x' || namaFile[panjang-2] == 'X') &&
        (namaFile[panjang-1] == 't' || namaFile[panjang-1] == 'T'))
    {
        return 1;
    }
    return 0;
}

void deleteAll()
{
    address P = First(L);
    address temp;

    while(P != Nil)
    {
        temp = P;
        P = Next(P);
        free(temp);
    }
    First(L) = Nil;
    jumlahBaris=0;
    setCursor(Nil);
}

void openFile()
{
    FILE *file;
    char namaFile[100];
    char temp[MAX_KARAKTER];
    char konfirmasi;

    if(isModified == 1)
    {
        printf("Perubahan belum disimpan. Tetap buka file baru? (y/n): ");
        scanf(" %c", &konfirmasi);
        while (getchar() != '\n');
        
        if (konfirmasi != 'y' && konfirmasi != 'Y')
        {
            printf("Open file dibatalkan\n");
            return;
        }
    }

    printf("Masukkan nama file (.txt): ");
    fgets(namaFile, sizeof(namaFile), stdin);
    namaFile[strcspn(namaFile, "\n")] = '\0';

    if(cekTxt(namaFile) == 0)
    {
        printf("File harus berekstensi .txt\n");
        return;
    }
    file = fopen(namaFile, "r");
    if(file == NULL)
    {
        printf("File tidak ditemukan\n");
        return;
    }

    pushSnapshot();
    clearRedo();
    deleteAll();

    while(fgets(temp, MAX_KARAKTER, file) != NULL)
    {   
        temp[strcspn(temp, "\r\n")] = '\0';
        address P = Alokasi(temp);
        if (P != NULL)
        {
            insertLast(P);
            jumlahBaris = jumlahBaris + 1;
        }
    }
    fclose(file);
    initCursor();
    strcpy(currentFile, namaFile);
    isModified = 0;
    printf("File berhasil dibuka\n");
}

void saveFile()
{
    FILE *file;
    char namaFile[100];
    char konfirmasi;

    if(strlen(currentFile)==0)
    {
        printf("Masukkan nama file (.txt): ");
        fgets(namaFile, sizeof(namaFile), stdin);
        namaFile[strcspn(namaFile, "\n")] = '\0';

        if(cekTxt(namaFile) == 0)
        {
            printf("Nama file harus .txt\n");
            return;
        }
    }
    else
    {
        strcpy(namaFile, currentFile);
        printf("Menyimpan ke file: %s\n", namaFile);
    }

    if(isModified==0)
    {
        printf("Tidak ada perubahan untuk disimpan\n");
        return;
    }
    printf("Simpan perubahan ke file? (y/n): ");
    scanf(" %c", &konfirmasi);
    while (getchar() != '\n');

    if (konfirmasi != 'y' && konfirmasi != 'Y' &&
        konfirmasi != 'n' && konfirmasi != 'N')
    {
        printf("Input tidak valid!\n");
        return;
    }

    if(konfirmasi == 'n' || konfirmasi == 'N')
    {
        printf("Penyimpanan dibatalkan\n");
        return;
    }

    file = fopen(namaFile, "w");
    if(file == NULL)
    {
        printf("Gagal menyimpan file\n");
        return;
    }
    address P = First(L);
    while (P != Nil)
    {
        fprintf(file, "%s\n", Info(P));   
        P = Next(P);
    }
    fclose(file);
    strcpy(currentFile, namaFile);
    isModified=0;
    printf("File berhasil disimpan\n");
}    