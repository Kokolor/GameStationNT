#ifndef ISR_H
#define ISR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
} registers;

void fault_handler(registers *r);
void irq_handler(registers *r);
void init_isr();
void init_irq();

void irq_install_handler(int irq, void (*handler)(registers *r));
void irq_uninstall_handler(int irq);

void init_timer();

extern void exception0();
extern void exception1();
extern void exception2();
extern void exception3();
extern void exception4();
extern void exception5();
extern void exception6();
extern void exception7();
extern void exception8();
extern void exception9();
extern void exception10();
extern void exception11();
extern void exception12();
extern void exception13();
extern void exception14();
extern void exception15();
extern void exception16();
extern void exception17();
extern void exception18();
extern void exception19();
extern void exception20();
extern void exception21();
extern void exception22();
extern void exception23();
extern void exception24();
extern void exception25();
extern void exception26();
extern void exception27();
extern void exception28();
extern void exception29();
extern void exception30();
extern void exception31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#define IRQ_BASE            0x20
#define IRQ_0_TIMER          0x00
#define IRQ_1_KEYBOARD       0x01
#define IRQ_2_CASCADE        0x02
#define IRQ_3_SERIAL_PORT2   0x03
#define IRQ_4_SERIAL_PORT1   0x04
#define IRQ_5_RESERVED       0x05
#define IRQ_6_DISKETTE_DRIVE 0x06
#define IRQ_7_PARALLEL_PORT  0x07
#define IRQ_8_CMOS_CLOCK     0x08
#define IRQ_9_CGA            0x09
#define IRQ_10_RESERVED      0x0A
#define IRQ_11_RESERVED      0x0B
#define IRQ_12_AUXILIARY     0x0C
#define IRQ_13_FPU           0x0D
#define IRQ_14_HARD_DISK     0x0E
#define IRQ_15_RESERVED      0x0F

#endif