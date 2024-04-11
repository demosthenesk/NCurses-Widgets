#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

typedef struct {
    int y, x; // Position
    char* label;
    int height, width; // Height and width properties
    bool highlighted;
    short normal_color_pair; // Color pair for normal state
    short highlight_color_pair; // Color pair for highlighted state
    void (*callback)(); // Function pointer for callback
} Button;

Button* create_button(int y, int x, int height, int width, char* label, short normal_color_pair, short highlight_color_pair, void (*callback)());
void draw_button(Button* button);
bool is_inside(Button* button, int y, int x);
void button_handle_mouse(Button* button);

#endif /* BUTTON_H */
