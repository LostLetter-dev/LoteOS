# Makefile for MyKernelProject

# Compiler and linker
CC = gcc
LD = ld

# Flags
CFLAGS = -m32 -ffreestanding -I./kernel
LDFLAGS = -m elf_i386 -T kernel/linker.ld

# Output binary and ISO
OUTPUT = kernel.bin
ISO_OUTPUT = kernel.iso

# Source files
KERNEL_SRC = kernel/kernel.c kernel/multiboot.c kernel/display_manager.c

# GRUB config
GRUB_CFG = grub/grub.cfg

# Object files
OBJ = kernel.o multiboot.o display_manager.o

# Default target
all: $(OUTPUT) $(GRUB_CFG) $(ISO_OUTPUT)

# Compile the C kernel source
kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o

multiboot.o: kernel/multiboot.c
	$(CC) $(CFLAGS) -c kernel/multiboot.c -o multiboot.o

display_manager.o: kernel/display_manager.c
	$(CC) $(CFLAGS) -c kernel/display_manager.c -o display_manager.o

# Link the object files
$(OUTPUT): $(OBJ)
	$(LD) $(LDFLAGS) -o $(OUTPUT) $(OBJ)

# Create the GRUB configuration file
$(GRUB_CFG):
	@echo "set timeout=0" > $(GRUB_CFG)
	@echo "set default=0" >> $(GRUB_CFG)
	@echo "menuentry 'My Kernel' {" >> $(GRUB_CFG)
	@echo "    multiboot /boot/kernel.bin" >> $(GRUB_CFG)
	@echo "    boot" >> $(GRUB_CFG)
	@echo "}" >> $(GRUB_CFG)

# Create the ISO image
$(ISO_OUTPUT): $(OUTPUT) $(GRUB_CFG)
	mkdir -p iso/boot/grub
	cp $(OUTPUT) iso/boot/
	cp $(GRUB_CFG) iso/boot/grub/
	grub-mkrescue -o $(ISO_OUTPUT) iso

# Clean up
clean:
	rm -f *.o $(OUTPUT) $(GRUB_CFG) iso/boot/kernel.bin iso/boot/grub/grub.cfg iso/boot/grub/* iso/boot/* $(ISO_OUTPUT) iso/
	rmdir iso/boot/grub iso/boot iso/ || true
