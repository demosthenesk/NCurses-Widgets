#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "button.h"

void button_click_callback(Button *button) {
    mvprintw(LINES - 1, 0, "%s Clicked!", button->label);
    refresh();
}

int main() {
    initscr(); // Initialize ncurses
    cbreak();
    noecho();
    curs_set(0);    // Hide cursor
    keypad(stdscr, TRUE); // Enable keypad for mouse input
    mousemask(ALL_MOUSE_EVENTS, NULL); // Enable mouse events
    start_color(); // Enable color support

    // Define color pairs
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // Normal state color pair (white text on blue background)
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // Highlighted state color pair (black text on white background)

    int ch;

    // Create the first button with callback function
    Button* button1 = create_button(5, 10, 3, 20, "Button 1", 1, 2, button_click_callback);

    // Create the second button with callback function
    Button* button2 = create_button(10, 10, 3, 20, "Button 2", 1, 2, button_click_callback);

    // Draw both buttons
    draw_button(button1);
    draw_button(button2);

    // Handle mouse input
    while ((ch = getch()) != 'q') {
        button_handle_mouse(button1);
        button_handle_mouse(button2);
    }

    // Clean up
    free(button1->label);
    free(button1);
    free(button2->label);
    free(button2);
    endwin(); // End ncurses

    return 0;
}
