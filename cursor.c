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
    address p = First(L);

    while (p != NULL && p != node) {
        p = Next(p);
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