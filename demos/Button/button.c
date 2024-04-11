#include "button.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

Button* create_button(int y, int x, int height, int width, char* label, short normal_color_pair, short highlight_color_pair, void (*callback)()) {
    Button* button = (Button*)malloc(sizeof(Button));
    button->y = y;
    button->x = x;
    button->height = height;
    button->width = width;
    button->label = strdup(label); // Duplicate the label string
    button->highlighted = false;
    button->normal_color_pair = normal_color_pair;
    button->highlight_color_pair = highlight_color_pair;
    button->callback = callback;
    return button;
}

void draw_button(Button* button) {
    if (button->highlighted)
        attron(COLOR_PAIR(button->highlight_color_pair));
    else
        attron(COLOR_PAIR(button->normal_color_pair));

    // Draw button frame
    for (int i = button->y; i < button->y + button->height; ++i) {
        mvaddch(i, button->x, ACS_VLINE);
        mvaddch(i, button->x + button->width - 1, ACS_VLINE);
    }
    for (int i = button->x; i < button->x + button->width; ++i) {
        mvaddch(button->y, i, ACS_HLINE);
        mvaddch(button->y + button->height - 1, i, ACS_HLINE);
    }
    mvaddch(button->y, button->x, ACS_ULCORNER);
    mvaddch(button->y, button->x + button->width - 1, ACS_URCORNER);
    mvaddch(button->y + button->height - 1, button->x, ACS_LLCORNER);
    mvaddch(button->y + button->height - 1, button->x + button->width - 1, ACS_LRCORNER);

    // Adjust label to fit button's width
    char filled_label[button->width + 1];
    int spaces_to_fill = button->width - strlen(button->label);
    int left_spaces = spaces_to_fill / 2;
    int right_spaces = spaces_to_fill - left_spaces;
    sprintf(filled_label, "%*s%s%*s", left_spaces, "", button->label, right_spaces, "");

    // Print filled label inside the button
    mvprintw(button->y + button->height / 2, button->x + (button->width - strlen(filled_label)) / 2, "%s", filled_label);

    if (button->highlighted)
        attroff(COLOR_PAIR(button->highlight_color_pair));
    else
        attroff(COLOR_PAIR(button->normal_color_pair));

    refresh();
}

bool is_inside(Button* button, int y, int x) {
    return (y >= button->y && y < button->y + button->height &&
            x >= button->x && x < button->x + button->width);
}

void button_handle_mouse(Button* button) {
    MEVENT event;
    int ch = getch();
    if (ch == KEY_MOUSE) {
        if (getmouse(&event) == OK) {
            // Check if the click is inside the button
            if (is_inside(button, event.y, event.x)) {
                // Handle button click here
                button->highlighted = !button->highlighted;
                draw_button(button);
                napms(700);
                button->highlighted = !button->highlighted;
                draw_button(button);

                if (button->callback != NULL) {
                    button->callback(button);
                }

            }
        }
    }
}
