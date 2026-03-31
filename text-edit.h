#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include "config.h"

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