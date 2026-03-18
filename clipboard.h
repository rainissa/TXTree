#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#define MAX_ROW 100
#define MAX_KARAKTER 200
#define MAX_CLIPBOARD_ROW 20

/* dokumen utama */
extern char buffer[MAX_ROW][MAX_KARAKTER];
extern int jumlahBaris;

/* clipboard multi baris */
extern char clipboard[MAX_CLIPBOARD_ROW][MAX_KARAKTER];
extern int jumlahClipboard;

/* fungsi clipboard */
void setCursor(int row, int col);   // helper untuk paste/cut
void copyBlock(int start, int end);
void cutBlock(int start, int end);
void pasteBlock();

#endif