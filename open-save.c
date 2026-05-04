#include <stdio.h>
#include <string.h>
#include "text-edit.h"
#include "open-save.h"
#include "cursor.h"
#include "config.h"
#include "history.h"

int isModified = 0;
char currentFile[100] = "";
int cekTxt(char namaFile[])
{
    int panjang = strlen(namaFile);

    if(panjang < 4)
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

void openFile()
{
    FILE *file;
    char namaFile[100];

    printf("Masukkan nama file (.txt): ");
    fgets(namaFile, 100, stdin);
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

    jumlahBaris = 0;

    while(jumlahBaris < MAX_ROW && fgets(buffer[jumlahBaris], MAX_KARAKTER, file) != NULL)
    {   
        buffer[jumlahBaris][strcspn(buffer[jumlahBaris], "\r\n")] = '\0';
        jumlahBaris = jumlahBaris + 1;
    }
    fclose(file);
    cursor_row = 0;
    cursor_col = 0;
    strcpy(currentFile, namaFile);
    isModified = 0;

    if(jumlahBaris == MAX_ROW)
    {
        printf("File terlalu besar, sebagian tidak dimuat!\n");
    }
    printf("File berhasil dibuka\n");
}

void saveFile()
{
    FILE *file;
    char namaFile[100];
    int i;

    if(strlen(currentFile)==0)
    {
        printf("Masukkan nama file (.txt): ");
        fgets(namaFile, 100, stdin);
        namaFile[strcspn(namaFile, "\n")] = '\0';

        if(cekTxt(namaFile) == 0)
        {
            printf("Nama file harus .txt\n");
            return;
        }
        strcpy(currentFile, namaFile);
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
    char konfirmasi;
    printf("File telah diubah. Yakin ingin menyimpan? (y/n): ");
    scanf(" %c", &konfirmasi);
    getchar();

    if(konfirmasi != 'y' && konfirmasi != 'Y')
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
    for(i = 0; i < jumlahBaris; i++)
    {
        fprintf(file, "%s\n", buffer[i]);
    }
    fclose(file);
    isModified=0;
    printf("File berhasil disimpan\n");
}