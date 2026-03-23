#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#ifndef MAX_ROW
#define MAX_ROW 100
#endif

#ifndef MAX_KARAKTER
#define MAX_KARAKTER 200
#endif

extern char buffer[MAX_ROW][MAX_KARAKTER];
extern int jumlahBaris;

void clearScreen();
void pauseScreen();
void tampilkan();

void tambahBaris();
void hapusBaris();
void editBaris();
void sisipBaris();

#endif