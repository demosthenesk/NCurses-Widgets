#include <ncurses.h>
#include "listbox.h"

int main() {
    struct ListBox listBox;
    int ch;

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Create a new window for the listbox
    WINDOW* listBoxWin = newwin(7, 22, 2, 2);

    // Initialize the listbox
    initListBox(&listBox);

    // Display the listbox in the window
    listBox.selected = 0;
    displayListBox(&listBox, listBoxWin);
    refresh();

    // Main loop
    while (1) {
        // Display the listbox in the window
        displayListBox(&listBox, listBoxWin);
        ch = getch();

        // Handle user input
        handleListboxInput(ch, &listBox);

        // Quit program
        if (ch == 'q') {
            break;
        }
    }

    // Clean up ncurses
    delwin(listBoxWin);
    endwin();
    return 0;
}
