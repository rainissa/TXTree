#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "config.h"
#define MAX_CLIPBOARD_ROW 20

/* dokumen utama */
extern char buffer[MAX_ROW][MAX_KARAKTER];
extern int jumlahBaris;

/* clipboard multi baris */
extern char clipboard[MAX_CLIPBOARD_ROW][MAX_KARAKTER];
extern int jumlahClipboard;

/* fungsi clipboard */
void copyBlock(int start, int end);
void cutBlock(int start, int end);
void pasteBlock();

#endif