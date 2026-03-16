#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#define MAX_BARIS 100
#define MAX_KARAKTER 256

/* variabel global dari dokumen */
extern char dokumen[MAX_BARIS][MAX_KARAKTER];
extern char clipboard[MAX_KARAKTER];
extern int jumlahBaris;
extern int cursor;

/* fungsi pengaturan cursor */
void setCursor(int posisi);

/* operasi clipboard */
void copyLine();
void cutLine();
void pasteLine();

#endif