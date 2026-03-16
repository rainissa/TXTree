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

/* COPY
   Memindahkan satu baris ke clipboard
   sekaligus menghapus dari dokumen
*/
void copyLine()
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

    printf("Baris berhasil dipindahkan ke clipboard\n");
}

/* CUT
   Sama seperti copy tetapi tetap sesuai rancangan
   memindahkan baris ke clipboard
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
   Menambahkan teks clipboard di bawah cursor
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
        printf("Dokumen sudah penuh\n");
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