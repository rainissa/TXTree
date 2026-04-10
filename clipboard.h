#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "config.h"

extern char buffer[MAX_ROW][MAX_KARAKTER];
extern int jumlahBaris;

void setClipboard(const char *text);
char* getClipboard();
int isClipboardEmpty();

void copyLine();
void cutLine();
void pasteLine();

#endif