#include <include/common/common.h>
#include "isr.h"

isr g_interrupt_handlers[NO_INTERRUPT_HANDLERS];

char *exception_messages[32] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Device Not Available (No Math Coprocessor)",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Unknown Interrupt (intel reserved)",
    "x87 FPU Floating-Point Error (Math Fault)",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void eoi_pic(uint8_t irq) {
    if(irq >= 0x28)
        outportb(PIC2, PIC_EOI);
    outportb(PIC1, PIC_EOI);
}

void isr_register_interrupt_handler(int num, isr handler) {
    if (num < NO_INTERRUPT_HANDLERS)
        g_interrupt_handlers[num] = handler;
}

void isr_end_interrupt(int num) {
    eoi_pic(num);
}

void isr_irq_handler(registers *reg) {
    if (g_interrupt_handlers[reg->int_no] != NULL) {
        isr handler = g_interrupt_handlers[reg->int_no];
        handler(reg);
    }
    eoi_pic(reg->int_no);
}

void isr_exception_handler(registers reg) {
    if (reg.int_no < 32) {
        clear_screen(0, 0, 0);
        put_string(exception_messages[reg.int_no], 15, 15, 255, 0, 0);
        for (;;)
            ;
    }
    if (g_interrupt_handlers[reg.int_no] != NULL) {
        isr handler = g_interrupt_handlers[reg.int_no];
        handler(&reg);
    }
}