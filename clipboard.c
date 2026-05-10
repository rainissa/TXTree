#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clipboard.h"
#include "text-edit.h"
#include "history.h"
#include "config.h"

static char clipboard[MAX_KARAKTER];

void setClipboard(const char *text)
{
    strncpy(clipboard, text, MAX_KARAKTER - 1);
    clipboard[MAX_KARAKTER - 1] = '\0';
}

char* getClipboard()
{
    return clipboard;
}

int isClipboardEmpty()
{
    return clipboard[0] == '\0';
}

void copyLine(List *L, address current)
{
    if (First(*L) == NULL || current == NULL)
    {
        printf("Tidak ada baris aktif\n");
        return;
    }

    setClipboard(Info(current));

    printf("Copy berhasil:\n\"%s\"\n", getClipboard());
}

void cutLine(List *L, address *current)
{
    address hapus;

    if (First(*L) == NULL || *current == NULL)
    {
        printf("Tidak ada baris aktif\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    setClipboard(Info(*current));

    hapus = *current;

    /* node satu-satunya */
    if (Prev(hapus) == NULL && Next(hapus) == NULL)
    {
        First(*L) = NULL;
        *current = NULL;
    }

    /* hapus node pertama */
    else if (Prev(hapus) == NULL)
    {
        First(*L) = Next(hapus);
        Prev(Next(hapus)) = NULL;

        *current = First(*L);
    }

    /* hapus node terakhir */
    else if (Next(hapus) == NULL)
    {
        Next(Prev(hapus)) = NULL;

        *current = Prev(hapus);
    }

    /* hapus node tengah */
    else
    {
        Next(Prev(hapus)) = Next(hapus);
        Prev(Next(hapus)) = Prev(hapus);

        *current = Next(hapus);
    }

    free(hapus);

    printf("Cut berhasil\n");
}

void pasteLine(List *L, address *current)
{
    address baru;

    if (isClipboardEmpty())
    {
        printf("Clipboard kosong\n");
        return;
    }

    pushSnapshot();
    clearRedo();

    baru = Alokasi(getClipboard());

    if (baru == NULL)
    {
        printf("Gagal alokasi memori\n");
        return;
    }

    /* jika list kosong */
    if (First(*L) == NULL)
    {
        First(*L) = baru;
        *current = baru;

        printf("Paste berhasil\n");
        return;
    }

    /* sisip setelah current */
    Next(baru) = Next(*current);
    Prev(baru) = *current;

    if (Next(*current) != NULL)
    {
        Prev(Next(*current)) = baru;
    }

    Next(*current) = baru;

    *current = baru;

    printf("Paste berhasil\n");
}