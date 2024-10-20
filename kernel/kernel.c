#include <stdint.h>
#include "display_manager.h"

void kernel_main(void) {
    set_resolution(80, 25);  // Set screen resolution to 80x25
    clear_screen();          // Clear the screen

    print_string("LoteOS V-0-1");

    // Dynamically create tabs
    make_tab();  // Create the first tab

    make_tab();  // Create the second tab

    // Switch between tabs and print
    switch_tab(0);  // Go back to Tab 1
    print_string("LoteOS V-0-1");
    print_string("This shouldn't make any impact on tab 2");
    print_string("This shouldn't make any impact on tab 2");
    print_string("This shouldn't make any impact on tab 2");
    print_string("This shouldn't make any impact on tab 2");

    switch_tab(1);  // Switch to Tab 2
    print_string("STFU tab 1...");

    // Prevent returning to GRUB
    while (1) {
        __asm__("hlt");  // Halt CPU to save power until the
    }
}
