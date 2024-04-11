#include <ncurses.h>
#include "checkbox.h"

int main() {
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Don't echo input
    keypad(stdscr, TRUE); // Enable keypad for arrow keys

    // Create checkboxes
    Checkbox checkboxes[MAX_CHECKBOXES];
    int num_checkboxes = 4;
    init_checkboxes(checkboxes, num_checkboxes);

    // Create a window
    WINDOW *win = create_window();
    keypad(win, TRUE); // Enable keypad for arrow keys

    //Draw checkboxes for first time
    draw_checkboxes(win, checkboxes, num_checkboxes);
    refresh();

    // Main loop
    int ch;
    do {
        draw_checkboxes(win, checkboxes, num_checkboxes);
        ch = handle_checkboxes_input(checkboxes, num_checkboxes);
    } while (ch != 'q');

    // Cleanup
    delwin(win);
    endwin(); // End ncurses

    return 0;
}
