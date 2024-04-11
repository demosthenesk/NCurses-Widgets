#include <stdlib.h>
#include "hscrollbar.h"
#include <string.h>

#define NUM_HSCROLLBARS 2

// Function to initialize the scrollable window
HScrollableWindow *initHScrollableWindow(int height, int width, int y, int x, char *content) {
    HScrollableWindow *sw = malloc(sizeof(HScrollableWindow));
    sw->win = newwin(height, width, y, x);
    sw->content = strdup(content);
    sw->contentWidth = strlen(content);
    sw->scrollPos = 0;
    sw->isActive = false;
    return sw;
}

// Function to free resources used by the scrollable window
void freeHScrollableWindow(HScrollableWindow *sw) {
    delwin(sw->win);
    free(sw->content);
    free(sw);
}

// Function to draw the content and scrollbar of the scrollable window
void drawHScrollableWindow(HScrollableWindow *sw) {
    // Clear window
    werase(sw->win);

    // Draw content
    mvwprintw(sw->win, 1, 1, "%s", sw->content + sw->scrollPos);

    // Horizontal scrollbar
    int windowHeight, windowWidth;
    getmaxyx(sw->win, windowHeight, windowWidth);
    int scrollbarWidth = windowWidth - 2; // Width of the scrollbar excluding borders
    int scrollbarPos = (sw->scrollPos * scrollbarWidth) / sw->contentWidth;
    for (int i = 0; i < scrollbarWidth; ++i) {
        mvwaddch(sw->win, windowHeight - 2, i + 1, ' ');
    }
    mvwaddch(sw->win, windowHeight - 2, scrollbarPos + 1, ACS_BLOCK);

    // Draw window border
    box(sw->win, 0, 0);

    // Refresh window
    wrefresh(sw->win);
}

// Function to handle user input for the active window
void handleHScrollBarInput(HScrollableWindow *windows[], int *activeWindowIndex, int ch) {
    switch (ch) {
        case KEY_LEFT:
            if (windows[*activeWindowIndex]->scrollPos > 0) {
                windows[*activeWindowIndex]->scrollPos--;
            }
            break;
        case KEY_RIGHT:
            if (windows[*activeWindowIndex]->scrollPos < windows[*activeWindowIndex]->contentWidth - getmaxx(windows[*activeWindowIndex]->win) + 2) {
                windows[*activeWindowIndex]->scrollPos++;
            }
            break;
        case '\t': // Tab
            windows[*activeWindowIndex]->isActive = false;
            *activeWindowIndex = (*activeWindowIndex + 1) % NUM_HSCROLLBARS;
            windows[*activeWindowIndex]->isActive = true;
            break;
        case 'q': // Quit
        case 'Q':
            for (int i = 0; i < NUM_HSCROLLBARS; i++) {
                freeHScrollableWindow(windows[i]);
            }
            endwin();
            exit(0);
        default:
            break;
    }
}
