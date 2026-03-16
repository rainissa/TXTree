#include <stdio.h>
#include <string.h>
#include "clipboard.h"

/* mengatur posisi cursor */
void setCursor(int posisi)
{
    if (posisi >= 0 && posisi < jumlahBaris)
    {
        cursor = posisi;
        printf("Cursor berpindah ke baris %d\n", cursor);
    }
    else
    {
        printf("Posisi cursor tidak valid\n");
    }
}

/* INPUT TEKS
   Jika panjang baris penuh maka otomatis pindah baris
*/
void inputText(char teks[])
{
    int i = 0;

    while (teks[i] != '\0')
    {
        int panjang = strlen(dokumen[cursor]);

        /* jika baris sudah penuh */
        if (panjang >= MAX_KARAKTER - 1)
        {
            if (jumlahBaris >= MAX_BARIS - 1)
            {
                printf("Dokumen penuh\n");
                return;
            }

            cursor++;
            jumlahBaris++;
            dokumen[cursor][0] = '\0';
        }

        int pos = strlen(dokumen[cursor]);
        dokumen[cursor][pos] = teks[i];
        dokumen[cursor][pos + 1] = '\0';

        i++;
    }
}

/* COPY
   hanya menyalin baris ke clipboard
*/
void copyLine()
{
    if (jumlahBaris == 0)
    {
        printf("Dokumen kosong\n");
        return;
    }

    strcpy(clipboard, dokumen[cursor]);

    printf("Baris berhasil dicopy\n");
}

/* CUT
   menyalin ke clipboard lalu menghapus dari dokumen
*/
void cutLine()
{
    if (jumlahBaris == 0)
    {
        printf("Dokumen kosong\n");
        return;
    }

    strcpy(clipboard, dokumen[cursor]);

    for (int i = cursor; i < jumlahBaris - 1; i++)
    {
        strcpy(dokumen[i], dokumen[i + 1]);
    }

    jumlahBaris--;

    printf("Baris dipotong ke clipboard\n");
}

/* PASTE
   menempelkan clipboard di bawah cursor
*/
void pasteLine()
{
    if (strlen(clipboard) == 0)
    {
        printf("Clipboard kosong\n");
        return;
    }

    if (jumlahBaris >= MAX_BARIS)
    {
        printf("Dokumen penuh\n");
        return;
    }

    for (int i = jumlahBaris; i > cursor + 1; i--)
    {
        strcpy(dokumen[i], dokumen[i - 1]);
    }

    strcpy(dokumen[cursor + 1], clipboard);

    jumlahBaris++;

    printf("Clipboard ditempel di bawah cursor\n");
}