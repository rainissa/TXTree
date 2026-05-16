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
    address cursor = getCursor();
    if (First(L)==Nil)
    {
        insertFirst(P);
    }
    else if(cursor == First(L) || cursor == Nil)
    {
        insertFirst(P);
    }
    else if (Next(cursor)==Nil)
    {
        insertLast(P);
    }
    else
    {
        insertBefore(P, cursor);
    }
    setCursor(P);  // update cursor di baris baru
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
    int i = 1;
    while (temp != Nil && i < nomor)
    {
        temp = Next(temp);
        i=i+1;
    }
    if (temp == Nil)
    {
        printf("Baris tidak ditemukan!\n");
        return;
    }
    printf("Masukkan teks pengganti: ");
    fgets(Info(temp), MAX_KARAKTER, stdin);
    Info(temp)[strcspn(Info(temp), "\n")] = 0;
    setCursor(temp);
    isModified = 1;
}