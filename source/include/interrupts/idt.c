#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "idt.h"
#include "isr.h"

extern void load_idt();

struct idt_descriptor {
	unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__ ((packed));

struct idt_pointer {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

void init_pic(void) {
	uint8_t A1, A2;

    A1 = inportb(PIC1_DATA);
    A2 = inportb(PIC2_DATA);

    outportb(PIC1_COMMAND, ICW1);
    outportb(PIC2_COMMAND, ICW1);

    outportb(PIC1_DATA, 0x20);
    outportb(PIC2_DATA, 0x28);

    outportb(PIC1_DATA, 4);
    outportb(PIC2_DATA, 2);

    outportb(PIC1_DATA, ICW4_8086);
    outportb(PIC2_DATA, ICW4_8086);

    outportb(PIC1_DATA, A1);
    outportb(PIC2_DATA, A2);
}

struct idt_pointer kernel_idt_pointer;
struct idt_descriptor kernel_idt[IDT_SIZE];

void init_idt_descriptor(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    kernel_idt[num].base_lo = (base & 0xFFFF);
    kernel_idt[num].base_hi = (base >> 16) & 0xFFFF;
    kernel_idt[num].sel = sel;
    kernel_idt[num].always0 = 0;
    kernel_idt[num].flags = flags;
}

void init_idt(void) {
    kernel_idt_pointer.limit = (sizeof (struct idt_descriptor) * 256) - 1;
    kernel_idt_pointer.base = &kernel_idt;
    memset(&kernel_idt, 0, sizeof(struct idt_descriptor) * 256);
    load_idt();
}


