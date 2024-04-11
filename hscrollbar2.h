#ifndef HSCROLLBAR2_H
#define HSCROLLBAR2_H

typedef struct {
    int current_value;
    int min_value;
    int max_value;
    int bar_x;
    int scrollbar_x;
    int scrollbar_width;
    int max_x;
    int max_y;
} HScrollbar;

void init_hscrollbar(HScrollbar *scrollbar, int min_value, int max_value, int max_x, int max_y);
void update_hscrollbar(HScrollbar *scrollbar);
void draw_hscrollbar(HScrollbar *scrollbar);

#endif /* HSCROLLBAR2_H */
