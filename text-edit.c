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

void pauseScreen()
{
    printf("\nTekan ENTER untuk lanjut...");
    getchar();
}

void tampilkan()
{
    address temp = First(L);
    int i=1;
    while (temp != NULL)
    {
        printf ("%2d | %s\n", i, Info(temp));
        temp = Next(temp);
        i=i+1;
    }
}

void insertFirst(address P)
{
    if(First(L)!=Nil)
    {
        Prev(First(L))=P;
        Next(P)=First(L);
    }
    First(L)=P;
}

void insertLast(address P)
{
    if(First(L)==Nil)
    {
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

void insertBefore (address P, address temp)
{
    address before = Prev(temp);
    if (before == Nil)
    {
        insertFirst(P);
    }
    else
    {
        Next(before) = P;
        Prev(P) = before;
        Next(P) = temp;
        Prev(temp) = P;
    }
}

void tambahBaris()
{
    if(jumlahBaris >= MAX_ROW)
	{
        printf("Buffer penuh!\n");
        return;
    }
    pushSnapshot();
    clearRedo();

    infotype teks;
    printf("Masukkan teks: "); 
    fgets(teks, MAX_KARAKTER, stdin);
    teks[strcspn(teks, "\n")] = 0;

    address P = Alokasi(teks);
    address temp = First(L);
    int idx = 0;
    while (temp != Nil && idx < cursor_row)
    {
        temp = Next(temp);
        idx=idx+1;
    }

    if (First(L)==Nil)
    {
        insertFirst(P);
    }
    else if(temp == First(L))
    {
        insertFirst(P);
    }
    else if(temp == Nil)
    {
        insertLast(P);
    }
    else
    {
        insertBefore(P, temp);
    }
    cursor_row = jumlahBaris;  // update cursor di baris baru
    cursor_col = 0;
    jumlahBaris = jumlahBaris + 1;
    isModified = 1;
}

void editBaris()
{
    int nomor;

    printf("Masukkan nomor baris yang ingin diubah: ");
    scanf("%d", &nomor);
    getchar();
    
    while (getchar()!='\n');
    
    if(nomor < 1 || nomor > jumlahBaris){
        printf("Baris tidak ditemukan!\n");
        return;
    }

    pushSnapshot();
    clearRedo();
    
    address temp = First(L);
    int idx = 1;
    while (temp != NULL && idx < nomor)
    {
        temp = Next(temp);
        idx=idx+1;
    }
    if (temp != NULL)
    {
        printf("Masukkan teks pengganti: ");
        fgets(Info(temp), MAX_KARAKTER, stdin);
        Info(temp)[strcspn(Info(temp), "\n")] = 0;
    cursor_row = nomor - 1;
    cursor_col = 0;
    isModified = 1;
    }
}