#ifndef CHARLIST_H
#define CHARLIST_H

typedef struct CharNode {
    char data;
    struct CharNode *next;
} CharNode;

CharNode* buildList(const char *text);
void listToString(CharNode *head, char *dest, int maxLen);
void freeList(CharNode *head);

#endif