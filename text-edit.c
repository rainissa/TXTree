#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "text-edit.h"
#include "cursor.h"
#include "history.h"
#include "config.h"

char buffer[MAX_ROW][MAX_KARAKTER];
int jumlahBaris = 0;
int i;

void clearScreen()
{
    system("cls");   
}

void pauseScreen()
{
    printf("\nTekan ENTER untuk lanjut...");
    getchar();
}

void tampilkan()
{
    for(i = 0; i < jumlahBaris; i++)
	{
        printf("%2d | %s\n", i+1, buffer[i]);
    }
}

void tambahBaris()
{
    if(jumlahBaris >= MAX_ROW)
	{
        printf("Buffer penuh!\n");
        pauseScreen();
        return;
    }

    pushSnapshot();
    clearRedo();

    printf("Masukkan teks: "); 
    fgets(buffer[jumlahBaris], MAX_KARAKTER, stdin);

    buffer[jumlahBaris][strcspn(buffer[jumlahBaris], "\n")] = 0;

    cursor_row = jumlahBaris;  // update cursor di baris baru
    cursor_col = 0;

    jumlahBaris = jumlahBaris + 1;
}

void hapusBaris()
{
    int hpsBariske;

    printf("Hapus baris: ");
    scanf("%d", &hpsBariske);
    getchar();

    if(hpsBariske < 1 || hpsBariske > jumlahBaris)
	{
        printf("\nBaris tidak ada!\n");
        pauseScreen();
        return;
    }

    pushSnapshot();
    clearRedo();

    for(i = hpsBariske-1; i < jumlahBaris-1; i++)
	{
        strcpy(buffer[i], buffer[i+1]);
    }

    jumlahBaris = jumlahBaris - 1;

    if (jumlahBaris == 0)
    {
        cursor_row = 0;
    }
    else if (cursor_row >= jumlahBaris)
    {
        cursor_row = jumlahBaris - 1;
    }
    cursor_col = 0;
}

void editBaris()
{
    int nomor;

    printf("Masukkan nomor baris yang ingin diubah: ");
    scanf("%d", &nomor);
    getchar();

    if(nomor < 1 || nomor > jumlahBaris){
        printf("Baris tidak ditemukan!\n");
        pauseScreen();
        return;
    }

    pushSnapshot();
    clearRedo();

    printf("Masukkan teks pengganti: ");
    fgets(buffer[nomor-1], MAX_KARAKTER, stdin);

    buffer[nomor-1][strcspn(buffer[nomor-1], "\n")] = 0;

    cursor_row = nomor - 1;
    cursor_col = 0;
}

void sisipBaris()
{
    int posisi, i;
    if(jumlahBaris >= MAX_ROW)
    {
        printf("Buffer penuh!\n");
        pauseScreen();
        return;
    }

    printf("Masukkan posisi baris: ");
    scanf("%d", &posisi);
    getchar();

    if(posisi < 1 || posisi > jumlahBaris + 1)
	{
        printf("Posisi tidak tersedia!\n");
        pauseScreen();
        return;
    }

    pushSnapshot();
    clearRedo();

    for(i = jumlahBaris; i >= posisi; i--){
        strcpy(buffer[i], buffer[i-1]);
    }

    printf("Tulis teks baru: ");
    fgets(buffer[posisi-1], MAX_KARAKTER, stdin);

    buffer[posisi-1][strcspn(buffer[posisi-1], "\n")] = 0;

    cursor_row = posisi - 1;
    cursor_col = 0;

    jumlahBaris = jumlahBaris + 1;
}