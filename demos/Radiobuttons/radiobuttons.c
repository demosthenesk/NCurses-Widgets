#include "radiobuttons.h"

// Function to update focus state based on current selection
void updateFocus(RadioButton radioButtons[], int numButtons, int focusedOption) {
    for (int i = 0; i < numButtons; i++) {
        radioButtons[i].focused = (i == focusedOption);
    }
}

// Function to update and display the radio buttons
void updateRadioWindow(WINDOW *radioWin, RadioButton radioButtons[], int numButtons) {
    // Clear the radio window
    werase(radioWin);

    // Draw a box around the radio window
    box(radioWin, 0, 0);

    // Display the radio button options
    for (int i = 0; i < numButtons; i++) {
        if (radioButtons[i].focused) {
            // Set color pair for focused mode
            wattron(radioWin, COLOR_PAIR(3));
        } else if (radioButtons[i].selected) {
            // Set color pair for highlight mode
            wattron(radioWin, COLOR_PAIR(2));
        }
        mvwprintw(radioWin, i + 1, 2, "[%c] %s", radioButtons[i].selected ? 'X' : ' ', radioButtons[i].label);
        if (radioButtons[i].focused || radioButtons[i].selected) {
            // Turn off color pair after printing
            wattroff(radioWin, COLOR_PAIR(2));
            wattroff(radioWin, COLOR_PAIR(3));
        }
    }
}
