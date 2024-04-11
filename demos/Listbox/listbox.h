#ifndef LISTBOX_H
#define LISTBOX_H

#include <ncurses.h>

// Define a struct for listbox
struct ListBox {
    char* items[10]; // Maximum number of items
    int selected;
    int max_items; // Maximum number of items
    int start_index; // Index of the first visible item
    int visible_items; // Number of visible items
};

// Function to initialize a listbox
void initListBox(struct ListBox* listBox);

// Function to display the listbox within a box
void displayListBox(struct ListBox* listBox, WINDOW* win);

// Function to handle user input
void handleListboxInput(int ch, struct ListBox* listBox);

#endif /* LISTBOX_H */
