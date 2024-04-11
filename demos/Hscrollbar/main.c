#include <ncurses.h>
#include <stdlib.h>
#include "hscrollbar.h"

#define NUM_HSCROLLBARS 2

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Get terminal size
    int terminalWidth, terminalHeight;
    getmaxyx(stdscr, terminalHeight, terminalWidth);

    // Define window dimensions
    int windowHeight = 4;
    int windowWidth = 15;
    int windowY = (terminalHeight - (windowHeight * NUM_HSCROLLBARS)) / 2;
    int windowX = (terminalWidth / 2) - (windowWidth / 2);

    // Create array of scrollable windows
    HScrollableWindow *hscrollableWins[NUM_HSCROLLBARS];
    for (int i = 0; i < NUM_HSCROLLBARS; i++) {
        hscrollableWins[i] = initHScrollableWindow(windowHeight, windowWidth, windowY + (i * windowHeight), windowX,
                                                 "This is a long line of text. "
                                                 "You can scroll left and right with the arrow keys.");
    }

    // Set first window active by default
    hscrollableWins[0]->isActive = true;

    // Enable keypad for each window
    for (int i = 0; i < NUM_HSCROLLBARS; i++) {
        keypad(hscrollableWins[i]->win, TRUE);
    }

    // Draw all scrollable windows
    for (int i = 0; i < NUM_HSCROLLBARS; i++) {
        drawHScrollableWindow(hscrollableWins[i]);
    }
    refresh();

    int activeWindowIndex = 0;
    // Main loop
    while (true) {
        // Draw all scrollable windows
        for (int i = 0; i < NUM_HSCROLLBARS; i++) {
            drawHScrollableWindow(hscrollableWins[i]);
        }

        // Get user input
        int ch = getch();

        // Handle user input for active window
        handleHScrollBarInput(hscrollableWins, &activeWindowIndex, ch);
    }

    // End ncurses
    endwin();
    return 0;
}
