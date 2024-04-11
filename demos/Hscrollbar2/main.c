#include <ncurses.h>
#include "hscrollbar2.h"

#define MIN_VALUE 0
#define MAX_VALUE 100

int main() {
    HScrollbar scrollbar;
    int ch;

    // Initialize ncurses
    initscr();
    cbreak(); // Disable line buffering
    noecho(); // Don't echo input
    keypad(stdscr, TRUE); // Enable keypad input
    curs_set(0); // Hide cursor

    // Get screen dimensions
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    // Initialize scrollbar
    init_hscrollbar(&scrollbar, MIN_VALUE, MAX_VALUE, max_x, max_y);
    // Draw scrollbar
    draw_hscrollbar(&scrollbar);

    while ((ch = getch()) != 'q') { // Exit loop on 'q' key
        switch (ch) {
            case KEY_LEFT:
                if (scrollbar.current_value > scrollbar.min_value) {
                    scrollbar.current_value--;
                    update_hscrollbar(&scrollbar);
                }
                break;
            case KEY_RIGHT:
                if (scrollbar.current_value < scrollbar.max_value) {
                    scrollbar.current_value++;
                    update_hscrollbar(&scrollbar);
                }
                break;
        }

        clear();

        // Draw scrollbar
        draw_hscrollbar(&scrollbar);

        // Print current value
        mvprintw(scrollbar.max_y / 2 + 2, max_x / 2 - 5, "Value: %d", scrollbar.current_value);

        // Refresh the screen
        refresh();
    }

    endwin(); // End ncurses mode

    return 0;
}
