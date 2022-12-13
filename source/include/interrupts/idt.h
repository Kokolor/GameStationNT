#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <include/common/common.h>
// #include "Isr.h"

#define IDT_BASE  0x800
#define IDT_SIZE  0xFF
#define IDT_GATE  0x8E00

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1 + 1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2 + 1)

#define PIC_EOI         0x20

#define ICW1            0x11
#define ICW4_8086       0x01

struct idt_descriptor;
struct idt_pointer;

void init_pic(void);
void init_idt_descriptor(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void init_idt(void);
