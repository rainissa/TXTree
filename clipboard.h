#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include "text-edit.h"

void setClipboard(const char *text);
const char *getClipboard(void);

void copyLine(void);
void cutLine(void);
void pasteLine(void);

#endif