#include "textbox.h"

void draw_textbox(WINDOW *win, TEXTBOX *textbox) {
    // Draw the textbox outline
    box(win, 0, 0);

    // Print the text inside the textbox
    mvwprintw(win, 1, 1, "%-*s", textbox->width - 2, textbox->text);

    // Move the cursor to its position
    wmove(win, 1, 1 + textbox->cursor_pos);
    wrefresh(win);
}

void handle_textbox_input(TEXTBOX *textbox, int ch) {
    switch (ch) {
        case KEY_LEFT:
            if (textbox->cursor_pos > 0)
                textbox->cursor_pos--;
            break;
        case KEY_RIGHT:
            if (textbox->text[textbox->cursor_pos] != '\0')
                textbox->cursor_pos++;
            break;
        case KEY_BACKSPACE:
            if (textbox->cursor_pos > 0) {
                memmove(&(textbox->text[textbox->cursor_pos - 1]), &(textbox->text[textbox->cursor_pos]), strlen(textbox->text) - textbox->cursor_pos + 1);
                textbox->cursor_pos--;
            }
            break;
        default:
            if (ch >= 32 && ch <= 126 && strlen(textbox->text) < textbox->width - 2) {
                memmove(&(textbox->text[textbox->cursor_pos + 1]), &(textbox->text[textbox->cursor_pos]), strlen(textbox->text) - textbox->cursor_pos + 1);
                textbox->text[textbox->cursor_pos] = ch;
                textbox->cursor_pos++;
            }
            break;
    }
}
