// multiboot.c
#include "multiboot.h"

__attribute__((section(".multiboot_header"))) 
struct multiboot_header {
    unsigned int magic;
    unsigned int flags;
    unsigned int checksum;
} multiboot_hdr = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_HEADER_CHECKSUM
};
