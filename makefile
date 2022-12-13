SRCS := $(shell find source/ -name '*.c') 
OBJS := $(SRCS:.c=.o)

.SUFFIXE: .c
%.o: %.c
	i686-elf-gcc -Isource -w -ffreestanding -g -c $< -o $@

kernel.elf: $(OBJS)
	make asm
	i686-elf-gcc -std=gnu99 -Isource/ -ffreestanding -nostdlib -T source/linker.ld $(OBJS) boot.o interrupts.o idt.o -o $@ -lgcc

clean:
	rm -f $(OBJS)
	rm -f system/boot/kernel.elf
	rm -f *.o
	rm -f *.elf
	rm -f *.iso

iso:
	cp kernel.elf system/boot/
	grub-mkrescue system -o GameStationNT.iso

asm:
	nasm -f elf source/boot/boot.asm -o boot.o
	nasm source/include/interrupts/interrupts.asm -f elf32 -o interrupts.o
	nasm source/include/interrupts/idt.asm -f elf32 -o idt.o

run: $(KERNEL_DISK)
	make iso
	qemu-system-i386 -m 2048M -enable-kvm -cdrom ./GameStationNT.iso
