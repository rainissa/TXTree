#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include "config.h"

extern char buffer[MAX_ROW][MAX_KARAKTER];
extern int jumlahBaris;

void pauseScreen();
void tampilkan();

void tambahBaris();
void editBaris();
void sisipBaris();

#endif