#ifndef CURSOR_H
#define CURSOR_H

#include "text-edit.h"

void initCursor(void);
void validateCursor(void);
void setCursor(address node);
address getCursor(void);
int getCursorIndex(void);
void restoreCursorByIndex(int index);

#endif