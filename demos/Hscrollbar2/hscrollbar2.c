#include "hscrollbar2.h"
#include <ncurses.h>

void init_hscrollbar(HScrollbar *scrollbar, int min_value, int max_value, int max_x, int max_y) {
    scrollbar->current_value = min_value;
    scrollbar->min_value = min_value;
    scrollbar->max_value = max_value;
    scrollbar->bar_x = 0;
    scrollbar->scrollbar_x = max_x / 4;
    scrollbar->scrollbar_width = max_x / 2;
    scrollbar->max_x = max_x;
    scrollbar->max_y = max_y;
}

void update_hscrollbar(HScrollbar *scrollbar) {
    scrollbar->bar_x = (scrollbar->current_value - scrollbar->min_value) * scrollbar->scrollbar_width /
                       (scrollbar->max_value - scrollbar->min_value);
}

void draw_hscrollbar(HScrollbar *scrollbar) {
    mvprintw(scrollbar->max_y / 2, scrollbar->scrollbar_x, "[");
    for (int i = 0; i < scrollbar->scrollbar_width; ++i) {
        if (i == scrollbar->bar_x)
            printw("|"); // Draw the bar
        else
            printw("-");
    }
    printw("]");
}
