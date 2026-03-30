#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#define MAX_ROW 100
#define MAX_KARAKTER 200

extern char buffer[MAX_ROW][MAX_KARAKTER];
extern int jumlahBaris;

extern char clipboard[MAX_KARAKTER];

void copyLine();
void cutLine();
void pasteLine();

#endif