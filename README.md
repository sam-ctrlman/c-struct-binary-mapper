# c-struct-binary-mapper
Learn low-level memory concepts by building a C Struct to Binary Mapper that bypasses the OS to decode raw hard drive bytes directly.



# Bare-Metal File System Decoder

Have you ever wondered how an operating system actually reads a hard drive? 

When Linus Torvalds was first building the Linux kernel, he needed a way to read files from his hard drive. Instead of relying on an existing OS to do it for him, he wrote a low-level driver that looked at the raw 1s and 0s on the disk and decoded the file system from scratch.

This repository is a hands-on learning artifact that recreates that exact experience. We create a "virtual" floppy disk, format it with the ancient FAT12 file system, and use a C struct to bypass the operating system and read the raw binary boot sector directly.

## Prerequisites
To run this workshop, you need a Linux or macOS environment with a C compiler and the tools to format a FAT file system.

* `gcc` (or `clang`)
* `dosfstools` (provides the `mkfs.fat` command)

## How to Run It

If you have `make` installed, you can build the virtual drive, compile the code, and run the decoder all in one command:

```bash
make run
```


If you prefer to do it manually step-by-step:
1. Create and format the virtual hard drive:

```bash
make run
```

#The "Aha!" Moment: How It Works

Normally, programs ask the OS Kernel to read files for them. This program bypasses the Kernel's file explorer entirely.

If you look at the floppy.img file with a hex editor (xxd -l 128 floppy.img), it just looks like a wall of random numbers.

In driver.c, we define a rigid struct BootSector that perfectly matches the mathematical blueprint of a FAT12 disk. When we use fread(), C takes that struct and stamps it down over the raw binary chaos like a stencil. The chaotic bytes instantly snap into readable C variables (like bytes_per_sector or volume_label), proving that files and folders are just illusions painted over raw memory offsets!
