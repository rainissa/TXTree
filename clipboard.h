#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "config.h"
#include "text-edit.h"

void setClipboard(const char *text);
char* getClipboard();
int isClipboardEmpty();

void copyLine(List *L, address current);
void cutLine(List *L, address *current);
void pasteLine(List *L, address *current);

#endif