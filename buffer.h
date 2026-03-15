#ifndef BUFFER_H
#define BUFFER_H

#define MAX_BARIS 100
#define MAX_KARAKTER 200

extern char buffer[MAX_BARIS][MAX_KARAKTER];
extern int jumlahBaris;

void clearScreen();
void pauseScreen();
void tampilkan();

void tambahBaris();
void hapusBaris();
void editBaris();
void sisipBaris();

#endif