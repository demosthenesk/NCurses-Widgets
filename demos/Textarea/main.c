#include <ncurses.h>
#include <string.h>
#include "textarea.h"

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Create text area window
    TextArea text_area;
    text_area.width = 50;
    text_area.height = 10;

    WINDOW *text_area_win = newwin(text_area.height + 2, text_area.width + 2, 1, 1);
    keypad(text_area_win, TRUE);

    // Initialize text area content
    memset(text_area.text, ' ', sizeof(text_area.text));
    text_area.cursor_x = 0;
    text_area.cursor_y = 0;

    // Display initial text area
    draw_text_area(text_area_win, &text_area);

    // Main loop
    int ch;
    while ((ch = wgetch(text_area_win)) != 27) //27 = ESCAPE ASCII Code
    {
        switch(ch) {
            case KEY_DC:
                // Delete the character at current cursor position
                text_area.text[text_area.cursor_y][text_area.cursor_x] = ' ';
                break;
            case KEY_BACKSPACE:
            case 127: // 127 is the ASCII value for BACKSPACE
                if (text_area.cursor_x > 0 || text_area.cursor_y > 0) {
                    if (text_area.cursor_x == 0) {
                        // If cursor is at beginning of line, move it to end of previous line
                        text_area.cursor_x = text_area.width - 2;
                        text_area.cursor_y--;
                    } else {
                        // Delete the character at current cursor position
                        text_area.text[text_area.cursor_y][text_area.cursor_x - 1] = ' ';
                        text_area.cursor_x--;
                    }
                }
                break;
            case KEY_UP:
                if (text_area.cursor_y > 0)
                    text_area.cursor_y--;
                break;
            case KEY_DOWN:
                if (text_area.cursor_y < text_area.height - 1)
                    text_area.cursor_y++;
                break;
            case KEY_LEFT:
                if (text_area.cursor_x > 1)
                    text_area.cursor_x--;
                break;
            case KEY_RIGHT:
                if (text_area.cursor_x < text_area.width - 2)
                    text_area.cursor_x++;
                break;
            default:
                if (ch >= 32 && ch <= 126) { // printable ASCII characters
                    text_area.text[text_area.cursor_y][text_area.cursor_x - 1] = ch;
                    if (text_area.cursor_x < text_area.width - 2) {
                        text_area.cursor_x++;
                    } else if (text_area.cursor_y < text_area.height - 1) {
                        text_area.cursor_x = 1;
                        text_area.cursor_y++;
                    }
                }
                break;
        }

        // Redraw text area with updated cursor position
        draw_text_area(text_area_win, &text_area);
    }

    // Clean up
    delwin(text_area_win);
    endwin();

    return 0;
}
