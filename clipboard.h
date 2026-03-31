#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "config.h"
#define MAX_CLIPBOARD_ROW 20

extern char buffer[MAX_ROW][MAX_KARAKTER];
extern int jumlahBaris;

extern char clipboard[MAX_KARAKTER];

void copyLine();
void cutLine();
void pasteLine();

#endif