// vscrollbar.h

#ifndef VSCROLLBAR_H
#define VSCROLLBAR_H

#include <ncurses.h>

typedef struct {
    int min_value;
    int max_value;
    int current_value;
    int thumb_pos;
    int scrollbar_height;
    int x;
    int y;
} VScrollbar;

void draw_Vscrollbar(WINDOW *win, VScrollbar *scrollbar);
void erase_Vscrollbar(WINDOW *win, VScrollbar *scrollbar);
void handle_Vscrollbar_input(int ch, VScrollbar *scrollbar);

#endif /* VSCROLLBAR_H */
