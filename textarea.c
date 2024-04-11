#include "textarea.h"
#include <string.h>

void draw_text_area(WINDOW *win, TextArea *text_area) {
    werase(win);
    box(win, 0, 0);
    for (int i = 0; i < text_area->height; i++) {
        for (int j = 0; j < text_area->width - 2; j++) {
            mvwaddch(win, i + 1, j + 2, text_area->text[i][j]);
        }
    }
    wmove(win, text_area->cursor_y + 1, text_area->cursor_x + 1);
    wrefresh(win);
}

