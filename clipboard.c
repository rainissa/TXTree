#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "clipboard.h"
#include "cursor.h"
#include "history.h"
#include "text-edit.h"
#include "config.h"

extern List L;
extern int jumlahBaris;
extern int isModified;

static char clipboard[MAX_KARAKTER] = "";

static int cursorAktif(address current)
{
    if (current == NULL)
    {
        printf("[!] Operasi gagal: belum ada baris yang aktif di cursor.\n");
        return 0;
    }
    return 1;
}

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

    if (!cursorAktif(current))
        return;

    setClipboard(Info(current));

    printf("[v] Baris %d berhasil disalin ke clipboard.\n",
           getCursorIndex() + 1);
}

void cutLine(void)
{
    address current = getCursor();

    if (!cursorAktif(current))
        return;

    pushSnapshot();
    clearRedo();

    setClipboard(Info(current));

    address prevNode = Prev(current);
    address nextNode = Next(current);

    if (prevNode != NULL)
        Next(prevNode) = nextNode;
    else
        First(L) = nextNode;

    if (nextNode != NULL)
        Prev(nextNode) = prevNode;

    free(current);
    jumlahBaris--;

    setCursor(jumlahBaris > 0 ? (nextNode != NULL ? nextNode : prevNode)
                              : NULL);

    isModified = 1;

    printf("[v] Baris berhasil dipotong dan disimpan ke clipboard.\n");
}

void pasteLine(void)
{
    if (clipboard[0] == '\0')
    {
        printf("[!] Paste gagal: clipboard kosong, tidak ada teks yang bisa ditempel.\n");
        return;
    }

    if (First(L) == NULL)
    {
        address newNode = Alokasi(clipboard);

        if (newNode == NULL)
        {
            printf("[!] Paste gagal: alokasi memori untuk baris baru tidak berhasil.\n");
            return;
        }

        pushSnapshot();
        clearRedo();

        insertFirst(newNode);  
        setCursor(newNode);
        jumlahBaris++;
        isModified = 1;

        printf("[v] Paste berhasil: baris baru dibuat dari isi clipboard.\n");
        return;
    }

    address current = getCursor();

    if (!cursorAktif(current))
        return;

    size_t currentLen = strlen(Info(current));
    size_t clipLen    = strlen(clipboard);
    size_t available  = (MAX_KARAKTER - 1) - currentLen;   

    if (available == 0)
    {
        printf("[!] Paste gagal: baris aktif sudah penuh (%d karakter), tidak ada ruang lagi.\n",
               MAX_KARAKTER - 1);
        return;
    }

    pushSnapshot();
    clearRedo();

    if (clipLen > available)
    {
        strncat(Info(current), clipboard, available);
        printf("[~] Paste sebagian: hanya %zu dari %zu karakter yang bisa ditempel"
               " (baris hampir penuh).\n",
               available, clipLen);
    }
    else
    {
        strncat(Info(current), clipboard, clipLen);
        printf("[v] Paste berhasil: isi clipboard ditempelkan ke baris %d.\n",
               getCursorIndex() + 1);
    }

    Info(current)[MAX_KARAKTER - 1] = '\0'; 

    isModified = 1;
}