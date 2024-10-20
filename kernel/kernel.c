#include <stdint.h>
#include "display_manager.h"

void kernel_main(void) {
    clear_screen();  // Clear the screen
    print_string("LoteOS V-0-1");
    print_string("END MY SUFFERING.");  // Use the display manager to print
    
    // Prevent returning to GRUB
    while (1) {
        __asm__("hlt");  // Halt CPU to save power until the next interrupt
    }
}
