#include "listbox.h"

// Function to initialize a listbox
void initListBox(struct ListBox* listBox) {
    listBox->selected = 0;
    listBox->max_items = 10;
    listBox->visible_items = 5; // Number of visible items
    listBox->start_index = 0;
    listBox->items[0] = "Item 1";
    listBox->items[1] = "Item 2";
    listBox->items[2] = "Item 3";
    listBox->items[3] = "Item 4";
    listBox->items[4] = "Item 5";
    listBox->items[5] = "Item 6";
    listBox->items[6] = "Item 7";
    listBox->items[7] = "Item 8";
    listBox->items[8] = "Item 9";
    listBox->items[9] = "Item 10";
}

// Function to display the listbox within a box
void displayListBox(struct ListBox* listBox, WINDOW* win) {
    // Clear the window
    werase(win);

    // Draw a box around the window
    box(win, 0, 0);

    // Display the listbox inside the box
    for (int i = listBox->start_index; i < listBox->start_index + listBox->visible_items && i < listBox->max_items; i++) {
        int display_index = i - listBox->start_index + 1;
        if (i == listBox->selected) {
            wattron(win, A_REVERSE);
        }
        mvwprintw(win, display_index, 1, "%s", listBox->items[i]);
        if (i == listBox->selected) {
            wattroff(win, A_REVERSE);
        }
    }

    // Calculate scrollbar parameters
    int total_items = listBox->max_items;
    int total_visible = listBox->visible_items;
    int scrollbar_height = (total_visible * total_visible) / total_items;
    int scrollbar_position = (listBox->start_index * total_visible) / total_items;

    // Draw the scrollbar
    for (int i = 0; i < total_visible; i++) {
        mvwprintw(win, i + 1, 20, "|");
    }
    for (int i = scrollbar_position; i < scrollbar_position + scrollbar_height; i++) {
        mvwprintw(win, i + 1, 20, "#");
    }

    // Refresh the window
    wrefresh(win);
}

// Function to handle user input
void handleListboxInput(int ch, struct ListBox* listBox) {
    // Move selection up
    if (ch == KEY_UP) {
        if (listBox->selected > 0) {
            listBox->selected--;
            if (listBox->selected < listBox->start_index) {
                listBox->start_index--;
            }
        }
    }
    // Move selection down
    else if (ch == KEY_DOWN) {
        if (listBox->selected < listBox->max_items - 1) {
            listBox->selected++;
            if (listBox->selected >= listBox->start_index + listBox->visible_items) {
                listBox->start_index++;
            }
        }
    }
}
