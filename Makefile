CC = gcc
CFLAGS = -Wall -Wextra

all: disk driver

# Create the virtual hard drive and format it as FAT12
disk:
	@echo "Creating virtual 1.44MB floppy disk..."
	dd if=/dev/zero of=floppy.img bs=1024 count=1440 2>/dev/null
	@echo "Formatting disk as FAT12..."
	mkfs.fat -F 12 -n "MYWORKSHOP" floppy.img

# Compile the C program
driver: driver.c
	$(CC) $(CFLAGS) -o driver driver.c

# Run the compiled program
run: all
	./driver

# Clean up generated files
clean:
	rm -f driver floppy.img

.PHONY: all disk driver run clean
