#include "checkbox.h"

WINDOW *create_window() {
    int window_height = 10;
    int window_width = 20;
    int window_y = (LINES - window_height) / 2;
    int window_x = (COLS - window_width) / 2;
    WINDOW *win = newwin(window_height, window_width, window_y, window_x);
    box(win, 0, 0); // Draw a border around the window
    wrefresh(win); // Refresh the window to show the border
    return win;
}

void draw_checkbox(WINDOW *win, const Checkbox *checkbox) {
    // Draw checkbox
    if (checkbox->focused) {
        wattron(win, A_STANDOUT); // Highlight focused checkbox
    }
    mvwprintw(win, checkbox->row, checkbox->col, "[%c]", checkbox->checked ? 'X' : ' ');
    mvwprintw(win, checkbox->row, checkbox->col + 3, " Checkbox");
    if (checkbox->focused) {
        wattroff(win, A_STANDOUT);
    }
}

void init_checkboxes(Checkbox *checkboxes, int num_checkboxes) {
    for (int i = 0; i < num_checkboxes; ++i) {
        checkboxes[i].row = i + 1;
        checkboxes[i].col = 2;
        checkboxes[i].checked = false;
        checkboxes[i].focused = (i == 0); // Focus the first checkbox initially
    }
}

void draw_checkboxes(WINDOW *win, Checkbox *checkboxes, int num_checkboxes) {
    // Clear the window
    werase(win);

    // Draw checkboxes within the window
    for (int i = 0; i < num_checkboxes; ++i) {
        draw_checkbox(win, &checkboxes[i]);
    }

    // Draw border around the window
    box(win, 0, 0);

    // Refresh the window to show updates
    wrefresh(win);
}

int handle_checkboxes_input(Checkbox *checkboxes, int num_checkboxes) {
    int ch = getch();
    switch(ch) {
        case KEY_UP:
            for (int i = 0; i < num_checkboxes; ++i) {
                if (checkboxes[i].focused) {
                    checkboxes[i].focused = false;
                    checkboxes[(i - 1 + num_checkboxes) % num_checkboxes].focused = true;
                    break;
                }
            }
            break;
        case KEY_DOWN:
            for (int i = 0; i < num_checkboxes; ++i) {
                if (checkboxes[i].focused) {
                    checkboxes[i].focused = false;
                    checkboxes[(i + 1) % num_checkboxes].focused = true;
                    break;
                }
            }
            break;
        case ' ':
            for (int i = 0; i < num_checkboxes; ++i) {
                if (checkboxes[i].focused) {
                    checkboxes[i].checked = !checkboxes[i].checked;
                    break;
                }
            }
            break;
    }
    return ch;
}
