// vscrollbar.c

#include "vscrollbar.h"

void draw_Vscrollbar(WINDOW *win, VScrollbar *scrollbar) {
    // Calculate the position of the thumb
    scrollbar->thumb_pos = (scrollbar->current_value - scrollbar->min_value) * (scrollbar->scrollbar_height - 2) / (scrollbar->max_value - scrollbar->min_value) + 1;

    // Display the scrollbar
    box(win, 0, 0);
    mvwprintw(win, scrollbar->thumb_pos, 2, "|");
    wrefresh(win);
}

void erase_Vscrollbar(WINDOW *win, VScrollbar *scrollbar) {
    // Clear the scrollbar window
    werase(win);
    wrefresh(win);
}

void handle_Vscrollbar_input(int ch, VScrollbar *scrollbar) {
    switch (ch) {
        case KEY_DOWN:
            if (scrollbar->current_value < scrollbar->max_value) {
                scrollbar->current_value++;
            }
            break;
        case KEY_UP:
            if (scrollbar->current_value > scrollbar->min_value) {
                scrollbar->current_value--;
            }
            break;
    }
}
