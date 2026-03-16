#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#define MAX_BARIS 100
#define MAX_KARAKTER 256

/* variabel global dokumen */
extern char dokumen[MAX_BARIS][MAX_KARAKTER];
extern char clipboard[MAX_KARAKTER];
extern int jumlahBaris;
extern int cursor;

/* pengaturan cursor */
void setCursor(int posisi);

/* input teks dengan auto pindah baris */
void inputText(char teks[]);

/* operasi clipboard */
void copyLine();
void cutLine();
void pasteLine();

#endif