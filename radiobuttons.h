#ifndef RADIOBUTTONS_H
#define RADIOBUTTONS_H

#include <ncurses.h>

// Define a struct to represent each radio button
typedef struct {
    char label[20];
    int selected;
    int focused;
} RadioButton;

// Function prototypes
void updateFocus(RadioButton radioButtons[], int numButtons, int focusedOption);
void updateRadioWindow(WINDOW *radioWin, RadioButton radioButtons[], int numButtons);

#endif /* RADIOBUTTONS_H */
