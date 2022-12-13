#include <include/common/common.h>
#include "isr.h"

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
    "SIMD Floating-Point exception",
    "Virtualization exception",
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

void fault_handler(registers *r) {
}

void init_isr() {
    init_idt_descriptor(0, (unsigned)exception0, 0x08, 0x8E);
    init_idt_descriptor(1, (unsigned)exception1, 0x08, 0x8E);
    init_idt_descriptor(2, (unsigned)exception2, 0x08, 0x8E);
    init_idt_descriptor(3, (unsigned)exception3, 0x08, 0x8E);
    init_idt_descriptor(4, (unsigned)exception4, 0x08, 0x8E);
    init_idt_descriptor(5, (unsigned)exception5, 0x08, 0x8E);
    init_idt_descriptor(6, (unsigned)exception6, 0x08, 0x8E);
    init_idt_descriptor(7, (unsigned)exception7, 0x08, 0x8E);
    init_idt_descriptor(8, (unsigned)exception8, 0x08, 0x8E);
    init_idt_descriptor(9, (unsigned)exception9, 0x08, 0x8E);
    init_idt_descriptor(10, (unsigned)exception10, 0x08, 0x8E);
    init_idt_descriptor(11, (unsigned)exception11, 0x08, 0x8E);
    init_idt_descriptor(12, (unsigned)exception12, 0x08, 0x8E);
    init_idt_descriptor(13, (unsigned)exception13, 0x08, 0x8E);
    init_idt_descriptor(14, (unsigned)exception14, 0x08, 0x8E);
    init_idt_descriptor(15, (unsigned)exception15, 0x08, 0x8E);
    init_idt_descriptor(16, (unsigned)exception16, 0x08, 0x8E);
    init_idt_descriptor(17, (unsigned)exception17, 0x08, 0x8E);
    init_idt_descriptor(18, (unsigned)exception18, 0x08, 0x8E);
    init_idt_descriptor(19, (unsigned)exception19, 0x08, 0x8E);
    init_idt_descriptor(20, (unsigned)exception20, 0x08, 0x8E);
    init_idt_descriptor(21, (unsigned)exception21, 0x08, 0x8E);
    init_idt_descriptor(22, (unsigned)exception22, 0x08, 0x8E);
    init_idt_descriptor(23, (unsigned)exception23, 0x08, 0x8E);
    init_idt_descriptor(24, (unsigned)exception24, 0x08, 0x8E);
    init_idt_descriptor(25, (unsigned)exception25, 0x08, 0x8E);
    init_idt_descriptor(26, (unsigned)exception26, 0x08, 0x8E);
    init_idt_descriptor(27, (unsigned)exception27, 0x08, 0x8E);
    init_idt_descriptor(28, (unsigned)exception28, 0x08, 0x8E);
    init_idt_descriptor(29, (unsigned)exception29, 0x08, 0x8E);
    init_idt_descriptor(30, (unsigned)exception30, 0x08, 0x8E);
    init_idt_descriptor(31, (unsigned)exception31, 0x08, 0x8E);
}

void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void (*handler)(registers *r)) {
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) {
    irq_routines[irq] = 0;
}

void remap_irq(void) {
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void init_irq() {
    remap_irq();

    init_idt_descriptor(32, (uint32_t)irq0, 0x08, 0x8E);
    init_idt_descriptor(33, (uint32_t)irq1, 0x08, 0x8E);
    init_idt_descriptor(34, (uint32_t)irq2, 0x08, 0x8E);
    init_idt_descriptor(35, (uint32_t)irq3, 0x08, 0x8E);
    init_idt_descriptor(36, (uint32_t)irq4, 0x08, 0x8E);
    init_idt_descriptor(37, (uint32_t)irq5, 0x08, 0x8E);
    init_idt_descriptor(38, (uint32_t)irq6, 0x08, 0x8E);
    init_idt_descriptor(39, (uint32_t)irq7, 0x08, 0x8E);
    init_idt_descriptor(40, (uint32_t)irq8, 0x08, 0x8E);
    init_idt_descriptor(41, (uint32_t)irq9, 0x08, 0x8E);
    init_idt_descriptor(42, (uint32_t)irq10, 0x08, 0x8E);
    init_idt_descriptor(43, (uint32_t)irq11, 0x08, 0x8E);
    init_idt_descriptor(44, (uint32_t)irq12, 0x08, 0x8E);
    init_idt_descriptor(45, (uint32_t)irq13, 0x08, 0x8E);
    init_idt_descriptor(46, (uint32_t)irq14, 0x08, 0x8E);
    init_idt_descriptor(47, (uint32_t)irq15, 0x08, 0x8E);
}

void irq_handler(registers *r) {
    void (*handler)(registers *r);
    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }
    if (r->int_no >= 40)
    {
        outportb(0xA0, 0x20);
    }

    outportb(0x20, 0x20);
}

void timer_phase(int hz) {
    int divisor = 1193180 / hz;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}

int timer_ticks = 0;

void timer_handler(registers* r) {
    timer_ticks++;
    if (timer_ticks % 18 == 0)
    {
        // DrawString("Tick!", 15, 15, 0xFFFFFF);
    }
}

void init_timer() {
    irq_install_handler(0, timer_handler);
}