#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "text-edit.h"
#include "cursor.h"
#include "history.h"
#include "config.h"

extern int isModified;

List L;
int jumlahBaris = 0;

void CreateList(List *L)
{
    First(*L) = Nil;
}

address Alokasi(infotype x)
{
    address P = (address) malloc(sizeof(BarisTeks));

    if (P != Nil)
    {
        strcpy(Info(P), x);
        Next(P) = Nil;
        Prev(P) = Nil;
    }

    return P;
}

void pauseScreen()
{
    printf("\nTekan ENTER untuk lanjut...");
    getchar();
}

void tampilkan()
{
    address temp = First(L);
    int i=1;
    while (temp != Nil)
    {
        printf ("%2d | %s\n", i, Info(temp));
        temp = Next(temp);
        i=i+1;
    }
}

void insertFirst(address P)
{
    if(P==Nil)
    {
        return;
    }
    Prev(P)=Nil;

    if(First(L)!=Nil)
    {
        Prev(First(L))=P;
        Next(P)=First(L);
    }
    else
    {
        Next(P)=Nil;
    }
    First(L)=P;
}

void insertLast(address P)
{
    if(P==Nil)
    {
        return;
    }
    Next(P)=Nil;

    if(First(L)==Nil)
    {
        Prev(P)=Nil;
        First(L)=P;
        return;
    }
    address temp = First(L);
    while (Next(temp)!=Nil)
    {
        temp=Next(temp);
    }
    Next(temp)=P;
    Prev(P)=temp;
}

void insertAfter (address cursor, address P)
{
    if (cursor == Nil || P == Nil)
    {
        return;
    }
    
    address after = Next(cursor);
    Next(cursor) = P;
    Prev(P) = cursor;

    if (after != Nil)
    {
        Next(P) = after;
        Prev(after) = P;
    }
    else
    {
        Next(P) = Nil;
    }
}

void tambahBaris()
{
    infotype teks;
    printf("Masukkan teks: "); 
    fgets(teks, MAX_KARAKTER, stdin);
    teks[strcspn(teks, "\n")] = 0;

    address P = Alokasi(teks);
    if (P == Nil)
    {
        printf("[!] Alokasi memori gagal\n");
        return;
    }
    pushSnapshot();
    clearRedo();
    
    address cursor = getCursor();
    if (First(L)==Nil)
    {
        insertFirst(P);
    }
    else if (Next(cursor)==Nil)
    {
        insertLast(P);
    }
    else
    {
        insertAfter(cursor, P);
    }
    setCursor(P);  // update cursor di baris baru
    jumlahBaris = jumlahBaris + 1;
    isModified = 1;
    printf("[v] Baris berhasil ditambahkan\n");
}

void editBaris()
{
    int nomor;

    printf("Masukkan nomor baris yang ingin diubah: ");
    scanf("%d", &nomor);
    while (getchar()!='\n');

    pushSnapshot();
    clearRedo();
    
    address temp = First(L);
    int i = 1;
    while (temp != Nil && i < nomor)
    {
        temp = Next(temp);
        i=i+1;
    }
    if (temp == Nil || i != nomor)
    {
        printf("[!] Baris tidak ditemukan!\n");
        return;
    }
    printf("Masukkan teks pengganti: ");
    fgets(Info(temp), MAX_KARAKTER, stdin);
    Info(temp)[strcspn(Info(temp), "\n")] = 0;
    setCursor(temp);
    isModified = 1;
    printf("[v] Baris berhasil diubah\n");
}