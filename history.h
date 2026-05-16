#ifndef HISTORY_H
#define HISTORY_H

#include "config.h"
#include "text-edit.h"

typedef struct SnapBaris {
    infotype teks;
    struct SnapBaris *next;
} SnapBaris;

typedef struct {
    SnapBaris *head;
    int jumlahBaris;
    int cursor_index;
} Snapshot;

typedef struct NodeSnapshot {
    Snapshot info;
    struct NodeSnapshot *next;
} NodeSnapshot;

typedef NodeSnapshot *address_snap;

void pushSnapshot(void);
void undo(void);
void redo(void);
void clearRedo(void);
void clearHistory(void);

#endif