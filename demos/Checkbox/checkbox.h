#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <ncurses.h>
#include <stdbool.h>

#define MAX_CHECKBOXES 5

typedef struct {
    int row;
    int col;
    bool checked;
    bool focused;
} Checkbox;

WINDOW *create_window();
void init_checkboxes(Checkbox *checkboxes, int num_checkboxes);
void draw_checkboxes(WINDOW *win, Checkbox *checkboxes, int num_checkboxes);
int handle_checkboxes_input(Checkbox *checkboxes, int num_checkboxes);
void draw_checkbox(WINDOW *win, const Checkbox *checkbox);

#endif /* CHECKBOX_H */
