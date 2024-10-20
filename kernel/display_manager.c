// display_manager.c
#include "display_manager.h"

#define VIDEO_MEMORY 0xb8000
#define WHITE_ON_BLACK 0x07
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Clear the screen by filling it with spaces
void clear_screen() {
    char* screen = (char*)VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        screen[i * 2] = ' ';      // Character
        screen[i * 2 + 1] = WHITE_ON_BLACK; // Attribute byte
    }
}

// Print a single character
void print_char(char c) {
    static int cursor_x = 0;
    static int cursor_y = 0;

    char* screen = (char*)VIDEO_MEMORY;

    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        screen[(cursor_y * SCREEN_WIDTH + cursor_x) * 2] = c;      // Character
        screen[(cursor_y * SCREEN_WIDTH + cursor_x) * 2 + 1] = WHITE_ON_BLACK; // Attribute byte
        cursor_x++;
    }

    if (cursor_x >= SCREEN_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= SCREEN_HEIGHT) {
        cursor_x = cursor_y = 0; // Wrap around to top
        clear_screen();          // Optional: clear screen on overflow
    }
}

// Print a string followed by a newline
void print_string(const char* str) {
    while (*str) {
        print_char(*str++);
    }
    print_char('\n');  // Add a newline at the end
}
