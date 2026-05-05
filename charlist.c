#include <stdlib.h>
#include "charlist.h"

CharNode* buildList(const char *text) {
    CharNode *head = NULL, *tail = NULL;

    for (int i = 0; text[i] != '\0'; i++) {
        CharNode *node = (CharNode*) malloc(sizeof(CharNode));
        if (!node) return NULL;

        node->data = text[i];
        node->next = NULL;

        if (!head) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

void listToString(CharNode *head, char *dest, int maxLen) {
    int i = 0;
    while (head && i < maxLen - 1) {
        dest[i++] = head->data;
        head = head->next;
    }
    dest[i] = '\0';
}

void freeList(CharNode *head) {
    while (head) {
        CharNode *temp = head;
        head = head->next;
        free(temp);
    }
}