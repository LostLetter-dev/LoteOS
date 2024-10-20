// display_manager.h
#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

void clear_screen();
void print_char(char c);
void print_string(const char* str);

void set_resolution(int width, int height);
void switch_tab(int tab);

void draw_vertical_split();
void make_tab();

#endif // DISPLAY_MANAGER_H
