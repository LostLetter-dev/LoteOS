// display_manager.c
#include "display_manager.h"
#include <stdint.h>

#define VIDEO_MEMORY 0xb8000
#define WHITE_ON_BLACK 0x07
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAX_TABS 4  // Allow up to 4 tabs

typedef struct Tab {
    int cursor_x;
    int cursor_y;
    int tab_width;
    int tab_offset;
} Tab;

static Tab tabs[MAX_TABS];  // Stores the state for each tab
static int active_tab = -1;  // No active tab initially
static int tab_count = 0;  // Tracks the number of tabs

static int screen_width = SCREEN_WIDTH;
static int screen_height = SCREEN_HEIGHT;

// Function declarations
void draw_tabs();  // Add a forward declaration for draw_tabs()

// Clear the screen by filling it with spaces
void clear_screen() {
    char* screen = (char*)VIDEO_MEMORY;
    for (int i = 0; i < screen_width * screen_height; i++) {
        screen[i * 2] = ' ';           // Character
        screen[i * 2 + 1] = WHITE_ON_BLACK; // Attribute byte
    }
}

// Print a single character in the current tab
void print_char(char c) {
    if (active_tab == -1) return;  // No active tab, don't print

    char* screen = (char*)VIDEO_MEMORY;
    Tab* tab = &tabs[active_tab];

    if (c == '\n') {
        tab->cursor_x = 0;
        tab->cursor_y++;
    } else {
        screen[((tab->cursor_y * screen_width + tab->cursor_x + tab->tab_offset+1)) * 2] = c;  // Character
        screen[((tab->cursor_y * screen_width + tab->cursor_x + tab->tab_offset+1)) * 2 + 1] = WHITE_ON_BLACK; // Attribute byte
        tab->cursor_x++;
    }

    // Handle cursor wrapping
    if (tab->cursor_x >= tab->tab_width) {
        tab->cursor_x = 0;
        tab->cursor_y++;
    }
    if (tab->cursor_y >= screen_height) {
        tab->cursor_x = tab->cursor_y = 0;  // Wrap around to top
        clear_screen();  // replace later
    }
}

// Print a string followed by a newline
void print_string(const char* str) {
    while (*str) {
        print_char(*str++);
    }
    print_char('\n');  // Add a newline at the end
}

// Set screen resolution (currently hardcoded to 80x25)
// make this change the actual screen size of the emulator later ;p
void set_resolution(int width, int height) {
    screen_width = width;
    screen_height = height;
    clear_screen();
}

// Dynamically create a new tab
// TODO: make tabs > 2 split the bottom half of the screen than vertical.
void make_tab() {
    if (tab_count >= MAX_TABS) return;  // Prevent more than the max number of tabs

    int tab_index = tab_count;
    tab_count++;

    tabs[tab_index].cursor_x = 0;
    tabs[tab_index].cursor_y = 0;
    tabs[tab_index].tab_width = screen_width / tab_count;  // Recalculate width for all tabs
    tabs[tab_index].tab_offset = tab_index * tabs[tab_index].tab_width;  // Each tab starts at a different offset

    // Redraw screen to reflect the new tab layout
    draw_tabs();

    // Switch to the newly created tab
    active_tab = tab_index;
}

// Switch between tabs
void switch_tab(int tab) {
    if (tab >= 0 && tab < tab_count) {
        active_tab = tab;
    }
}

// Redraw tabs and vertical splits for the current tab layout
void draw_tabs() {
    clear_screen();  // Start by clearing the screen to prevent visual gore
    for (int i = 1; i < tab_count; i++) {
        draw_vertical_split(tabs[i].tab_offset);  // Draw split lines between tabs
    }
}

// Draw a vertical split at a given offset
void draw_vertical_split(int offset) {
    char* screen = (char*)VIDEO_MEMORY;
    for (int y = 0; y < screen_height; y++) {
        screen[(y * screen_width + offset) * 2] = '|';  // Character for vertical line
        screen[(y * screen_width + offset) * 2 + 1] = WHITE_ON_BLACK; // Attribute byte
    }
}
