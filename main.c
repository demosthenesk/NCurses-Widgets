#include <ncurses.h>
#include "radiobuttons.h"

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Initialize color if supported
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_BLACK, COLOR_YELLOW); // Color for highlight mode
        init_pair(3, COLOR_WHITE, COLOR_RED); // Color for focused mode
    }

    // Create an array of RadioButton structs
    RadioButton radioButtons[] = {
        {"Option 1", 0, 0},
        {"Option 2", 0, 0},
        {"Option 3", 0, 0}
    };

    int numButtons = sizeof(radioButtons) / sizeof(radioButtons[0]);

    // Calculate the size of the window for the radio buttons
    int winHeight = numButtons + 2; // Add 2 for the border
    int winWidth = 30;

    // Create a new window for the radio buttons
    WINDOW *radioWin = newwin(winHeight, winWidth, (LINES - winHeight) / 2, (COLS - winWidth) / 2);

    // Enable keypad input for the radio window
    keypad(radioWin, TRUE);

    int ch;
    int selectedOption = -1;
    int focusedOption = 0; // Initial focus on the first option
    updateFocus(radioButtons, numButtons, focusedOption);

    // Update radiobuttons
    updateRadioWindow(radioWin, radioButtons, numButtons);
    wrefresh(radioWin);

    while ((ch = wgetch(radioWin)) != 'q') {

        // Update radiobuttons
        updateRadioWindow(radioWin, radioButtons, numButtons);
        wrefresh(radioWin);

        // Update the selected option or focus based on user input
        switch (ch) {
            case KEY_DOWN:
                focusedOption = (focusedOption + 1) % numButtons;
                updateFocus(radioButtons, numButtons, focusedOption);
                break;
            case KEY_UP:
                focusedOption = (focusedOption - 1 + numButtons) % numButtons;
                updateFocus(radioButtons, numButtons, focusedOption);
                break;
            case ' ': // Spacebar
            case '\n':
                selectedOption = focusedOption;
                for (int i = 0; i < numButtons; i++) {
                    radioButtons[i].selected = (i == selectedOption);
                }
                break;
        }

        // Update radiobuttons
        updateRadioWindow(radioWin, radioButtons, numButtons);
        wrefresh(radioWin);
    }

    // Clean up
    delwin(radioWin);
    endwin();
    return 0;
}
