#include <stdio.h>
#include <string.h>
#include "text-edit.h"
#include "open-save.h"
#include "cursor.h"
#include "config.h"
#include "history.h"

// Mengecek apakah file berekstensi .txt
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

    printf("Masukkan nama file (.txt): ");
    fgets(namaFile, 100, stdin);
	namaFile[strcspn(namaFile, "\n")] = '\0';

    if(cekTxt(namaFile) == 0)
    {
        printf("Nama file harus .txt\n");
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
    printf("File berhasil disimpan\n");
}