#include "cursor.h"
#include "text-edit.h"

extern List L;

static address current = NULL;

void initCursor(void) {
    current = First(L);
}

void validateCursor(void) {
    if (First(L) == NULL) {
        current = NULL;
        return;
    }
    if (current == NULL) {
        current = First(L);
    }
}

void setCursor(address node) {
    if (node == NULL) {
        current = NULL;
        validateCursor();
        return;
    }

    address p = current;
    while (p != NULL && p != node) {
        p = Next(p);
    }

    if (p == NULL) {
        p = current;
        while (p != NULL && p != node) {
            p = Prev(p);
        }
    }

    if (p == NULL) {
        p = First(L);
        while (p != NULL && p != node) {
            p = Next(p);
        }
    }

    if (p != NULL) {
        current = node;
    } else {
        current = NULL;
    }
    validateCursor();
}

address getCursor(void) {
    return current;
}

int getCursorIndex(void) {
    address curr = getCursor();
    if (curr == NULL) return -1;
    int index = 0;
    address p = First(L);
    while (p != NULL && p != curr) {
        index++;
        p = Next(p);
    }
    if (p == NULL) return -1;
    return index;
}

void restoreCursorByIndex(int index) {
    if (index < 0 || First(L) == NULL) {
        setCursor(NULL);
        return;
    }
    int count = 0;
    address p = First(L);
    while (p != NULL && count < index) {
        p = Next(p);
        count++;
    }
    if (p != NULL) {
        setCursor(p);
    } else {
        setCursor(First(L));
    }
}