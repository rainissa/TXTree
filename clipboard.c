#include <stdio.h>
#include <string.h>

#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "config.h"

extern List L;
extern int jumlahBaris;
extern int isModified;

static char clipboard[MAX_KARAKTER] = "";

void setClipboard(const char *text)
{
    if (text == NULL)
    {
        clipboard[0] = '\0';
        return;
    }

    strncpy(clipboard, text, MAX_KARAKTER - 1);
    clipboard[MAX_KARAKTER - 1] = '\0';
}

const char *getClipboard(void)
{
    return clipboard;
}

void copyLine(void)
{
    address current = getCursor();

    if (current == NULL)
    {
        printf("Tidak ada baris yang dipilih!\n");
        return;
    }

    setClipboard(Info(current));

    printf("Baris berhasil disalin.\n");
}

void cutLine(void)
{
    address current = getCursor();

    if (current == NULL)
    {
        printf("Tidak ada baris yang dipilih!\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    setClipboard(Info(current));

    address prevNode = Prev(current);
    address nextNode = Next(current);

    if (prevNode != NULL)
    {
        Next(prevNode) = nextNode;
    }
    else
    {
        First(L) = nextNode;
    }

    if (nextNode != NULL)
    {
        Prev(nextNode) = prevNode;
    }

    free(current);

    jumlahBaris--;

    if (jumlahBaris <= 0)
    {
        jumlahBaris = 0;
        setCursor(NULL);
    }
    else if (nextNode != NULL)
    {
        setCursor(nextNode);
    }
    else
    {
        setCursor(prevNode);
    }

    isModified = 1;

    printf("Baris berhasil dipotong.\n");
}

void pasteLine(void)
{
    if (clipboard[0] == '\0')
    {
        printf("Clipboard kosong!\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    address current = getCursor();

    if (First(L) == NULL)
    {
        address newNode = Alokasi(clipboard);

        if (newNode == NULL)
        {
            printf("Gagal alokasi memori!\n");
            return;
        }

        First(L) = newNode;

        setCursor(newNode);

        jumlahBaris++;

        isModified = 1;

        printf("Paste berhasil.\n");

        return;
    }

    if (current == NULL)
    {
        printf("Cursor tidak aktif!\n");
        return;
    }

    if (strlen(Info(current)) + strlen(clipboard) >= MAX_KARAKTER)
    {
        printf("Teks terlalu panjang!\n");
        return;
    }

    strcat(Info(current), clipboard);

    isModified = 1;

    printf("Paste berhasil.\n");
}