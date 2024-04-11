#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <ncurses.h>

typedef struct {
    char text[50][50];
    int cursor_x;
    int cursor_y;
    int width;
    int height;
} TextArea;

void draw_text_area(WINDOW *win, TextArea *text_area);

#endif /* TEXTAREA_H */
