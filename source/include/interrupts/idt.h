#ifndef IDT_H
#define IDT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <include/common/common.h>

#define NO_IDT_DESCRIPTORS     256

typedef struct {
    uint16_t base_low;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t type;
    uint16_t base_high;
} __attribute__((packed)) idt;

typedef struct {
    uint16_t limit;
    uint32_t base_address;
} __attribute__((packed)) idt_pointer;

extern void load_idt(uint32_t idt_pointer);
void idt_set_entry(int index, uint32_t base, uint16_t seg_sel, uint8_t flags);
void init_idt();

#endif