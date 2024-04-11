// main.c

#include <ncurses.h>
#include "vscrollbar.h"

int main() {
    VScrollbar scrollbar = {0, 100, 0, 1, 10, 20, 5}; // Example x and y values
    int ch;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Main window
    WINDOW *main_win = newwin(LINES - 2, COLS, 0, 0);
    keypad(main_win, TRUE);

    // Scrollbar window
    WINDOW *scrollbar_win = newwin(scrollbar.scrollbar_height, 5, scrollbar.y, scrollbar.x);
    keypad(scrollbar_win, TRUE);

    //Draw for the first time
    draw_Vscrollbar(scrollbar_win, &scrollbar);
    refresh();

    do {
        //Print some info to user
        mvprintw(0, 0, "Use UP/DOWN arrow keys to adjust the scrollbar value. Press q to quit.");
        wrefresh(main_win);

        //Redraw scrollbar
        erase_Vscrollbar(scrollbar_win, &scrollbar);
        draw_Vscrollbar(scrollbar_win, &scrollbar);

        //Erase old value
        mvprintw(scrollbar.y + scrollbar.scrollbar_height, scrollbar.x, "Value: %s", "   ");
        //Print the new value
        mvprintw(scrollbar.y + scrollbar.scrollbar_height, scrollbar.x, "Value: %d", scrollbar.current_value);
        refresh();

        //Catch inoput
        ch = getch();
        handle_Vscrollbar_input(ch, &scrollbar);
    } while (ch != 'q');

    endwin();

    return 0;
}
