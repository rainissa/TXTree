#ifndef CURSOR_H
#define CURSOR_H

typedef struct CursorNode {
    int col;
    struct CursorNode *next;
} CursorNode;

extern CursorNode *cursor_head;

#define cursor_col (cursor_head ? cursor_head->col : 0)

void initCursor(void);
void validateCursor(void);
void setCursor(int col);
void pushCursor(int col);
int  popCursor(void);
void freeCursorList(void);
void printCursorList(void);

#endif