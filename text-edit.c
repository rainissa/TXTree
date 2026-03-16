#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "text-edit.h"

#define MAX_BARIS 100
#define MAX_KARAKTER 200

char buffer[MAX_BARIS][MAX_KARAKTER];
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
    clearScreen();
    printf("\n====== TEXT EDITOR ======\n\n");

    for(i = 0; i < jumlahBaris; i++)
	{
        printf("%2d | %s\n", i+1, buffer[i]);
    }

    printf("\n---------------------------------\n");
    printf("1. Tambah baris\n");
    printf("2. Hapus baris\n");
    printf("3. Edit Baris\n");
    printf("4. Sisip Baris\n");
    printf("5. Save File\n");
    printf("6. Open File\n");
    printf("7. Keluar\n");
    printf("---------------------------------\n");
}

void tambahBaris()
{
    if(jumlahBaris >= MAX_BARIS)
	{
        printf("Buffer penuh!\n");
        pauseScreen();
        return;
    }

    printf("Masukkan teks: "); 
    fgets(buffer[jumlahBaris], MAX_KARAKTER, stdin);

    buffer[jumlahBaris][strcspn(buffer[jumlahBaris], "\n")] = 0;

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

    for(i = hpsBariske-1; i < jumlahBaris-1; i++)
	{
        strcpy(buffer[i], buffer[i+1]);
    }

    jumlahBaris = jumlahBaris - 1;
}

void editBaris()
{
    int nomor;

    printf("Masukkan nomor baris yang ingin diubah: ");
    scanf("%d", &nomor);
    getchar();

    if(nomor < 1 || nomor > jumlahBaris){
        printf("Baris tidak ditemukan!\n");
        return;
    }

    printf("Masukkan teks pengganti: ");
    fgets(buffer[nomor-1], MAX_KARAKTER, stdin);

    buffer[nomor-1][strcspn(buffer[nomor-1], "\n")] = 0;
}

void sisipBaris()
{
    int posisi, i;

    printf("Masukkan posisi baris: ");
    scanf("%d", &posisi);

    if(posisi < 1 || posisi > jumlahBaris + 1)
	{
        printf("Posisi tidak tersedia!\n");
        return;
    }

    for(i = jumlahBaris; i >= posisi; i--){
        strcpy(buffer[i], buffer[i-1]);
    }

    printf("Tulis teks baru: ");
    getchar();
    fgets(buffer[posisi-1], MAX_KARAKTER, stdin);

    buffer[posisi-1][strcspn(buffer[posisi-1], "\n")] = 0;

    jumlahBaris = jumlahBaris + 1;
}