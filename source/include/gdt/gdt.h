#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#define GDTBASE    0x0
#define GDTSIZE    0xFF

struct gdt_descriptor {
	uint16_t lim0_15;
	uint16_t base0_15;
	uint8_t base16_23;
	uint8_t acces;
	uint8_t lim16_19:4;
	uint8_t other:4;
	uint8_t base24_31;
} __attribute__ ((packed));

struct gdt_pointer {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

void init_gdt_descriptor(uint32_t base, uint32_t limit, uint8_t acces, uint8_t other, struct gdt_descriptor *descriptor);
void init_gdt(void);

#ifdef __GDT__
	struct gdt_descriptor kernel_gdt[GDTSIZE];
	struct gdt_pointer kernel_gdt_pointer;
#else
	extern struct gdt_descriptor kernel_gdt[];
	extern struct gdt_pointer kernel_gdt_pointer;
#endif

#endif