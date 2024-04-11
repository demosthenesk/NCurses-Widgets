#ifndef HSCROLLBAR_H
#define HSCROLLBAR_H

#include <ncurses.h>
#include <stdbool.h>

// Struct to hold window and scrollbar information
typedef struct {
    WINDOW *win;
    char *content;
    int contentWidth;
    int scrollPos;
    bool isActive;
} HScrollableWindow;

// Function prototypes
HScrollableWindow *initHScrollableWindow(int height, int width, int y, int x, char *content);
void freeHScrollableWindow(HScrollableWindow *sw);
void drawHScrollableWindow(HScrollableWindow *sw);
void handleHScrollBarInput(HScrollableWindow *windows[], int *activeWindowIndex, int ch);

#endif /* HSCROLLBAR_H */
