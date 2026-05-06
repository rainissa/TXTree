#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include "config.h"
#include <stdlib.h>
#include <string.h>
#define Nil NULL
#define Info(P) (P)->teks
#define Next(P) (P)->next
#define Prev(P) (P)->prev
#define First(L) (L).first

typedef char infotype[MAX_KARAKTER];
typedef struct BarisTeks *address;
typedef struct BarisTeks{
    infotype teks;
    address next;
    address prev;
} BarisTeks;
typedef struct {
    address first;
} List;

void CreateList (List *L);
void pauseScreen();
void insertFirst(address P);
void insertLast(address P);
void insertBefore(address P, address temp);
void tampilkan();
void tambahBaris();
void editBaris();
address Alokasi(infotype x);

#endif