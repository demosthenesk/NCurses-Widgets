#ifndef TEXTBOX_H
#define TEXTBOX_H

typedef struct {
    char *text;
    int cursor_pos;
    int width;
    int height;
    int starty;
    int startx;
} TEXTBOX;

#include <ncurses.h>
#include <string.h>

void draw_textbox(WINDOW *win, TEXTBOX *textbox);
void handle_textbox_input(TEXTBOX *textbox, int ch);

#endif /* TEXTBOX_H */
