#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "textbox.h"

#define MAX_TEXTBOXES 3

int main() {
    TEXTBOX textboxes[MAX_TEXTBOXES] = {
        {NULL, 0, 30, 3, 5, 10}, // Textbox 1 (height, width, starty, startx)
        {NULL, 0, 30, 3, 8, 30}, // Textbox 2 (height, width, starty, startx)
        {NULL, 0, 30, 3, 11, 50} // Textbox 3 (height, width, starty, startx)
    };

    // Allocate memory for textbox texts
    for (int i = 0; i < MAX_TEXTBOXES; i++) {
        textboxes[i].text = (char *)malloc((textboxes[i].width + 1) * sizeof(char)); // Default width + 1 for null terminator
        textboxes[i].text[0] = '\0'; // Initialize text as empty
    }

    // Initialize NCurses
    initscr();
    cbreak(); // Line buffering disabled
    noecho(); // Don't echo while we do getch
    keypad(stdscr, TRUE); // Enable keyboard mapping

    // Create windows for the textboxes and draw them for the first time
    WINDOW *textboxWins[MAX_TEXTBOXES];
    for (int i = 0; i < MAX_TEXTBOXES; i++) {
        textboxWins[i] = newwin(textboxes[i].height, textboxes[i].width, textboxes[i].starty, textboxes[i].startx);
        keypad(textboxWins[i], TRUE); // Enable keyboard mapping for each textbox window
        scrollok(textboxWins[i], TRUE);
    }
    refresh();

    // Enable scrolling for each textbox window
    int active_textbox_index;
    for (int i = 0; i < MAX_TEXTBOXES; i++) {
        // Redraw the textbox1
        werase(textboxWins[i]);
        draw_textbox(textboxWins[i], &textboxes[i]);
        wrefresh(textboxWins[i]);
        // Set initial active textbox
        active_textbox_index = i;
    }


    // Loop for getting input
    int ch;
    while ((ch = getch()) != '\n') {
        // Handle input for the active textbox
        handle_textbox_input(&textboxes[active_textbox_index], ch);

        // Check if the focus should be switched to another textbox
        if (ch == '\t') { // Tab key pressed
            active_textbox_index = (active_textbox_index + 1) % MAX_TEXTBOXES;
        }

        // Redraw the active textbox
        werase(textboxWins[active_textbox_index]);
        draw_textbox(textboxWins[active_textbox_index], &textboxes[active_textbox_index]);
        wrefresh(textboxWins[active_textbox_index]);

    }

    // Print the entered text for each textbox
    for (int i = 0; i < MAX_TEXTBOXES; i++) {
        printw("Textbox%d entered: %s\n", i + 1, textboxes[i].text);
    }
    getch();

    // Clean up
    for (int i = 0; i < MAX_TEXTBOXES; i++) {
        delwin(textboxWins[i]);
        free(textboxes[i].text);
    }
    endwin();
    return 0;
}
