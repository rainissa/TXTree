#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"
#include "cursor.h"
#include "text-edit.h"
#include "config.h"

extern List L;
extern int jumlahBaris;

static address_snap undoStack = NULL;
static address_snap redoStack = NULL;

static void freeSnapBaris(SnapBaris *head) {
    while (head != NULL) {
        SnapBaris *hapus = head;
        head = head->next;
        free(hapus);
    }
}

static address_snap alokasiSnapshot(void) {
    address_snap new_node = malloc(sizeof(NodeSnapshot));
    if (new_node == NULL) return NULL;

    new_node->info.jumlahBaris  = jumlahBaris;
    new_node->info.cursor_index = getCursorIndex();
    new_node->info.head         = NULL;
    new_node->next              = NULL;

    SnapBaris *snapTail = NULL;
    address src = First(L);
    while (src != NULL) {
        SnapBaris *node = malloc(sizeof(SnapBaris));
        if (!node) {
            freeSnapBaris(new_node->info.head);
            free(new_node);
            return NULL;
        }
        strcpy(node->teks, Info(src));
        node->next = NULL;
        if (snapTail == NULL) {
            new_node->info.head = node;
        } else {
            snapTail->next = node;
        }
        snapTail = node;
        src = Next(src);
    }

    return new_node;
}

static void pushToStack(address_snap *stack, address_snap node) {
    if (node != NULL) {
        node->next = *stack;
        *stack = node;
    }
}

static address_snap popFromStack(address_snap *stack) {
    if (*stack == NULL) return NULL;
    address_snap target = *stack;
    *stack = (*stack)->next;
    target->next = NULL;
    return target;
}

static void popBottom(address_snap *stack) {
    if (*stack == NULL) return;
    if ((*stack)->next == NULL) {
        freeSnapBaris((*stack)->info.head);
        free(*stack);
        *stack = NULL;
        return;
    }
    address_snap p = *stack;
    while (p->next->next != NULL) {
        p = p->next;
    }
    freeSnapBaris(p->next->info.head);
    free(p->next);
    p->next = NULL;
}

static void restoreSnapshot(Snapshot *snap) {
    address p = First(L);
    while (p != NULL) {
        address hapus = p;
        p = Next(p);
        free(hapus);
    }
    First(L) = NULL;
    resetCursor(); 
    
    int count = 0;
    SnapBaris *src = snap->head;
    while (src != NULL) {
        address node = Alokasi(src->teks);
        if (node == NULL) {
            printf("[!] Gagal me-restore seluruh baris karena memori penuh.\n");
            break;
        }
        insertLast(node);
        count++;
        src = src->next;
    }

    jumlahBaris = count;
    restoreCursorByIndex(snap->cursor_index);
}

void clearRedo(void) {
    while (redoStack != NULL) {
        address_snap temp = popFromStack(&redoStack);
        freeSnapBaris(temp->info.head);
        free(temp);
    }
}

void pushSnapshot(void) {
    if (undoStack != NULL) {
        int count = 0;
        address_snap p = undoStack;
        while (p != NULL) { count++; p = p->next; }
        if (count >= STACK_SIZE) {
            popBottom(&undoStack);
        }
    }
    address_snap new_snap = alokasiSnapshot();
    if (new_snap != NULL) {
        pushToStack(&undoStack, new_snap);
    }
}

void undo(void) {
    if (undoStack == NULL) {
        printf("\n[!] Tidak ada aksi untuk di-undo.\n");
        return;
    }
    address_snap current_state = alokasiSnapshot();
    if (current_state != NULL) {
        pushToStack(&redoStack, current_state);
    }
    address_snap prev_state = popFromStack(&undoStack);
    restoreSnapshot(&(prev_state->info));
    freeSnapBaris(prev_state->info.head);
    free(prev_state);
    printf("\n[v] Undo berhasil.\n");
}

void redo(void) {
    if (redoStack == NULL) {
        printf("\n[!] Tidak ada aksi untuk di-redo.\n");
        return;
    }
    address_snap current_state = alokasiSnapshot();
    if (current_state != NULL) {
        pushToStack(&undoStack, current_state);
    }
    address_snap next_state = popFromStack(&redoStack);
    restoreSnapshot(&(next_state->info));
    freeSnapBaris(next_state->info.head);
    free(next_state);
    printf("\n[v] Redo berhasil.\n");
}

void clearHistory(void) {
    while (undoStack != NULL) {
        address_snap temp = popFromStack(&undoStack);
        freeSnapBaris(temp->info.head);
        free(temp);
    }
    clearRedo();
}